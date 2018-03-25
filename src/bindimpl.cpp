#include "bindimpl.h"
#include "context.h"

using namespace ch::internal;

static void add_port(bindportimpl* bindport, std::vector<lnode>& list) {
  // lookup existing binding
  size_t index = 0;
  for (;index < list.size(); ++index) {
    auto impl = dynamic_cast<bindportimpl*>(list[index].get_impl());
    if (impl->get_ioport().get_id() == bindport->get_ioport().get_id())
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
  auto module_clk = module->get_default_clk();
  if (module_clk) {
    this->bind_input(ctx->get_clk(), module_clk);
  }

  // bind default reset
  auto module_reset = module->get_default_reset();
  if (module_reset) {
    this->bind_input(ctx->get_reset(), module_reset);
  }
}

bindimpl::~bindimpl() {
  // detach outputs
  while (!outputs_.empty()) {
    dynamic_cast<bindportimpl*>(outputs_.front().get_impl())->detach();
  }

  // release module instance
  module_->release();
}

void bindimpl::remove_output(bindportimpl* output) {
  for (auto it = outputs_.begin(), end = outputs_.end(); it != end; ++it) {
    if (it->get_id() == output->get_id()) {
      outputs_.erase(it);
      break;
    }
  }
}

void bindimpl::bind_input(const lnode& src, const lnode& ioport) {
  assert(src.get_ctx() == ctx_);
  assert(ioport.get_ctx() != ctx_);

  // create bind port
  auto bindport(ctx_->createNode<bindportimpl>(src, ioport));
  dynamic_cast<inputimpl*>(ioport.get_impl())->bind(bindport);

  // add to list
  add_port(bindport, srcs_);
}

void bindimpl::bind_output(const lnode& dst, const lnode& ioport) {
  assert(dst.get_ctx() == ctx_);
  assert(ioport.get_ctx() != ctx_);

  // create bind port
  auto bindport(ctx_->createNode<bindportimpl>(this, ioport));
  const_cast<lnode&>(dst).write(0, bindport, 0, dst.get_size());

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
  out << "#" << id_ << " <- " << this->get_type();
  out << "(" << module_->get_name();
  for (auto& src : srcs_) {
    out << ", #" << src.get_id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

bindportimpl::bindportimpl(context* ctx, const lnode& src, const lnode& ioport)
  : ioimpl(ctx, type_bindport, ioport.get_size())
  , ioport_(ioport)
  , tick_(~0ull) {
  srcs_.push_back(src);
  is_output_ = (dynamic_cast<outputimpl*>(ioport.get_impl()) != nullptr);
  name_ = is_output_ ? "bindout" : "bindin";
}

bindportimpl::~bindportimpl() {
  this->detach();
}

void bindportimpl::detach() {
  if (is_output_) {
    if (!srcs_[0].is_empty()) {
      dynamic_cast<bindimpl*>(srcs_[0].get_impl())->remove_output(this);
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
  out << "#" << id_ << " <- " << (is_output_ ? "bindout" : "bindin") << value_.get_size();
  out << "(#" << srcs_[0].get_id() << ", $" << ioport_.get_id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}


