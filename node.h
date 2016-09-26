#pragma once

#include "bitvector.h"

namespace chdl_internal {

class nodeimpl;
class context;

class ch_node {
public:

  ch_node() : m_impl(nullptr) {}
  ch_node(const ch_node& rhs);
  ch_node(ch_node&& rhs);
  ch_node(const ch_node& rhs, uint32_t size);
  explicit ch_node(nodeimpl* impl);
  explicit ch_node(const std::initializer_list<uint32_t>& value, uint32_t size);

  virtual ~ch_node();
  
  ch_node& operator=(const ch_node& rhs);
  
  ch_node& operator=(ch_node&& rhs);

  uint64_t get_id() const;
  
  uint32_t get_size() const;
  
  context* get_ctx() const;
  
  bool ready() const;
  
  bool valid() const;
 
  const bitvector& eval(ch_cycle t);
  
  void assign(uint32_t size, uint32_t dst_offset, const ch_node& src, uint32_t src_offset, uint32_t src_length);
  
  explicit operator nodeimpl*() const { 
    return m_impl; 
  }
  
  void ensureInitialized(uint32_t size) const;

protected:

  void assign(nodeimpl* impl);
  
  void move(ch_node& rhs);
  
  void clear();
    
  friend class nodeimpl;
  friend class context;
  template <typename T> friend T* get_impl(const ch_node& n);
  
  mutable nodeimpl* m_impl;
};

template <typename T>
T* get_impl(const ch_node& n) {
  return dynamic_cast<T*>(n.m_impl);
}

inline std::ostream& operator<<(std::ostream& out, const ch_node& rhs) {
  out << rhs.get_id();
  return out;
}

ch_node createNullNode(uint32_t size);
}
