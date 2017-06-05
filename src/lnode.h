#pragma once

#include "typebase.h"
#include "bitvector.h"

namespace cash {
namespace detail {

class lnodeimpl;
class context;

using ch_cycle = uint64_t;

class lnode {
public:
  
  using data_type = nodeset<lnodeimpl*>;

  lnode();

  lnode(uint32_t size);

  lnode(const lnode& rhs);

  lnode(lnode&& rhs);

  explicit lnode(lnodeimpl* impl);

  lnode(const data_type& data);

  lnode(const bitvector& value);
  
  ~lnode();

  const lnode& ensureInitialized(uint32_t size) const;
  
  lnodeimpl* get_impl() const;

  void set_impl(lnodeimpl* impl);
  
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
  
  void read_data(data_type& inout, uint32_t offset, uint32_t length, uint32_t size) const;
  
  void write_data(uint32_t dst_offset, const data_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size);

protected:

  void clear();

  void assign(lnodeimpl* impl, bool initialization = false);
  
  void move(lnode& rhs);
  
  void assign(uint32_t dst_offset, lnodeimpl* src, uint32_t src_offset, uint32_t src_length, uint32_t size, bool initialization = false);
  
  mutable lnodeimpl* impl_;
  
  friend class lnodeimpl;
  friend class context; 
};

inline std::ostream& operator<<(std::ostream& out, const lnode& rhs) {
  out << rhs.get_id();
  return out;
}

}
}
