#pragma once

#include "common.h"
#include "bitvector.h"

namespace ch {
namespace internal {

class lnodeimpl;
class context;

using ch_tick = uint64_t;

class lnode {
public:

  lnode();

  lnode(const lnode& rhs);

  explicit lnode(uint32_t size);

  lnode(uint32_t size, const lnode& src, unsigned src_offset);

  lnode(lnodeimpl* impl);

  lnode(const bitvector& value);

  ~lnode();

  const lnode& ensureInitialized(uint32_t size) const;

  lnode& operator=(const lnode& rhs);

  void clear();

  bool is_empty() const;

  void set_impl(lnodeimpl* impl);

  lnodeimpl* get_impl() const;
  
  uint32_t get_id() const;
  
  uint32_t get_size() const;
  
  context* get_ctx() const;

  const bitvector& eval(ch_tick t);

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length,
             uint32_t size);

  const bitvector& get_data() const;

  bitvector& get_data();

  bool get_bool(unsigned index) const;

  void set_bool(unsigned index, bool value);

  lnodeimpl* clone(uint32_t size) const;

protected:

  void ensureInitialized(uint32_t size, bool initialize) const;
  
  mutable lnodeimpl* impl_;
};

std::ostream& operator<<(std::ostream& out, const lnode& node);

}
}
