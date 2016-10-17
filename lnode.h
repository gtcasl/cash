#pragma once

#include "typebase.h"

namespace chdl_internal {

class lnodeimpl;
class context;

typedef uint64_t ch_cycle;

class lnode {
public:

  lnode() : m_impl(nullptr) {}
  
  lnode(const lnode& rhs);
  lnode(lnode&& rhs);
  lnode(const lnode& rhs, uint32_t size);
  explicit lnode(lnodeimpl* impl);
  lnode(const std::string& value);
  explicit lnode(const std::initializer_list<uint32_t>& value, uint32_t size);

  virtual ~lnode();
  
  lnode& operator=(const lnode& rhs);
  
  lnode& operator=(lnode&& rhs);

  uint32_t get_id() const;
  
  uint32_t get_size() const;
  
  context* get_ctx() const;
  
  bool ready() const;
  
  bool valid() const;
 
  const bitvector& eval(ch_cycle t);
  
  void assign(const std::initializer_list<uint32_t>& value, uint32_t size);
  
  void assign(uint32_t dst_offset, const lnode& src, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  void read(std::vector< partition<lnode> >& out, uint32_t offset, uint32_t length, uint32_t size) const;
  
  void write(uint32_t dst_offset, const std::vector< partition<lnode> >& src, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  void ensureInitialized(uint32_t offset, uint32_t length, uint32_t size) const;
    
  explicit operator lnodeimpl*() const { 
    assert(m_impl);
    return m_impl; 
  }  

protected:  
  
  void reset(lnodeimpl* impl = nullptr) const;

  void assign(lnodeimpl* impl) const;
  
  void move(lnode& rhs);
  
  mutable lnodeimpl* m_impl;
  
  friend class lnodeimpl;
  friend class proxyimpl;
  friend class context;
  template <typename T> friend T* get_impl(const lnode& n);
};

template <typename T>
T* get_impl(const lnode& node) {
  return dynamic_cast<T*>(node.m_impl);
}

inline std::ostream& operator<<(std::ostream& out, const lnode& rhs) {
  out << rhs.get_id();
  return out;
}

lnode createNullNode(uint32_t size);

}
