#include "udf.h"
#include "ioport.h"
#include "udfimpl.h"
#include "proxyimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

udf_iface::udf_iface() {}

udf_iface::~udf_iface() {}

///////////////////////////////////////////////////////////////////////////////

udfimpl::udfimpl(context* ctx,
                 lnodetype type,
                 udf_iface* udf,
                 const std::string& name,
                 const source_location& sloc)
  : ioimpl(ctx, type, 0, name, sloc)
  , udf_(udf) {
  udf_->acquire();
}

udfimpl::~udfimpl() {
  udf_->release();
}

void udfimpl::remove_port(lnodeimpl* port) {
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
  for (auto it = this->srcs().begin(), end = this->srcs().end(); it != end; ++it) {
    if (it->id() == port->id()) {
      this->remove_src(it - this->srcs().begin());
      return;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

udfcimpl::udfcimpl(context* ctx,
                   udf_iface* udf,
                   const std::string& name,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfc, udf, name, sloc)
{}

udfcimpl::~udfcimpl() {}

lnodeimpl* udfcimpl::clone(context* ctx, const clone_map&) const {
  return ctx->create_node<udfcimpl>(udf_, name_, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

udfsimpl::udfsimpl(context* ctx,
                   udf_iface* udf,
                   lnodeimpl* cd,
                   lnodeimpl* reset,
                   const std::string& name,
                   const source_location& sloc)
  : udfimpl(ctx, type_udfs, udf, name, sloc) {
  cd_idx_ = this->add_src(cd);
  reset_idx_ = this->add_src(reset);
}

udfsimpl::~udfsimpl() {}

lnodeimpl* udfsimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto cd = cloned_nodes.at(this->cd().id());
  auto reset = cloned_nodes.at(this->reset().id());
  return ctx->create_node<udfsimpl>(udf_, cd, reset, name_, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

udfportimpl::udfportimpl(context* ctx,
                         unsigned size,
                         lnodeimpl* src,
                         udfimpl* udf,
                         const io_value_t& value,
                         const std::string& name,
                         const source_location& sloc)
  : ioportimpl(ctx, type_udfin, size, value, name, sloc)
  , udf_(udf) {
  this->add_src(src);
  udf->acquire();  
  udf->add_input(this);
}

udfportimpl::udfportimpl(context* ctx,
                         unsigned size,
                         udfimpl* udf,
                         const io_value_t& value,
                         const std::string& name,
                         const source_location& sloc)
  : ioportimpl(ctx, type_udfout, size, value, name, sloc)
  , udf_(udf) {
  this->add_src(udf);
  udf->acquire();
  udf->add_output(this);
}

udfportimpl::~udfportimpl() {
  udf_->remove_port(this);
  udf_->release();
}

lnodeimpl* udfportimpl::clone(context* ctx, const clone_map& cloned_nodes) const {  
  auto udf = reinterpret_cast<udfimpl*>(cloned_nodes.at(udf_->id()));
  if (type_ == type_udfin) {
    auto src = reinterpret_cast<udfimpl*>(cloned_nodes.at(this->src(0).id()));
    return ctx->create_node<udfportimpl>(this->size(), src, udf, value_, name_, sloc_);
  } else {        
    return ctx->create_node<udfportimpl>(this->size(), udf, value_, name_, sloc_);
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::createUDFNode(const std::string& name,
                                 bool is_seq,
                                 udf_iface* udf) {
  auto sloc = get_source_location();
  ctx_curr()->create_udf_node(udf, is_seq, name, sloc);
}

lnodeimpl* ch::internal::bindInputNode(system_io_buffer* input) {
  CH_API_ENTRY(2);
  auto sloc = get_source_location();
  auto ctx  = ctx_curr();
  auto udf  = ctx->current_udf();
  auto value = smart_ptr<sdata_type>::make(input->size());
  auto src  = ctx->create_node<proxyimpl>(input->size(), input->name(), sloc);
  auto node = ctx->create_node<udfportimpl>(input->size(), src, udf, value, input->name(), sloc);
  input->bind(node->value());  
  return src;
}

lnodeimpl* ch::internal::bindOutputNode(system_io_buffer* output) {
  CH_API_ENTRY(2);
  auto sloc = get_source_location();
  auto ctx  = ctx_curr();
  auto udf  = ctx->current_udf();
  auto value = smart_ptr<sdata_type>::make(output->size());
  auto node = ctx->create_node<udfportimpl>(output->size(), udf, value, output->name(), sloc);
  output->bind(node->value());
  return node;
}
