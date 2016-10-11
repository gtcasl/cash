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

snodeimpl::snodeimpl(const std::string& value)
  : m_id(generate_id())
  , m_value(value)
  , m_changeid(1) // m_value has been set
{}

snodeimpl::snodeimpl(const std::initializer_list<uint32_t>& value, uint32_t size) 
  : m_id(generate_id())
  , m_value(value, size)
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
  if (n == 0) {
    src->acquire();
    m_srcs.push_back({ src, start, offset, length });       
  } else {  
    for (uint32_t i = 0; length && i < n; ++i) {
      source_t& curr = m_srcs[i];
      uint32_t src_end  = start + length;
      uint32_t curr_end = curr.start + curr.length;
      
      src->acquire();
      source_t new_src = { src, start, offset, length };
      
      // do ranges intersect?
      if ((curr_end > start && src_end > curr.start)) {
        if (start <= curr.start && src_end >= curr_end) {
          // source fully overlaps
          uint32_t len = curr_end - start;
          new_src.length = len;
          curr.node->release();          
          curr = new_src;
          
          start  += len;        
          offset += len;        
          length -= len;        
        } else if (start < curr.start) {
          // source intersets left
          uint32_t overlap = src_end - curr.start;
          curr.start  += overlap;
          curr.offset += overlap;
          curr.length -= overlap;
          
          m_srcs.insert(m_srcs.begin() + i, new_src); 
          ++i;
          ++n;
          
          length = 0;  
        } else if (src_end > curr_end) {
          // source intersets right
          uint32_t overlap = curr_end - start;
          curr.length -= overlap;
          
          new_src.length = overlap;
          m_srcs.insert(m_srcs.begin() + (i + 1), new_src); 
          ++i;
          ++n;       
          
          start  += overlap;
          offset += overlap;
          length -= overlap;
        } else {
          // source fully included          
          source_t curr_after(curr);
          uint32_t delta = src_end - curr.start;        
          curr_after.start  += delta;
          curr_after.offset += delta;
          curr_after.length -= delta;
          
          curr.length -= (curr_end - start);
          
          m_srcs.insert(m_srcs.begin() + (i + 1), 2, new_src); // insert two copies 
          m_srcs[i+2] = curr_after; // udpate second copy
          i += 2;
          n += 2;
          
          length = 0;
        }
      } else {
        uint32_t j = i + (curr_end <= start) ? 0 : 1;
        m_srcs.insert(m_srcs.begin() + j, new_src);       
        ++i;
        ++n;
        
        length = 0;
      } 
    }
  }
}

void snodeimpl::sync_sources() const {
  if (m_srcs.size() == 0)
    return;
  
  int changed = 0;
  for (source_t& src : m_srcs) {
    if (src.changeid != src.node->m_changeid) {
      src.changeid = src.node->m_changeid;
      m_value.copy(src.start, src.node->read(), src.offset, src.length);      
      changed = 1;
    }
  }
  m_changeid += changed;
}

///////////////////////////////////////////////////////////////////////////////

snode::snode(const snode& rhs) : m_impl(nullptr), m_readonly(false) {
  this->assign(rhs.m_impl); 
}

snode::snode(snode&& rhs) : m_impl(nullptr), m_readonly(false) {  
  this->move(rhs);
}

snode::snode(const snode& rhs, uint32_t size) : m_impl(nullptr), m_readonly(false) {
  rhs.ensureInitialized(size);  
  this->assign(rhs.m_impl);
}

snode::snode(snodeimpl* impl) : m_impl(nullptr), m_readonly(false) {
  this->assign(impl);
}

snode::snode(const std::string& value) : m_impl(nullptr), m_readonly(false) {
  this->assign(new snodeimpl(value), true);
}

snode::snode(const std::initializer_list<uint32_t>& value, uint32_t size) 
  : m_impl(nullptr), m_readonly(false) {
  this->assign(value, size);  
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

uint32_t snode::get_size() const {
  return m_impl ? m_impl->get_size() : 0;
}

void snode::ensureInitialized(uint32_t size) const {
  if (m_impl == nullptr) {
    m_impl = new snodeimpl(size);
    m_impl->acquire();
  }
  assert(m_impl->get_size() == size);
}

void snode::move(snode& rhs) {  
  m_impl = rhs.m_impl;
  m_readonly = rhs.m_readonly;
  rhs.m_impl = nullptr;
  rhs.m_readonly = false;
}

void snode::assign(const std::initializer_list<uint32_t>& value, uint32_t size) {
  this->assign(new snodeimpl(value, size), true);
}

void snode::assign(snodeimpl* impl, bool is_owner) {  
  assert(impl);
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

void snode::assign(uint32_t dst_offset, const snode& src, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert((dst_offset + src_length) <= size);
  if (size == src_length && size == src.get_size()) {
    assert(dst_offset == 0 && src_offset == 0);
    this->assign(src.m_impl);
  } else {
    this->ensureInitialized(size);
    if (m_readonly)
      this->clone();
    m_impl->assign(dst_offset, src.m_impl, src_offset, src_length);
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

uint32_t snode::read(uint32_t idx, uint32_t size) const {
  this->ensureInitialized(size);
  return m_impl->read(idx);
}

void snode::write(uint32_t idx, uint32_t value, uint32_t size) {
  this->ensureInitialized(size);
  if (m_readonly)
    this->clone();
  m_impl->write(idx, value);
}

bool snode::to_bool(uint32_t size) const {
  this->ensureInitialized(size);
  return m_impl->to_bool();
}

void snode::read(std::vector< partition<snode> >& out, uint32_t offset, uint32_t length, uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size);
  out.push_back({*this, offset, length});
}

void snode::write(uint32_t dst_offset, const std::vector< partition<snode> >& src, uint32_t src_offset, uint32_t src_length, uint32_t size) {
  assert((dst_offset + src_length) <= size);
  for (auto& p : src) {
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
