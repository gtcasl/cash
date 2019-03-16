#include "bindimpl.h"
#include "ioport.h"
#include "context.h"

using namespace ch::internal;

static void add_port(bindportimpl* bindport, std::vector<lnode>& list) {
  // lookup existing binding
  size_t index = 0;
  for (;index < list.size(); ++index) {
    auto impl = reinterpret_cast<bindportimpl*>(list[index].impl());
    if (impl->ioport().id() == bindport->ioport().id())
      break;
  }

  // add to list
  if (index < list.size()) {
    list[index] = bindport;
  } else {
    list.push_back(bindport);
  }
}

bindimpl::bindimpl(context* ctx, context* module, const source_location& sloc)
  : ioimpl(ctx, type_bind, 0, sloc, module->name())
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

void bindimpl::remove_port(bindportimpl* port) {
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
  add_port(input, this->srcs());
}

void bindimpl::bind_output(lnodeimpl* dst,
                           outputimpl* ioport,
                           const source_location& sloc) {
  assert(dst->ctx() == ctx_);
  assert(ioport->ctx() != ctx_);

  // create bind port
  auto output = ctx_->create_node<bindportimpl>(this, ioport, sloc);
  dst->write(0, output, 0, dst->size());

  // add to list
  add_port(output, outputs_);
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
  : ioimpl(ctx, type_bindin, ioport->size(), sloc, "")
  , binding_(binding)
  , ioport_(ioport) {
  binding->acquire();
  this->add_src(src);
}

bindportimpl::bindportimpl(context* ctx,
                           bindimpl* binding,
                           outputimpl* ioport,
                           const source_location& sloc)
  : ioimpl(ctx, type_bindout, ioport->size(), sloc, "")
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
  if (type_bindout == type_) {
    out << "#" << ioport_.id() << ", ";
  }
  for (uint32_t i = 0; i < this->srcs().size(); ++i) {
    if (i)
      out << ", ";
    out << "#" << this->src(i).id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bindInput(const lnode& src, const lnode& input) {
  auto sloc = get_source_location();
  auto ctx = src.impl()->ctx();
  auto binding = ctx->current_binding();  
  binding->bind_input(src.impl(), reinterpret_cast<inputimpl*>(input.impl()), sloc);
}

void ch::internal::bindOutput(const lnode& dst, const lnode& output) {
  auto sloc = get_source_location();
  auto ctx = dst.impl()->ctx();
  auto binding = ctx->current_binding();
  binding->bind_output(dst.impl(), reinterpret_cast<outputimpl*>(output.impl()), sloc);
}
