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
  : ioimpl(ctx, type_bind, 0, sloc)
  , module_(module) {
  // acquire module instance
  module_->acquire();

  // bind default clock
  auto module_clk = module->default_clk();
  if (module_clk) {
    auto cd = ctx->current_cd(sloc);
    this->bind_input(cd->clk(), module_clk, sloc);
  }

  // bind default reset
  auto module_reset = module->default_reset();
  if (module_reset) {
    auto reset = ctx->current_reset(sloc);
    this->bind_input(reset, module_reset, sloc);
  }
}

bindimpl::~bindimpl() {
  // release module instance
  module_->release();
}

void bindimpl::remove_port(bindportimpl* port) {
  for (auto it = srcs_.begin(), end = srcs_.end(); it != end; ++it) {
    if (it->id() == port->id()) {
      srcs_.erase(it);
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

void bindimpl::bind_input(const lnode& src,
                          const lnode& ioport,
                          const source_location& sloc) {
  assert(src.impl()->ctx() == ctx_);
  assert(ioport.impl()->ctx() != ctx_);

  // create bind port
  auto input = ctx_->create_node<bindportimpl>(this, src, ioport, sloc);
  reinterpret_cast<inputimpl*>(ioport.impl())->bind(input);

  // add to list
  add_port(input, srcs_);
}

void bindimpl::bind_output(const lnode& dst,
                           const lnode& ioport,
                           const source_location& sloc) {
  assert(dst.impl()->ctx() == ctx_);
  assert(ioport.impl()->ctx() != ctx_);

  // create bind port
  auto output = ctx_->create_node<bindportimpl>(this, ioport, sloc);
  const_cast<lnode&>(dst).write(0, output, 0, dst.size(), sloc);

  // add to list
  add_port(output, outputs_);
}

void bindimpl::eval() {}

void bindimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->type();
  out << "(" << module_->name();
  for (auto& src : srcs_) {
    out << ", #" << src.id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

bindportimpl::bindportimpl(context* ctx,
                           bindimpl* binding,
                           const lnode& src,
                           const lnode& ioport,
                           const source_location& sloc)
  : ioimpl(ctx, type_bindin, ioport.size(), sloc)
  , binding_(binding)
  , ioport_(ioport)
  , words_(nullptr) {
  binding->acquire();
  srcs_.push_back(src);
}

bindportimpl::bindportimpl(context* ctx,
                           bindimpl* binding,
                           const lnode& ioport,
                           const source_location& sloc)
  : ioimpl(ctx, type_bindout, ioport.size(), sloc)
  , binding_(binding)
  , ioport_(ioport)
  , words_(nullptr) {
  binding->acquire();
  srcs_.push_back(binding);
}

bindportimpl::~bindportimpl() {
  if (words_) {
    data_.words(words_);
  }
  binding_->remove_port(this);
  binding_->release();
}

void bindportimpl::initialize() {
  if (words_) {
    data_.words(words_);
  }
  auto& src_node = (type_bindin == type_) ? srcs_[0] : ioport_;
  words_ = data_.words(src_node.data().words());
}

void bindportimpl::eval() {}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bindInput(const lnode& src,
                             const lnode& input,
                             const source_location& sloc) {
  auto ctx = src.impl()->ctx();
  auto binding = ctx->find_binding(input.impl()->ctx(), sloc);
  binding->bind_input(src, input, sloc);
}

void ch::internal::bindOutput(const lnode& dst,
                              const lnode& output,
                              const source_location& sloc) {
  auto ctx = dst.impl()->ctx();
  auto binding = ctx->find_binding(output.impl()->ctx(), sloc);
  binding->bind_output(dst, output, sloc);
}
