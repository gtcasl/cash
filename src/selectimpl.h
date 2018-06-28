#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class selectimpl : public lnodeimpl {
public:

  bool has_key() const {
    return has_key_;
  }

  void remove_key() {
    this->srcs().erase(this->srcs().begin());
    has_key_ = false;
  }

  bool is_ternary() const {
    return (srcs_.size() == (has_key_ ? 4 : 3));
  }

  bool equals(const lnodeimpl& other) const override;

  std::size_t hash() const override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:

  selectimpl(context* ctx,
             uint32_t size,
             lnodeimpl* key,
             const source_location& sloc);

  ~selectimpl();

  bool has_key_;

  friend class context;
};

}
}
