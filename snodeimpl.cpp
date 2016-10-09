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
  , m_output(nullptr)
  , m_value(size)
  , m_ctime(~0ull) 
{}

snodeimpl::snodeimpl(ioimpl_ptr output) 
  : m_id(generate_id())
  , m_output(output)
  , m_value(output->get_size())
  , m_ctime(~0ull) {
  output->::refcounted::acquire();
}

snodeimpl::snodeimpl(const std::string& value)
  : m_id(generate_id())
  , m_output(nullptr)
  , m_value(value)
  , m_ctime(~0ull) 
{}

snodeimpl::snodeimpl(const std::initializer_list<uint32_t>& value, uint32_t size) 
  : m_id(generate_id())
  , m_output(nullptr)
  , m_value(value, size)
  , m_ctime(~0ull) 
{}

snodeimpl::~snodeimpl() {
  if (m_output) {
    m_output->release();
    assert(m_srcs.size() == 0);
  } else {
    for (auto& src : m_srcs) {
      assert(src.node);
      src.node->release();
    }
  }
}

void snodeimpl::assign(uint32_t start, snodeimpl_ptr src, uint32_t offset, uint32_t length) {
  assert(this != src);
  // disconnect output port if present  
  if (m_output) {
    m_output->release();
    m_output = nullptr;
  }  
  
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

const bitvector& snodeimpl::eval(ch_cycle t) {
  if (m_ctime != t) {
    m_ctime = t;
    
    if (m_output) {
      m_value = m_output->eval(t);
    } else {
      for (auto& src : m_srcs) {
        assert(src.node);
        m_value.copy(src.start, src.node->eval(t), src.offset, src.length);
      }
    }
  }
  return m_value;
}

context* snodeimpl::get_ctx() const {
  return m_output ? m_output->get_ctx() : nullptr; 
}

///////////////////////////////////////////////////////////////////////////////

snode::snode(const snode& rhs) : m_impl(nullptr) {
  this->assign(rhs.m_impl); 
}

snode::snode(snode&& rhs) : m_impl(nullptr) {  
  this->move(rhs);
}

snode::snode(const snode& rhs, uint32_t size) : m_impl(nullptr) {
  rhs.ensureInitialized(size);  
  this->assign(rhs.m_impl);
}

snode::snode(snodeimpl* impl) : m_impl(nullptr) {
  this->assign(impl);
}

snode::snode(const std::string& value) : m_impl(nullptr) {
  snodeimpl* impl = new snodeimpl(value);
  this->assign(impl);
  impl->release();
}

snode::snode(const std::initializer_list<uint32_t>& value, uint32_t size) : m_impl(nullptr) {
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
  }
  assert(m_impl->get_size() == size);
}

void snode::move(snode& rhs) {  
  m_impl = rhs.m_impl;
  rhs.m_impl = nullptr;
}

void snode::assign(const std::initializer_list<uint32_t>& value, uint32_t size) {
  this->assign(new snodeimpl(value, size));
}

void snode::assign(snodeimpl_ptr impl) {  
  assert(impl);
  if (m_impl == nullptr) {
    impl->acquire();
    m_impl = impl;
  } else {
    if (m_impl != impl)
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
    m_impl->assign(dst_offset, src.m_impl, src_offset, src_length);
  }  
}

uint32_t snode::read(uint32_t idx) const {
  assert(m_impl);
  return m_impl->read(idx);
}

void snode::write(uint32_t idx, uint32_t value) {
  assert(m_impl);
  m_impl->write(idx, value);
}
