#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class assertimpl : public ioimpl {
public:

  auto& cond() const {
    return this->src(0);
  }

  auto& time() const {
    return this->src(1);
  }

  const std::string& message() const {
    return message_;
  }

  bool has_pred() const {
    return (pred_idx_ != -1);
  }

  auto& pred() const {
    return this->src(pred_idx_);
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

protected:

  assertimpl(context* ctx,
             lnodeimpl* cond,
             const std::string& message,
             const source_location& sloc);

  assertimpl(context* ctx,
             lnodeimpl* cond,
             lnodeimpl* pred,
             const std::string& message,
             const source_location& sloc);

  std::string message_;
  int pred_idx_;

  friend class context;
};

}
}
