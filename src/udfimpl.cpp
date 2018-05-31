#include "udfimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udfimpl::udfimpl(context* ctx,
                 udf_iface* udf,
                 const std::initializer_list<lnode>& srcs)
  : lnodeimpl(ctx, type_udf, udf->output_size())
  , udf_(udf) {
  for (auto src : srcs) {
    srcs_.push_back(src);
  }
}

udfimpl::~udfimpl() {}

void udfimpl::initialize() {
  udf_->initialize();
}

void udfimpl::reset() {
  udf_->reset();
}

void udfimpl::eval() {
  udf_->eval(value_, srcs_);
}

///////////////////////////////////////////////////////////////////////////////

delayed_udfimpl::delayed_udfimpl(context* ctx,
                                 udf_iface* udf,
                                 const std::initializer_list<lnode>& srcs)
  : udfimpl(ctx, udf, srcs)
  , cd_idx_(-1)
  , wenable_idx_(-1) {

  values_.resize(udf->delta() - 1, bitvector(this->size()));

  if (udf->enable()) {
    assert(srcs_.size() != 0);
    wenable_idx_ = srcs_.size() - 1;
  }

  auto cd = ctx->current_cd();
  cd->add_reg(this);
  cd_idx_ = srcs_.size();
  srcs_.push_back(cd);
}

delayed_udfimpl::~delayed_udfimpl() {}

void delayed_udfimpl::tick() {
  if (values_.empty()) {
    value_ = q_next_;
  } else {
    auto last = values_.size() - 1;
    value_ = values_[last];
    for (int i = last; i > 0; --i) {
      values_[i] = values_[i-1];
    }
    values_[0] = q_next_;
  }
}

void delayed_udfimpl::eval() {
  if (wenable_idx_ == -1 || srcs_[wenable_idx_].data().word(0)) {
    udf_->eval(q_next_, srcs_);
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::create_udf_node(udf_iface* udf, const std::initializer_list<lnode>& inputs) {
  return ctx_curr()->create_udf_node(udf, inputs);
}
