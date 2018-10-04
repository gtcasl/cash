#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class selectimpl : public lnodeimpl {
public:

  bool has_key() const {
    return key_idx_ != -1;
  }

  auto& key() const {
    return srcs_[key_idx_];
  }

  void remove_key() {
    this->srcs().erase(this->srcs().begin());
    key_idx_ = -1;
  }

  bool is_ternary() const {
    return srcs_.size() == (has_key() ? 4 : 3);
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  bool equals(const lnodeimpl& other) const override;

  std::size_t hash() const override;

  void print(std::ostream& out) const override;

protected:

  selectimpl(context* ctx,
             uint32_t size,
             lnodeimpl* key,
             const source_location& sloc);

  int key_idx_;

  friend class context;
};

}
}
