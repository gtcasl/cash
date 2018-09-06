#include "udfimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udfimpl::udfimpl(context* ctx,
                 lnodetype type,
                 udf_iface* udf,
                 const std::initializer_list<lnode>& srcs,
                 const source_location& sloc)
  : lnodeimpl(ctx, type, udf->output_size(), sloc)
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

void udfcimpl::eval() {
  udf_->eval(data_, udf_srcs_);
}

///////////////////////////////////////////////////////////////////////////////

udfsimpl::udfsimpl(context* ctx,
                   udf_iface* udf,
                   const std::initializer_list<lnode>& srcs,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfs, udf, srcs, sloc)
  , cd_idx_(-1)
  , reset_idx_(-1) {
  auto cd = ctx->current_cd(sloc);
  cd_idx_ = this->add_src(cd);
  if (udf->has_init()) {
    auto reset = ctx->current_reset(sloc);
    reset_idx_ = this->add_src(reset);
  }
  pipe_.resize(udf->delta() - 1, bitvector(this->size()));
}

void udfsimpl::eval() {
  // check clock transition
  auto cd = reinterpret_cast<cdimpl*>(this->cd().impl());
  if (!static_cast<bool>(cd->data()))
    return;

  bitvector* value = &data_;

  // advance the pipeline
  if (!pipe_.empty()) {
    auto last = pipe_.size() - 1;
    data_ = pipe_[last];
    for (int i = last; i > 0; --i) {
      pipe_[i] = pipe_[i-1];
    }
    value = &pipe_[0];
  }

  // push new entry
  if (this->has_init() && static_cast<bool>(this->reset().data())) {
    udf_->reset(*value, udf_srcs_);
  } else {
    udf_->eval(*value, udf_srcs_);
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createUDFNode(udf_iface* udf,
                                       const std::initializer_list<lnode>& inputs,
                                       const source_location& sloc) {
  return ctx_curr()->create_udf_node(udf, inputs, sloc);
}
