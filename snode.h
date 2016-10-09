#pragma once

#include "bitvector.h"

namespace chdl_internal {

class snodeimpl;

class snode {
public:

  snode() : m_impl(nullptr) {}
  snode(const snode& rhs);
  snode(snode&& rhs);
  snode(const snode& rhs, uint32_t size);
  explicit snode(snodeimpl* impl);
  snode(const std::string& value);
  explicit snode(const std::initializer_list<uint32_t>& value, uint32_t size);

  virtual ~snode();
  
  snode& operator=(const snode& rhs);
  
  snode& operator=(snode&& rhs);
  
  uint32_t get_size() const;
  
  uint32_t read(uint32_t idx) const;
  
  void write(uint32_t idx, uint32_t value);
  
  void assign(const std::initializer_list<uint32_t>& value, uint32_t size);
  
  void assign(uint32_t dst_offset, const snode& src, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  explicit operator snodeimpl*() const {
    return m_impl; 
  }
  
  void ensureInitialized(uint32_t size) const;

protected:

  void assign(snodeimpl* impl);
  
  void move(snode& rhs);
  
  mutable snodeimpl* m_impl;
  
  friend class context;
};

}
