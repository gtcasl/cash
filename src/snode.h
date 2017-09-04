#pragma once

#include "typebase.h"

namespace cash {
namespace internal {

class snodeimpl;

class snode {
public:
  
  using data_type = nodebuf<const snode&>;
  
  snode();

  snode(const snode& rhs);

  snode(const snode& rhs, uint32_t size);

  snode(snode&& rhs);

  snode(snodeimpl* impl);

  snode(const data_type& data);

  snode(const bitvector& value);

  ~snode();
  
  snode& operator=(const snode& rhs);

  snode& operator=(snode&& rhs);

  bool is_empty() const;
  
  bool is_equal(const snode& rhs, uint32_t size) const;
  
  bool is_less(const snode& rhs, uint32_t size) const;

  uint32_t get_id() const;

  snodeimpl* get_impl() const;
  
  uint32_t get_size() const;

  const bitvector& get_value() const;

  bool operator[](uint32_t idx) const;

  void assign(const snode& rhs, uint32_t size);

  void assign(const bitvector& rhs);
  
  uint32_t get_word(uint32_t idx, uint32_t size) const;
  
  void set_word(uint32_t idx, uint32_t value, uint32_t size);
  
  void read(uint32_t dst_offset,
            void* out,
            uint32_t sizeInBytes,
            uint32_t src_offset,
            uint32_t length,
            uint32_t size) const;
  
  void write(uint32_t dst_offset,
             const void* in,
             uint32_t sizeInBytes,
             uint32_t src_offset,
             uint32_t length,
             uint32_t size);

  void read_data(data_type& inout,
                 uint32_t offset,
                 uint32_t length,
                 uint32_t size) const;
  
  void write_data(uint32_t dst_offset,
                  const data_type& in,
                  uint32_t src_offset,
                  uint32_t length,
                  uint32_t size);

protected:

  void ensureInitialized(uint32_t size) const;

  void clear();
  
  void assign(uint32_t dst_offset,
              const snode& src,
              uint32_t src_offset,
              uint32_t length,
              uint32_t size,
              bool is_owner);
  
  void assign(snodeimpl* impl, bool is_owner);
  
  void move(snode& rhs);
  
  void clone(bool keep_data);
    
  mutable snodeimpl* impl_;
};

std::ostream& operator<<(std::ostream& os, const snode& node);

}
}
