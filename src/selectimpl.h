#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class selectimpl : public lnodeimpl {
public:

  bool has_key() const {
    return has_key_;
  }

  const auto& key() const {
    return this->src(0);
  }

  void remove_key() {
    this->remove_src(0);
    has_key_ = false;
  }

  bool is_ternary() const {
    return this->num_srcs() == (has_key() ? 4 : 3);
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  bool equals(const lnodeimpl& other) const override;

  void print(std::ostream& out) const override;

protected:

  selectimpl(context* ctx,
             uint32_t size,
             lnodeimpl* key,
             const source_location& sloc);

  bool has_key_;

  friend class context;
};

}
}
