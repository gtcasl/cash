#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class assertimpl : public ioimpl {
public:

  auto& cond() const {
    return srcs_[0];
  }

  auto& time() const {
    return srcs_[1];
  }

  const std::string& msg() const {
    return msg_;
  }

  bool has_pred() const {
    return (pred_idx_ != -1);
  }

  auto& pred() const {
    return srcs_[pred_idx_];
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

protected:

  assertimpl(context* ctx,
             lnodeimpl* cond,
             const std::string& msg,
             const source_location& sloc);

  assertimpl(context* ctx,
             lnodeimpl* cond,
             lnodeimpl* pred,
             const std::string& msg,
             const source_location& sloc);

  std::string msg_;
  int pred_idx_;

  friend class context;
};

}
}
