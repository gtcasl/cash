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

  lnode(uint32_t size, const lnode& src, unsigned src_offset = 0);

  lnode(lnodeimpl* impl);

  lnode(const bitvector& value);

  ~lnode();

  lnode& operator=(const lnode& rhs);

  void clear();

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length);

  bool empty() const;

  void set_impl(lnodeimpl* impl);

  lnodeimpl* get_impl() const;
  
  uint32_t get_id() const;

  const std::string& get_name() const;

  void set_name(const std::string& name);
  
  uint32_t size() const;
  
  context* get_ctx() const;

  const bitvector& get_data() const;

  bitvector& get_data();

  uint32_t get_var_id() const;

  void set_var_id(uint32_t var_id);

  const source_location& get_source_location() const;

  void set_source_location(const source_location& sloc);

  lnodeimpl* clone() const;

  const bitvector& eval(ch_tick t) const;

protected:

  mutable lnodeimpl* impl_;

  inline friend bool operator==(const lnode& lhs, const lnode& rhs) {
    return lhs.get_id() == rhs.get_id();
  }

  inline friend bool operator!=(const lnode& lhs, const lnode& rhs) {
    return lhs.get_id() != rhs.get_id();
  }

  inline friend bool operator<(const lnode& lhs, const lnode& rhs) {
    return lhs.get_id() < rhs.get_id();
  }
};

std::ostream& operator<<(std::ostream& out, const lnode& node);

}
}
