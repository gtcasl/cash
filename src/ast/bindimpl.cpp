#include "bindimpl.h"
#include "proxyimpl.h"
#include "ioport.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

static uint32_t find_port_index(bindportimpl* bindport, const std::vector<lnode>& list) {
  // lookup existing binding  
  for (uint32_t index = 0; index < list.size(); ++index) {
    auto impl = reinterpret_cast<bindportimpl*>(list[index].impl());
    if (impl->ioport().id() == bindport->ioport().id())
      return index;
  }
  return -1;
}

bindimpl::bindimpl(context* ctx, 
                   context* module, 
                   const std::string& name,
                   const source_location& sloc)
  : ioimpl(ctx, type_bind, 0, name, sloc)
  , module_(module) {
  // acquire module instance
  module_->acquire();

  // bind system clock
  auto module_clk = module->sys_clk();
  if (module_clk) {
    auto cd = ctx->current_cd(sloc);
    this->bind_input(cd->clk().impl(), module_clk, sloc);
  }

  // bind system reset
  auto module_reset = module->sys_reset();
  if (module_reset) {
    auto reset = ctx->current_reset(sloc);
    this->bind_input(reset, module_reset, sloc);
  }
}

bindimpl::~bindimpl() {
  // release module instance
  module_->release();
}

lnodeimpl* bindimpl::clone(context*, const clone_map&) const {
  return nullptr;
}

void bindimpl::remove_port(lnodeimpl* port) {
  for (auto it = this->srcs().begin(), end = this->srcs().end(); it != end; ++it) {
    if (it->id() == port->id()) {
      this->remove_src(it - this->srcs().begin());
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

void bindimpl::bind_input(lnodeimpl* src,
                          inputimpl* ioport,
                          const source_location& sloc) {
  assert(src->ctx() == ctx_);
  assert(ioport->ctx() != ctx_);

  // create bind port
  auto input = ctx_->create_node<bindportimpl>(this, src, ioport, sloc);
  ioport->add_bindport(input);

  // add to list
  auto p = find_port_index(input, this->srcs());
  if (p < this->num_srcs()) {
    this->set_src(p, input);
  } else {
    this->add_src(input);
  }
}

void bindimpl::bind_output(lnodeimpl* dst,
                           outputimpl* ioport,
                           const source_location& sloc) {
  assert(dst->ctx() == ctx_);
  assert(ioport->ctx() != ctx_);

  // create bind port
  auto output = ctx_->create_node<bindportimpl>(this, ioport, sloc);
  assert(type_proxy == dst->type());
  reinterpret_cast<proxyimpl*>(dst)->write(0, output, 0, dst->size(), sloc);

  // add to list
  auto p = find_port_index(output, outputs_);
  if (p < outputs_.size()) {
    outputs_[p] = output;
  } else {
    outputs_.push_back(output);
  }
}

void bindimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type();
  out << "(" << module_->name();
  for (auto& src : this->srcs()) {
    out << ", #" << src.id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

bindportimpl::bindportimpl(context* ctx,
                           bindimpl* binding,
                           lnodeimpl* src,
                           inputimpl* ioport,
                           const source_location& sloc)
  : ioimpl(ctx, type_bindin, ioport->size(), ioport->name(), sloc)
  , binding_(binding)
  , ioport_(ioport) {
  binding->acquire();
  this->add_src(src);
}

bindportimpl::bindportimpl(context* ctx,
                           bindimpl* binding,
                           outputimpl* ioport,
                           const source_location& sloc)
  : ioimpl(ctx, type_bindout, ioport->size(), ioport->name(), sloc)
  , binding_(binding)
  , ioport_(ioport) {
  binding->acquire();
  this->add_src(binding);
}

bindportimpl::~bindportimpl() {
  binding_->remove_port(this);
  binding_->release();
}

lnodeimpl* bindportimpl::clone(context*, const clone_map&) const {
  return nullptr;
}

void bindportimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << this->size();
  out << "(";
  for (uint32_t i = 0; i < this->num_srcs(); ++i) {
    if (i)
      out << ", ";
    out << "#" << this->src(i).id();
  }
  if (type_bindout == type_) {
    out << ", $" << ioport_.id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::bindInputNode(const lnode& input, const source_location& sloc) {
  auto ctx = ctx_curr();
  auto binding = ctx->current_binding();
  auto name = stringf("%s.%s", binding->module()->name().c_str(), input.name().c_str());
  auto node = ctx->create_node<proxyimpl>(input.size(), name, sloc);
  binding->bind_input(node, reinterpret_cast<inputimpl*>(input.impl()), sloc);
  return node;
}

lnodeimpl* ch::internal::bindOutputNode(const lnode& output, const source_location& sloc) {
  auto ctx = ctx_curr();
  auto binding = ctx->current_binding();
  auto name = stringf("%s.%s", binding->module()->name().c_str(), output.name().c_str());
  auto node = ctx->create_node<proxyimpl>(output.size(), name, sloc);
  binding->bind_output(node, reinterpret_cast<outputimpl*>(output.impl()), sloc);
  return node;
}
