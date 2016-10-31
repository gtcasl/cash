#pragma once

#include "typebase.h"
#include "bitvector.h"

namespace chdl_internal {

class snodeimpl;

class snode {
public:
  
  typedef bitstream<snodeimpl> bitstream_type;
  
  snode() : m_impl(nullptr), m_readonly(false) {}
  snode(const snode& rhs);
  snode(snode&& rhs);
  explicit snode(snodeimpl* impl);
  snode(const bitstream_type& data);
  snode(const bitvector& value);

  virtual ~snode();
  
  const snode& ensureInitialized(uint32_t size) const;
  
  snodeimpl* get_impl() const {
    assert(m_impl);
    return m_impl;
  }
  
  snode& operator=(const snode& rhs);
  
  snode& operator=(snode&& rhs);
  
  bool operator==(const snode& rhs) const;
  
  bool operator<(const snode& rhs) const;
  
  uint32_t get_size() const;
  
  uint32_t read(uint32_t idx) const;
  
  void write(uint32_t idx, uint32_t value);
  
  void assign(const bitvector& value);
  
  void assign(uint32_t dst_offset, snodeimpl* src, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  void read(bitstream_type& inout, uint32_t offset, uint32_t length, uint32_t size) const;
  
  void write(uint32_t dst_offset, const bitstream_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  bool to_bool() const;

protected:
  
  void assign(snodeimpl* impl, bool is_owner = false);
  
  void move(snode& rhs);
  
  void clone() const;
  
  mutable snodeimpl* m_impl;
  mutable bool m_readonly;
};

std::ostream& operator<<(std::ostream& os, const snode& node);

}
