#include "udfimpl.h"
#include "proxyimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udfimpl::udfimpl(context* ctx,
                 lnodetype type,
                 udf_iface* udf,
                 const source_location& sloc,
                 const std::string& name)
  : ioimpl(ctx, type, 0, sloc, name)
  , udf_(udf) {
  udf_->acquire();
}

udfimpl::~udfimpl() {
  udf_->release();
}

void udfimpl::remove_port(lnodeimpl* port) {
  for (auto it = this->srcs().begin(), end = this->srcs().end(); it != end; ++it) {
    if (it->id() == port->id()) {
      this->remove_src(it - this->srcs().begin());
      return;
    }
  }
  for (auto it = inputs_.begin(), end = inputs_.end(); it != end; ++it) {
    if (it->id() == port->id()) {
      inputs_.erase(it);
      return;
    }
  }
  for (auto it = outputs_.begin(), end = outputs_.end(); it != end; ++it) {
    if (it->id() == port->id()) {
      outputs_.erase(it);
      return;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

udfcimpl::udfcimpl(context* ctx,
                   udf_iface* udf,
                   const source_location& sloc,
                   const std::string& name)
  : udfimpl(ctx, type_udfc, udf, sloc, name)
{}

udfcimpl::~udfcimpl() {}

lnodeimpl* udfcimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto udf = ctx->create_node<udfcimpl>(udf_, sloc_, name_);
  for (auto& input : inputs_) {
    auto new_input = reinterpret_cast<udfportimpl*>(cloned_nodes.at(input.id()));
    udf->add_input(new_input);
  }
  return udf;
}

///////////////////////////////////////////////////////////////////////////////

udfsimpl::udfsimpl(context* ctx,
                   udf_iface* udf,
                   lnodeimpl* cd,
                   lnodeimpl* reset,
                   const source_location& sloc,
                   const std::string& name)
  : udfimpl(ctx, type_udfs, udf, sloc, name) {
  cd_idx_ = this->add_src(cd);
  reset_idx_ = this->add_src(reset);
}

udfsimpl::~udfsimpl() {}

lnodeimpl* udfsimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto cd = cloned_nodes.at(this->cd().id());
  auto reset = cloned_nodes.at(this->reset().id());
  auto udf = ctx->create_node<udfsimpl>(udf_, cd, reset, sloc_, name_);
  for (auto& input : inputs_) {
    auto new_input = reinterpret_cast<udfportimpl*>(cloned_nodes.at(input.id()));
    udf->add_input(new_input);
  }
  return udf;
}

///////////////////////////////////////////////////////////////////////////////

udfportimpl::udfportimpl(context* ctx,
                         lnodeimpl* src,
                         const io_value_t& value,
                         const source_location& sloc,
                         const std::string& name)
  : ioportimpl(ctx, type_udfin, src->size(), value, sloc, name)
  , udf_(nullptr) {
  this->add_src(src);
}

udfportimpl::udfportimpl(context* ctx,
                         unsigned size,
                         udfimpl* udf,
                         const io_value_t& value,
                         const source_location& sloc,
                         const std::string& name)
  : ioportimpl(ctx, type_udfout, size, value, sloc, name)
  , udf_(udf) {
  this->add_src(udf);
  udf->acquire();
  udf->add_output(this);
}

udfportimpl::~udfportimpl() {
  if (udf_) {
    udf_->remove_port(this);
    udf_->release();
  }
}

lnodeimpl* udfportimpl::clone(context* ctx, const clone_map& cloned_nodes) const {  
  if (type_ == type_udfin) {
    auto src = reinterpret_cast<udfimpl*>(cloned_nodes.at(this->src(0).id()));
    return ctx->create_node<udfportimpl>(src, value_, sloc_, name_);
  } else {    
    auto udf = reinterpret_cast<udfimpl*>(cloned_nodes.at(udf_->id()));
    return ctx->create_node<udfportimpl>(this->size(), udf, value_, sloc_, name_);
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::createUDFNode(const std::string& name,
                                 bool is_seq,
                                 udf_iface* udf) {
  auto sloc = get_source_location();
  ctx_curr()->create_udf_node(udf, is_seq, name, sloc);
}

lnodeimpl* ch::internal::bindInputNode(system_io_buffer* input,
                                       const sloc_getter&) {
  auto sloc = get_source_location();
  auto ctx  = ctx_curr();
  auto value = smart_ptr<sdata_type>::make(input->size());
  auto src  = ctx->create_node<proxyimpl>(input->size(), sloc, input->name());
  auto node = ctx->create_node<udfportimpl>(src, value, sloc, input->name());
  input->bind(node->value());
  auto udf = ctx->current_udf();
  udf->add_input(node);
  return src;
}

lnodeimpl* ch::internal::bindOutputNode(system_io_buffer* output,
                                        const sloc_getter&) {
  auto sloc = get_source_location();
  auto ctx  = ctx_curr();
  auto udf  = ctx->current_udf();
  auto value = smart_ptr<sdata_type>::make(output->size());
  auto node = ctx->create_node<udfportimpl>(output->size(), udf, value, sloc, output->name());
  output->bind(node->value());
  return node;
}
