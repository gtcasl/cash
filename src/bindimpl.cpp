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

bindimpl::bindimpl(context* ctx, context* module)
  : ioimpl(ctx, type_bind, 0)
  , module_(module)
  , tick_(~0ull) {
  // acquire module instance
  module_->acquire();

  // bind default clock
  auto module_clk = module->default_clk();
  if (module_clk) {
    auto cd = ctx->current_cd();
    this->bind_input(cd->clock(), module_clk);
  }

  // bind default reset
  auto module_reset = module->default_reset();
  if (module_reset) {
    auto cd = ctx->current_cd();
    this->bind_input(cd->reset(), module_reset);
  }
}

bindimpl::~bindimpl() {
  // detach outputs
  while (!outputs_.empty()) {
    reinterpret_cast<bindportimpl*>(outputs_.front().impl())->detach();
  }

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

void bindimpl::bind_input(const lnode& src, const lnode& ioport) {
  assert(src.ctx() == ctx_);
  assert(ioport.ctx() != ctx_);

  // create bind port
  auto bindport(ctx_->create_node<bindportimpl>(src, ioport));
  reinterpret_cast<inputimpl*>(ioport.impl())->bind(bindport);

  // add to list
  add_port(bindport, srcs_);
}

void bindimpl::bind_output(const lnode& dst, const lnode& ioport) {
  assert(dst.ctx() == ctx_);
  assert(ioport.ctx() != ctx_);

  // create bind port
  auto bindport(ctx_->create_node<bindportimpl>(this, ioport));
  const_cast<lnode&>(dst).write(0, bindport, 0, dst.size());

  // add to list
  add_port(bindport, outputs_);
}

void bindimpl::tick(ch_tick t) {
  module_->tick(t);
}

void bindimpl::tick_next(ch_tick t) {
  module_->tick_next(t);
}

const bitvector& bindimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    module_->eval(t);
  }
  return value_;
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

bindportimpl::bindportimpl(context* ctx, const lnode& src, const lnode& ioport)
  : ioimpl(ctx, type_bindport, ioport.size())
  , ioport_(ioport)
  , tick_(~0ull) {
  srcs_.push_back(src);
  is_output_ = (type_output == ioport.impl()->type());
  name_ = is_output_ ? "bindout" : "bindin";
}

bindportimpl::~bindportimpl() {
  this->detach();
}

void bindportimpl::detach() {
  if (is_output_) {
    if (!srcs_[0].empty()) {
      reinterpret_cast<bindimpl*>(srcs_[0].impl())->remove_output(this);
      srcs_[0].clear();
    }
  }
}

const bitvector& bindportimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;    
    value_ = is_output_ ? ioport_.eval(t) : srcs_[0].eval(t);
  }
  return value_;
}

void bindportimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << (is_output_ ? "bindout" : "bindin") << value_.size();
  out << "(#" << srcs_[0].id() << ", $" << ioport_.id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}


