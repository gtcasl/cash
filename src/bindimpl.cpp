#include "bindimpl.h"
#include "context.h"

using namespace ch::internal;

bindimpl::bindimpl(context* ctx, context* module)
  : ioimpl(ctx, type_bind, 0)
  , module_(module)
  , tick_(~0ull) {
  module_->acquire();
  srcs_.resize(module->get_inputs().size());
  outputs_.resize(module->get_outputs().size());
}

bindimpl::~bindimpl() {
  module_->release();
}

void bindimpl::bind_input(const lnode& src, const lnode& ioport) {
  assert(src.get_ctx() == ctx_);
  assert(ioport.get_ctx() != ctx_);
  // get input index
  auto index = find_distance(module_->get_inputs().begin(),
                             module_->get_inputs().end(),
                             ioport);
  assert(index != -1);

  // create bind port
  lnode bindport(ctx_->createNode<bindportimpl>(src, ioport));
  dynamic_cast<inputimpl*>(ioport.get_impl())->bind(bindport);

  // add to list
  srcs_[index] = bindport;
}

void bindimpl::bind_output(const lnode& dst, const lnode& ioport) {
  assert(dst.get_ctx() == ctx_);
  assert(ioport.get_ctx() != ctx_);
  // get output index
  auto index = find_distance(module_->get_outputs().begin(),
                             module_->get_outputs().end(),
                             ioport);
  assert(index != -1);

  // create bind port
  lnode bindport(ctx_->createNode<bindportimpl>(this, ioport));
  auto input = dynamic_cast<inputimpl*>(dst.get_impl());
  if (input) {
    this->bind_input(bindport, input);
  } else {
    const_cast<lnode&>(dst).write(0, bindport, 0, dst.get_size(), dst.get_size());
  }

  // add to list
  outputs_[index] = bindport;
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
  is_output_ = dynamic_cast<outputimpl*>(ioport_.get_impl()) != nullptr;
}

const bitvector& bindportimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;    
    value_ = is_output_ ? ioport_.eval(t) : srcs_[0].eval(t);
  }
  return value_;
}

void bindportimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_type() << value_.get_size();
  out << "(" << (is_output_ ? "out" : "in") << ", ";
  out << "#" << srcs_[0].get_id() << ", $" << ioport_.get_id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}


