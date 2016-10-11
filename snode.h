#pragma once

#include "typebase.h"

namespace chdl_internal {

class snodeimpl;

class snode {
public:

  snode() : m_impl(nullptr), m_readonly(false) {}
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
  
  uint32_t read(uint32_t idx, uint32_t size) const;
  
  void write(uint32_t idx, uint32_t value, uint32_t size);
  
  void assign(const std::initializer_list<uint32_t>& value, uint32_t size);
  
  void assign(uint32_t dst_offset, const snode& src, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  void read(std::vector< partition<snode> >& out, uint32_t offset, uint32_t length, uint32_t size) const;
  
  void write(uint32_t dst_offset, const std::vector< partition<snode> >& src, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  bool to_bool(uint32_t size) const;
  
  void ensureInitialized(uint32_t size) const;
  
  explicit operator snodeimpl*() const {
    assert(m_impl);
    if (m_readonly)
      this->clone();
    return m_impl; 
  }

protected:
  
  void assign(snodeimpl* impl, bool is_owner = false);
  
  void move(snode& rhs);
  
  void clone() const;
  
  mutable snodeimpl* m_impl;
  mutable bool m_readonly;
  
  friend class context;
};

}
