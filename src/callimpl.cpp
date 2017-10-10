#include "callimpl.h"
#include "context.h"

using namespace ch::internal;

callimpl::callimpl(context* ctx, context* module_ctx)
  : ioimpl(ctx, type_call, 0)
  , module_ctx_(module_ctx)
  , tick_(~0ull) {
  module_ctx->acquire();
  srcs_.resize(module_ctx->get_inputs().size());
}

callimpl::~callimpl() {
  module_ctx_->release();
}

void callimpl::bind_input(const lnode& input, const lnode& src) {
  auto it = module_ctx_->get_inputs().begin();
  for (auto& _src : srcs_) {
    if ((*it)->get_id() == input.get_id()) {
      _src = src;
      break;
    }
    ++it;
  }
}

void callimpl::tick(ch_tick t) {
  module_ctx_->tick(t);
}

void callimpl::tick_next(ch_tick t) {
  module_ctx_->tick_next(t);
}

const bitvector& callimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    module_ctx_->eval(t);
  }
  return value_;
}

void callimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->get_type();
  out << "(" << module_ctx_->get_name();
  for (auto& src : srcs_) {
    out << ", #" << src.get_id();
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

callportimpl::callportimpl(context* ctx, callimpl* call, const lnode& output)
  : ioimpl(ctx, type_callport, output.get_size())
  , output_(output)
  , tick_(~0ull) {
  srcs_.push_back(call);
}

const bitvector& callportimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = output_.eval(t);
  }
  return value_;
}

void callportimpl::print(std::ostream& out, uint32_t level) const {
  auto call = dynamic_cast<callimpl*>(srcs_[0].get_impl());
  out << "#" << id_ << " <- " << this->get_type() << value_.get_size();
  out << "(" << call->get_id() << ", $";
  out << output_.get_id();
  out << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}


