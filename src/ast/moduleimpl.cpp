#include "moduleimpl.h"
#include "proxyimpl.h"
#include "ioport.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

static uint32_t find_port_index(moduleportimpl* port, const std::vector<lnode>& list) {
  // lookup existing binding  
  for (uint32_t index = 0; index < list.size(); ++index) {
    auto impl = reinterpret_cast<moduleportimpl*>(list[index].impl());
    if (impl->ioport().id() == port->ioport().id())
      return index;
  }
  return -1;
}

moduleimpl::moduleimpl(context* ctx, 
                       context* target, 
                       const std::string& name,
                       const source_location& sloc)
  : ioimpl(ctx, type_module, 0, name, sloc)
  , target_(target) {
  // acquire module instance
  target->acquire();

  // bind system clock
  auto module_clk = target->sys_clk();
  if (module_clk) {
    auto cd = ctx->current_cd(sloc);
    this->bind_input(cd->clk().impl(), module_clk, sloc);
  }

  // bind system reset
  auto module_reset = target->sys_reset();
  if (module_reset) {
    auto reset = ctx->current_reset(sloc);
    this->bind_input(reset, module_reset, sloc);
  }
}

moduleimpl::~moduleimpl() {
  // release module instance
  target_->release();
}

lnodeimpl* moduleimpl::clone(context*, const clone_map&) const {
  return nullptr;
}

void moduleimpl::remove_port(lnodeimpl* port) {
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

void moduleimpl::bind_input(lnodeimpl* src,
                          inputimpl* ioport,
                          const source_location& sloc) {
  assert(src->ctx() == ctx_);
  assert(ioport->ctx() != ctx_);

  // create port
  auto input = ctx_->create_node<moduleportimpl>(this, src, ioport, sloc);
  ioport->bind(input);

  // add to list
  auto p = find_port_index(input, this->srcs());
  if (p < this->num_srcs()) {
    this->set_src(p, input);
  } else {
    this->add_src(input);
  }
}

void moduleimpl::bind_output(lnodeimpl* dst,
                           outputimpl* ioport,
                           const source_location& sloc) {
  assert(dst->ctx() == ctx_);
  assert(ioport->ctx() != ctx_);

  // create port
  auto output = ctx_->create_node<moduleportimpl>(this, ioport, sloc);
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

void moduleimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type();
  out << "(" << target_->name();
  for (auto& src : this->srcs()) {
    out << ", #" << src.id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

moduleportimpl::moduleportimpl(context* ctx,
                               moduleimpl* module,
                               lnodeimpl* src,
                               inputimpl* ioport,
                               const source_location& sloc)
  : ioimpl(ctx, type_modpin, ioport->size(), ioport->name(), sloc)
  , module_(module)
  , ioport_(ioport) {
  module->acquire();
  this->add_src(src);
}

moduleportimpl::moduleportimpl(context* ctx,
                               moduleimpl* module,
                               outputimpl* ioport,
                               const source_location& sloc)
  : ioimpl(ctx, type_modpout, ioport->size(), ioport->name(), sloc)
  , module_(module)
  , ioport_(ioport) {
  module->acquire();
  this->add_src(module);
}

moduleportimpl::~moduleportimpl() {
  module_->remove_port(this);
  module_->release();
}

lnodeimpl* moduleportimpl::clone(context*, const clone_map&) const {
  return nullptr;
}

void moduleportimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << this->size();
  out << "(";
  for (uint32_t i = 0; i < this->num_srcs(); ++i) {
    if (i)
      out << ", ";
    out << "#" << this->src(i).id();
  }
  if (type_modpout == type_) {
    out << ", $" << ioport_.id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::bindInputNode(const lnode& input, const source_location& sloc) {
  auto ctx = ctx_curr();
  auto module = ctx->current_module();
  auto name = stringf("%s.%s", module->target()->name().c_str(), input.name().c_str());
  auto node = ctx->create_node<proxyimpl>(input.size(), name, sloc);
  module->bind_input(node, reinterpret_cast<inputimpl*>(input.impl()), sloc);
  return node;
}

lnodeimpl* ch::internal::bindOutputNode(const lnode& output, const source_location& sloc) {
  auto ctx = ctx_curr();
  auto module = ctx->current_module();
  auto name = stringf("%s.%s", module->target()->name().c_str(), output.name().c_str());
  auto node = ctx->create_node<proxyimpl>(output.size(), name, sloc);
  module->bind_output(node, reinterpret_cast<outputimpl*>(output.impl()), sloc);
  return node;
}
