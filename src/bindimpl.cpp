#include "bindimpl.h"
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

void bindimpl::remove_output(bindportimpl* output) {
  for (auto it = outputs_.begin(), end = outputs_.end(); it != end; ++it) {
    if (it->id() == output->id()) {
      outputs_.erase(it);
      break;
    }
  }
}

void bindimpl::bind_input(const lnode& src,
                          const lnode& ioport,
                          const source_location& sloc) {
  assert(src.impl()->ctx() == ctx_);
  assert(ioport.impl()->ctx() != ctx_);

  // create bind port
  auto input = ctx_->create_node<bindinimpl>(this, src, ioport, sloc);
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
  auto output = ctx_->create_node<bindoutimpl>(this, ioport, sloc);
  const_cast<lnode&>(dst).write(0, output, 0, dst.size(), sloc);

  // add to list
  add_port(output, outputs_);
}

void bindimpl::eval() {
  //--
}

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
                           lnodetype type,
                           bindimpl* binding,
                           const lnode& ioport,
                           const source_location& sloc)
  : ioimpl(ctx, type, ioport.size(), sloc)
  , binding_(binding)
  , ioport_(ioport) {
  binding->acquire();
}

bindportimpl::~bindportimpl() {
  binding_->release();
}

///////////////////////////////////////////////////////////////////////////////

bindinimpl::bindinimpl(context* ctx,
                       bindimpl* binding,
                       const lnode& src,
                       const lnode& ioport,
                       const source_location& sloc)
  : bindportimpl(ctx, type_bindin, binding, ioport, sloc)
  , words_(nullptr) {
  srcs_.push_back(src);
}

bindinimpl::~bindinimpl() {
  if (words_) {
    value_.words(words_);
  }
}

void bindinimpl::initialize() {
  if (words_) {
    value_.words(words_);
  }
  words_ = value_.words(srcs_[0].data().words());
}

void bindinimpl::eval() {
  //--
}

void bindinimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << "bindin" << value_.size();
  out << "(#" << src(0).id() << ", $" << ioport_.id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

bindoutimpl::bindoutimpl(context* ctx,
                         bindimpl* binding,
                         const lnode& ioport,
                         const source_location& sloc)
  : bindportimpl(ctx, type_bindout, binding, ioport, sloc)
  , words_(nullptr) {
  srcs_.push_back(binding); // make binding a source
}

bindoutimpl::~bindoutimpl() {
  binding_->remove_output(this);
  if (words_) {
    value_.words(words_);
  }
}

void bindoutimpl::initialize() {
  if (words_) {
    value_.words(words_);
  }
  words_ = value_.words(ioport_.data().words());
}

void bindoutimpl::eval() {
  //--
}

void bindoutimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << "bindout" << value_.size();
  out << "(#" << binding_->id() << ", $" << ioport_.id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}
