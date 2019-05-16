#include "udfimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udf_obj::udf_obj(uint32_t id,
                     const std::string& name,
                     bool is_seq,
                     uint32_t output_size,
                     const std::initializer_list<uint32_t>& inputs_size,
                     udf_base* impl)
  : id_(id)
  , name_(name)
  , is_managed_(false)
  , is_seq_(is_seq)
  , output_size_(output_size)
  , inputs_size_(inputs_size)
  , impl_(impl) {
  impl_->acquire();
}

udf_obj::~udf_obj() {
  if (impl_) {
    impl_->release();
    if (is_managed_) {
      destroyUDF(id_);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

udfimpl::udfimpl(context* ctx,
                 lnodetype type,
                 udf_obj* udf,
                 const std::vector<lnode>& srcs,
                 const source_location& sloc)
  : ioimpl(ctx, type, udf->output_size(), sloc, udf->name())
  , udf_(udf) {
  udf->acquire();
  for (auto src : srcs) {
    this->add_src(src);
  }
}

udfimpl::~udfimpl() {
  udf_->release();
}

///////////////////////////////////////////////////////////////////////////////

udfcimpl::udfcimpl(context* ctx,
                   udf_obj* udf,
                   const std::vector<lnode>& srcs,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfc, udf, srcs, sloc)
{}

lnodeimpl* udfcimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  std::vector<lnode> srcs;
  srcs.resize(udf_->inputs_size().size());
  for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
    srcs[i] = cloned_nodes.at(this->src(i).id());
  }
  return ctx->create_node<udfcimpl>(udf_, srcs, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

udfsimpl::udfsimpl(context* ctx,
                   udf_obj* udf,
                   lnodeimpl* cd,
                   lnodeimpl* reset,
                   const std::vector<lnode>& srcs,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfs, udf, srcs, sloc) {
  cd_idx_ = this->add_src(cd);
  reset_idx_ = this->add_src(reset);
}

lnodeimpl* udfsimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  std::vector<lnode> srcs;
  srcs.resize(udf_->inputs_size().size());
  for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
    srcs[i] = cloned_nodes.at(this->src(i).id());
  }
  auto cd = cloned_nodes.at(this->cd().id());
  auto reset = cloned_nodes.at(this->reset().id());
  return ctx->create_node<udfsimpl>(udf_, cd, reset, srcs, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

udfimpl2::udfimpl2(context* ctx,
                   lnodetype type,
                   udf_iface* udf,
                   const std::vector<lnode>& srcs,
                   const source_location& sloc)
  : ioimpl(ctx, type, 0, sloc, "") {
  //--
}

udfimpl2::~udfimpl2() {}

void udfimpl2::remove_port(udfportimpl* output) {
  //--
}

///////////////////////////////////////////////////////////////////////////////

udfportimpl::udfportimpl(context* ctx,
                         lnodeimpl* src,
                         udfimpl2* udf,
                         const source_location& sloc)
  : ioimpl(ctx, type_udfin, src->size(), sloc, "")
  , udf_(udf) {
  udf->acquire();
  this->add_src(src);
}

udfportimpl::udfportimpl(context* ctx,
                         unsigned size,
                         udfimpl2* udf,
                         const source_location& sloc)
  : ioimpl(ctx, type_udfout, size, sloc, "")
  , udf_(udf) {
  udf->acquire();
  this->add_src(udf);
}

udfportimpl::~udfportimpl() {
  udf_->remove_port(this);
  udf_->release();
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createUDFNode(refcounted* handle, const std::vector<lnode>& inputs) {
  auto udf = reinterpret_cast<udf_obj*>(handle);
  auto sloc = get_source_location();
  return ctx_curr()->create_udf_node(udf, inputs, sloc);
}

lnodeimpl* ch::internal::createInputNode(const system_io_buffer* buffer,
                                         const sloc_getter&) {
  auto sloc = get_source_location();
  auto node = ctx_curr()->create_udf_input(buffer->size(), buffer->name(), sloc);
  return node;
}

lnodeimpl* ch::internal::createOutputNode(const system_io_buffer* buffer,
                                          const sloc_getter&) {
  auto sloc = get_source_location();
  auto node = ctx_curr()->create_udf_output(buffer->size(), buffer->name(), sloc);
  return node;
}
