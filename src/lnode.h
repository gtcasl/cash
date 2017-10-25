#pragma once

#include "common.h"
#include "bitvector.h"

namespace ch {
namespace internal {

class lnodeimpl;
class proxyimpl;
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

  lnode& operator=(const lnode& rhs);

  const lnode& ensureInitialized(uint32_t size, bool initialize = true) const;

  void clear();

  void move(const lnode& rhs);

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length,
             uint32_t size);

  bool is_empty() const;

  void set_impl(lnodeimpl* impl);

  lnodeimpl* get_impl() const;
  
  uint32_t get_id() const;
  
  uint32_t get_size() const;
  
  context* get_ctx() const;

  const bitvector& get_data() const;

  bitvector& get_data();

  bool get_bool(unsigned index) const;

  void set_bool(unsigned index, bool value);

  lnodeimpl* clone() const;

  const bitvector& eval(ch_tick t);

protected:

  mutable lnodeimpl* impl_;

  inline friend bool operator==(const lnode& lhs, const lnode& rhs) {
    return lhs.get_id() == rhs.get_id();
  }

  inline friend bool operator!=(const lnode& lhs, const lnode& rhs) {
    return lhs.get_id() != rhs.get_id();
  }

};

std::ostream& operator<<(std::ostream& out, const lnode& node);

}
}
