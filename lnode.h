#pragma once

#include "typebase.h"
#include "bitvector.h"

namespace chdl_internal {

class lnodeimpl;
class context;

using ch_cycle = uint64_t;

class lnode {
public:
  
  using bitstream_type = bitstream<lnodeimpl>;

  lnode(uint32_t size);  
  lnode(const lnode& rhs);
  lnode(lnode&& rhs);
  explicit lnode(lnodeimpl* impl);
  lnode(const bitstream_type& data);
  lnode(const bitvector& value);
  
  ~lnode();
  
  const lnode& ensureInitialized(uint32_t size, uint32_t offset, uint32_t length) const;
  
  // LCOV_EXCL_START
  const lnode& ensureInitialized(uint32_t size) const {
    return this->ensureInitialized(size, 0, size);
  }
  // LCOV_EXCL_END
  
  lnodeimpl* get_impl() const;
  
  void set_impl(lnodeimpl* curr_impl, lnodeimpl* new_impl) const;
  
  lnode& operator=(const lnode& rhs);
  
  lnode& operator=(lnode&& rhs);
  
  lnode& operator=(lnodeimpl* rhs);
  
  uint32_t get_id() const;
  
  uint32_t get_size() const;
  
  context* get_ctx() const;
  
  bool ready() const;
  
  bool valid() const;
 
  const bitvector& eval(ch_cycle t);  
  
  void assign(const bitvector& value);
  
  void read(bitstream_type& inout, uint32_t offset, uint32_t length, uint32_t size) const;
  
  void write(uint32_t dst_offset, const bitstream_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size);

protected:   
  
  void reset(lnodeimpl* impl = nullptr, bool initialization = false) const;

  void assign(lnodeimpl* impl, bool initialization = false) const;
  
  void move(lnode& rhs);
  
  void assign(uint32_t dst_offset, lnodeimpl* src, uint32_t src_offset, uint32_t src_length, uint32_t size, bool initialization);
  
  mutable lnodeimpl* m_impl;
};

inline std::ostream& operator<<(std::ostream& out, const lnode& rhs) {
  out << rhs.get_id();
  return out;
}

}
