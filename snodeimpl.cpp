#include "snodeimpl.h"
#include "ioimpl.h"
#include "bus.h"

using namespace std;
using namespace chdl_internal;

static uint32_t generate_id() {
  static uint32_t s_id(0);
  return ++s_id;
}

snodeimpl::snodeimpl(uint32_t size) 
  : m_id(generate_id())
  , m_value(size)
  , m_changeid(0) 
{}

snodeimpl::snodeimpl(const bitvector& value)
  : m_id(generate_id())
  , m_value(value)
  , m_changeid(1) // m_value has been set
{}

snodeimpl::~snodeimpl() {
  for (auto& src : m_srcs) {
    assert(src.node);
    src.node->release();
  }
}

void snodeimpl::assign(uint32_t start, snodeimpl* src, uint32_t offset, uint32_t length) {
  assert(src != nullptr && this != src);    
  
  uint32_t n = m_srcs.size();
  if (n > 0) {
    uint32_t i = 0;
    for (; length && i < n; ++i) {
      source_t& curr = m_srcs[i];
      uint32_t src_end  = start + length;
      uint32_t curr_end = curr.start + curr.length;
      
      source_t new_src = { src, start, offset, length };
      
      // do ranges intersect?
      if ((start < curr_end && src_end > curr.start)) {
        if (start <= curr.start && src_end >= curr_end) {
          // source fully overlaps
          uint32_t len = curr_end - start;
          new_src.length = len;
          src->acquire();
          curr.node->release();          
          curr = new_src;
          
          start  += len;        
          offset += len;        
          length -= len;    
 // LCOV_EXCL_START        
        } else if (start < curr.start) {
          // source intersets left
          uint32_t overlap = src_end - curr.start;
          curr.start  += overlap;
          curr.offset += overlap;
          curr.length -= overlap;
          
          src->acquire();
          m_srcs.insert(m_srcs.begin() + i, new_src);
          ++n;
          
          length = 0;  
        } else if (src_end > curr_end) {
          // source intersets right
          uint32_t overlap = curr_end - start;
          curr.length -= overlap;
          
          new_src.length = overlap;
          
          ++i;
          src->acquire();
          m_srcs.insert(m_srcs.begin() + i, new_src); 
          ++n;       
          
          start  += overlap;
          offset += overlap;
          length -= overlap;
        } else {
          // source fully included          
          uint32_t delta = src_end - curr.start;
          source_t curr_after(curr);          
          curr_after.length -= delta;
          curr_after.start  += delta;
          curr_after.offset += delta;
          
          src->acquire();
          curr.length -= (curr_end - start);
          if (curr.length > 0) {
            ++i;
            m_srcs.insert(m_srcs.begin() + i, 1, new_src);
            ++n;
          } else {
            curr = new_src;
          }          
          
          if (curr_after.length) {                              
            m_srcs.insert(m_srcs.begin() + (i+1), 1, curr_after); 
            ++n;
          }         
          length = 0;
        }
 // LCOV_EXCL_END
      } else if (i+1 == n || src_end <= m_srcs[i+1].start) {
        // no overlap with current and next
        i += (curr_end <= start) ? 1 : 0;
        src->acquire();
        m_srcs.insert(m_srcs.begin() + i, new_src);   
        ++n;
        
        length = 0;
      } else {
        // no overlap with current, skip merge if no update took place
        continue;
      }
      
      if (i > 0) {
        // try merging inserted node on the left
        this->merge_left(i);
      }       
    } 
    assert(length == 0);    
    if (i < n) {
      // try merging inserted node on the right
      this->merge_left(i);
    }
  } else {
    src->acquire();
    m_srcs.push_back({ src, start, offset, length });       
  }
}

void snodeimpl::merge_left(uint32_t idx) {
  assert(idx > 0);
  if (m_srcs[idx-1].node == m_srcs[idx].node && 
      (m_srcs[idx-1].start + m_srcs[idx-1].length) == m_srcs[idx].start &&
      m_srcs[idx].offset == m_srcs[idx-1].offset + m_srcs[idx-1].length) {
    m_srcs[idx].node->release();
    m_srcs[idx-1].length += m_srcs[idx].length;
    m_srcs.erase(m_srcs.begin() + idx);
  }      
}

uint64_t snodeimpl::sync_sources() const {
  if (!m_srcs.empty()) {  
    int changed = 0;
    for (source_t& src : m_srcs) {
      uint64_t changeid = src.node->sync_sources();
      if (src.changeid != changeid) {
        src.changeid = changeid;
        m_value.copy(src.start, src.node->read(), src.offset, src.length);      
        changed = 1;
      }
    }
    m_changeid += changed;
  }
  return m_changeid;
}

