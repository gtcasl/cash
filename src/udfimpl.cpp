#include "udfimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udfimpl::udfimpl(context* ctx,
                 lnodetype type,
                 udf_iface* udf,
                 const std::vector<lnode>& srcs,
                 const source_location& sloc)
  : lnodeimpl(ctx, type, udf->output_size(), sloc)
  , udf_(udf) {
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
                   const std::vector<lnode>& srcs,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfc, udf, srcs, sloc)
{}

lnodeimpl* udfcimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  std::vector<lnode> srcs;
  srcs.resize(udf_->inputs_size().size());
  for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
    srcs[i] = cloned_nodes.at(this->src(i).id());
  }
  return ctx->create_node<udfcimpl>(udf_, srcs, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

udfsimpl::udfsimpl(context* ctx,
                   udf_iface* udf,
                   const std::vector<lnode>& srcs,
                   lnodeimpl* cd,
                   lnodeimpl* reset,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfs, udf, srcs, sloc)
  , cd_idx_(-1)
  , reset_idx_(-1) {
  if (nullptr == cd) {
    cd = ctx->current_cd(sloc);
  }
  cd_idx_ = this->add_src(cd);
  if (udf->has_init_data()) {
    if (nullptr == reset) {
      reset = ctx->current_reset(sloc);
    }
    reset_idx_ = this->add_src(reset);
  }  
}

lnodeimpl* udfsimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  std::vector<lnode> srcs;
  srcs.resize(udf_->inputs_size().size());
  for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
    srcs[i] = cloned_nodes.at(this->src(i).id());
  }

  auto cd = cloned_nodes.at(this->cd().id());

  lnodeimpl* reset = nullptr;
  if (this->has_init_data()) {
    reset = cloned_nodes.at(this->reset().id());
  }

  return ctx->create_node<udfsimpl>(udf_, srcs, cd, reset, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createUDFNode(udf_iface* udf,
                                       const std::vector<lnode>& inputs,
                                       const source_location& sloc) {
  return ctx_curr()->create_udf_node(udf, inputs, sloc);
}
