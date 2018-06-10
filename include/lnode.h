#pragma once

#include "common.h"
#include "bitvector.h"

namespace ch {
namespace internal {

class lnodeimpl;

using ch_tick = uint64_t;

class lnode {
public:

  lnode();

  lnode(const lnode& rhs);

  explicit lnode(uint32_t size,
                 uint32_t var_id = 0,
                 const std::string& name = "",
                 const source_location& sloc = source_location());

  lnode(uint32_t size,
        const lnode& src,
        uint32_t src_offset = 0,
        uint32_t var_id = 0,
        const std::string& name = "",
        const source_location& sloc = source_location());

  lnode(lnodeimpl* impl);

  lnode(const bitvector& value);

  ~lnode();

  lnode& operator=(const lnode& rhs);

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length);

  bool empty() const;

  lnodeimpl* impl() const;
  
  uint32_t id() const;

  const std::string& name() const;
  
  uint32_t size() const;

  const bitvector& data() const;

  bitvector& data();

  uint32_t var_id() const;

  void set_var_id(uint32_t var_id);

  const source_location& sloc() const;

  lnodeimpl* clone() const;  

protected:

  mutable lnodeimpl* impl_;

  inline friend bool operator==(const lnode& lhs, const lnode& rhs) {
    return lhs.id() == rhs.id();
  }

  inline friend bool operator!=(const lnode& lhs, const lnode& rhs) {
    return lhs.id() != rhs.id();
  }

  inline friend bool operator<(const lnode& lhs, const lnode& rhs) {
    return lhs.id() < rhs.id();
  }
};

std::ostream& operator<<(std::ostream& out, const lnode& node);

}
}