///////////////////////////////////////////////////////////////////////////////

snode::snode(const snode& rhs) : m_impl(nullptr), m_readonly(false) {
  this->assign(rhs.m_impl); 
}

snode::snode(snode&& rhs) : m_impl(nullptr), m_readonly(false) {  
  this->move(rhs);
}

snode::snode(snodeimpl* impl) : m_impl(nullptr), m_readonly(false) {
  this->assign(impl);
}

snode::snode(const bitstream_type& data) : m_impl(nullptr), m_readonly(false) {
  uint32_t dst_offset = 0;
  for (auto& p : data) {
    this->assign(dst_offset, p.data, p.offset, p.length, data.get_size());   
    dst_offset += p.length;
  }
}

snode::snode(const bitvector& value) : m_impl(nullptr), m_readonly(false) {
  this->assign(new snodeimpl(value), true);
}

snode::~snode() {
  if (m_impl) {
    m_impl->release();
    m_impl == nullptr;
  }
}

snode& snode::operator=(const snode& rhs) {
  this->assign(rhs.m_impl);
  return *this;
}

snode& snode::operator=(snode&& rhs) {
  this->move(rhs);
  return *this;
}

bool snode::operator==(const snode& rhs) const {
  return (m_impl->get_value() == rhs.m_impl->get_value());
}

bool snode::operator<(const snode& rhs) const {
  return (m_impl->get_value() < rhs.m_impl->get_value());
}

uint32_t snode::get_size() const {
  return m_impl ? m_impl->get_size() : 0;
}

snodeimpl* snode::get_impl() const {
  assert(m_impl);
  return m_impl;
}

const snode& snode::ensureInitialized(uint32_t size) const {
  if (m_impl == nullptr) {
    m_impl = new snodeimpl(size);
    m_impl->acquire();
  }
  assert(m_impl->get_size() == size);
  return *this;
}

void snode::move(snode& rhs) {  
  assert(m_impl != rhs.m_impl);
  m_impl = rhs.m_impl;
  m_readonly = rhs.m_readonly;
  rhs.m_impl = nullptr;
  rhs.m_readonly = false;
}

void snode::assign(const bitvector& value) {
  this->assign(new snodeimpl(value), true);
}

void snode::assign(snodeimpl* impl, bool is_owner) {  
  assert(impl && m_impl != impl);
  if (m_impl == nullptr) {
    impl->acquire();
    m_impl = impl;
    m_readonly = !is_owner;
  } else {
    if (m_readonly)
      this->clone();
    m_impl->assign(0, impl, 0, impl->get_size());
  }
}

void snode::assign(uint32_t dst_offset, snodeimpl* src, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert((dst_offset + src_length) <= size);
  if (size == src_length && size == src->get_size()) {
    assert(dst_offset == 0 && src_offset == 0);
    this->assign(src);
  } else {
    this->ensureInitialized(size);
    if (m_readonly)
      this->clone();
    m_impl->assign(dst_offset, src, src_offset, src_length);
  }  
}

void snode::clone() const {
  assert(m_readonly);
  snodeimpl* impl = m_impl;
  m_impl = nullptr;
  this->ensureInitialized(impl->get_size());  
  m_impl->assign(0, impl, 0, impl->get_size());
  impl->release();
  m_readonly = false;
}

uint32_t snode::read(uint32_t idx) const {
  assert(m_impl);
  return m_impl->read(idx);
}

void snode::write(uint32_t idx, uint32_t value) {
  assert(m_impl);
  if (m_readonly)
    this->clone();
  m_impl->write(idx, value);
}

void snode::readBytes(uint8_t* out, uint32_t sizeInBytes) const {
  m_impl->readBytes(out, sizeInBytes);
}

void snode::writeBytes(const uint8_t* in, uint32_t sizeInBytes) {
  m_impl->writeBytes(in, sizeInBytes);
}

void snode::read(bitstream_type& inout, uint32_t offset, uint32_t length, uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size);
  inout.push({m_impl, offset, length});
}

void snode::write(uint32_t dst_offset, const bitstream_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert((dst_offset + src_length) <= size);
  for (auto& p : in) {
    if (src_offset < p.length) {
      size_t len = std::min(p.length - src_offset, src_length);
      this->assign(dst_offset, p.data, p.offset + src_offset, len, size);         
      src_length -= len;
      if (src_length == 0)
        return;
      dst_offset += len;                
      src_offset = p.length;
    }
    src_offset -= p.length;
  }
}

std::ostream& chdl_internal::operator<<(std::ostream& os, const snode& node) {
  return os << node.get_impl()->get_value();
}
