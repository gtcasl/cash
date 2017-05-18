#pragma once

#include "typebase.h"
#include "bitvector.h"

namespace cash {
namespace detail {

class snodeimpl;

class snode {
public:
  
  using data_type = nodeset<snode>;
  
  snode() : impl_(nullptr) {}
  snode(const snode& rhs);
  snode(snode&& rhs);
  explicit snode(snodeimpl* impl);
  snode(const data_type& data);
  snode(const bitvector& value);

  ~snode();
  
  const snode& ensureInitialized(uint32_t size) const;
  
  snodeimpl* get_impl() const;
  
  snode& operator=(const snode& rhs);
  
  snode& operator=(snode&& rhs);
  
  bool operator==(const snode& rhs) const;
  
  bool operator<(const snode& rhs) const;
  
  uint32_t get_size() const;
  
  uint32_t read(uint32_t idx) const;
  
  void write(uint32_t idx, uint32_t value);
  
  void read(uint8_t* out, uint32_t sizeInBytes) const;
  
  void write(const uint8_t* in, uint32_t sizeInBytes);
  
  void assign(const bitvector& value);
  
  void read(data_type& inout, uint32_t offset, uint32_t length, uint32_t size) const;
  
  void write(uint32_t dst_offset, const data_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size);

protected:
  
  void assign(uint32_t dst_offset, const snode& src, uint32_t src_offset, uint32_t src_length, uint32_t size);
  
  void assign(snodeimpl* impl, bool is_owner = false);
  
  void move(snode& rhs);
  
  void clone() const;
    
  mutable snodeimpl* impl_;
};

std::ostream& operator<<(std::ostream& os, const snode& node);

}
}
