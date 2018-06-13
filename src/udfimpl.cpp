#include "udfimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udfimpl::udfimpl(context* ctx,
                 lnodetype type,
                 udf_iface* udf,
                 const std::initializer_list<lnode>& srcs,
                 const source_location& sloc)
  : lnodeimpl(ctx, type, udf->output_size(), 0, "", sloc)
  , udf_(udf)
  , udf_srcs_(srcs_) {
  udf->acquire();

  for (auto src : srcs) {
    srcs_.push_back(src);
  }
}

udfimpl::~udfimpl() {
  udf_->release();
}

///////////////////////////////////////////////////////////////////////////////

udfcimpl::udfcimpl(context* ctx,
                   udf_iface* udf,
                   const std::initializer_list<lnode>& srcs,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfc, udf, srcs, sloc)
{}

udfcimpl::~udfcimpl() {}

void udfcimpl::eval() {
  udf_->eval(value_, udf_srcs_);
}

///////////////////////////////////////////////////////////////////////////////

udfsimpl::udfsimpl(context* ctx,
                   udf_iface* udf,
                   const std::initializer_list<lnode>& srcs,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfs, udf, srcs, sloc)
  , enable_idx_(-1)  {
  auto cd = ctx->current_cd(sloc);
  cd_idx_ = this->add_src(-1, cd);

  if (udf->enable() && srcs.size() > udf->inputs_sizes().size()) {
    // the last node is the enable signal
    enable_idx_ = srcs.size() - 1;
  }

  pipe_.resize(udf->delta() - 1, bitvector(this->size()));
}

udfsimpl::~udfsimpl() {}

void udfsimpl::eval() {
  // check clock transition
  auto cd = reinterpret_cast<cdimpl*>(this->cd().impl());
  if (0 == cd->value().word(0))
    return;

  // advance the pipeline
  if (!pipe_.empty()) {
    auto last = pipe_.size() - 1;
    value_ = pipe_[last];
    for (int i = last; i > 0; --i) {
      pipe_[i] = pipe_[i-1];
    }
  }
  // push new entry
  auto& value = pipe_.empty() ? value_ : pipe_[0];
  if (udf_->init() && cd->rst().data().word(0)) {
    udf_->reset(value, udf_srcs_);
  } else {
    int enable = this->has_enable() ? this->enable().data().word(0) : enable_idx_;
    if (enable) {
      udf_->eval(value, udf_srcs_);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createUDFNode(udf_iface* udf,
                                       const std::initializer_list<lnode>& inputs,
                                       const source_location& sloc) {
  return ctx_curr()->create_udf_node(udf, inputs, sloc);
}
