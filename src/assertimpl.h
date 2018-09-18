#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class assertimpl : public ioimpl {
public:

  const auto& condition() const {
    return srcs_[cond_idx_];
  }

  const std::string& message() const {
    return message_;
  }

  bool is_predicated() const {
    return (pred_idx_ != -1);
  }

  const auto& predicate() const {
    return srcs_[pred_idx_];
  }

protected:

  assertimpl(context* ctx,
             const lnode& cond,
             const std::string& msg,
             const source_location& sloc);

  std::string message_;
  int pred_idx_;
  int cond_idx_;

  friend class context;
};

}
}
