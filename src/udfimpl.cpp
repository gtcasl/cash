#include "udfimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udfimpl::udfimpl(context* ctx,
                 udf_iface* udf,
                 const std::initializer_list<lnode>& srcs)
  : lnodeimpl(ctx, type_udfc, udf->output_size())
  , udf_(udf) {
  udf->acquire();

  for (auto src : srcs) {
    srcs_.push_back(src);
  }
}

udfimpl::~udfimpl() {
  udf_->release();
}

void udfimpl::initialize() {
  for (auto src : srcs_) {
    udf_srcs_.push_back(&src.data());
  }
  udf_->initialize();
}

void udfimpl::eval() {
  udf_->eval(&value_, udf_srcs_);
}

///////////////////////////////////////////////////////////////////////////////

delayed_udfimpl::delayed_udfimpl(context* ctx,
                                 udf_iface* udf,
                                 const std::initializer_list<lnode>& srcs)
  : lnodeimpl(ctx, type_udfs, udf->output_size())
  , udf_(udf)
  , wenable_idx_(-1)  {
  udf->acquire();

  auto cd = ctx->current_cd();
  srcs_.push_back(cd);

  for (auto src : srcs) {
    srcs_.push_back(src);
  }

  if (udf->enable() && srcs.size() > udf->inputs_sizes().size()) {
    // the last node is the enable signal
    wenable_idx_ = srcs_.size() - 1;
  }

  values_.resize(udf->delta() - 1, bitvector(this->size()));
}

delayed_udfimpl::~delayed_udfimpl() {
  udf_->release();
}

void delayed_udfimpl::initialize() {
  // do not include the clock and enable signals
  uint32_t n = this->has_wenable() ? wenable_idx_ : srcs_.size();
  for (uint32_t i = 1; i < n; ++i) {
    udf_srcs_.push_back(&srcs_[i].data());
  }
  udf_->initialize();  
}

void delayed_udfimpl::eval() {
  auto cd = reinterpret_cast<cdimpl*>(this->cd().impl());
  if (cd->value().word(0)) {
    // advance the pipeline
    if (!values_.empty()) {
      auto last = values_.size() - 1;
      value_ = values_[last];
      for (int i = last; i > 0; --i) {
        values_[i] = values_[i-1];
      }
    }
    // push new entry
    auto& value = values_.empty() ? value_ : values_[0];
    if (udf_->init() && cd->rst().data().word(0)) {
      udf_->reset(&value, udf_srcs_);
    } else {
      int wenable = this->has_wenable() ? this->wenable().data().word(0) : wenable_idx_;
      if (wenable) {
        udf_->eval(&value, udf_srcs_);
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createUDFNode(udf_iface* udf, const std::initializer_list<lnode>& inputs) {
  return ctx_curr()->create_udf_node(udf, inputs);
}
