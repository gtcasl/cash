#include "cdimpl.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

cdimpl::cdimpl(context* ctx, const lnode& clock, const lnode& reset, bool posedge)
  : ioimpl(ctx, type_cd, 0)
  , posedge_(posedge)
  , prev_val_(false) {
  srcs_.emplace_back(clock);
  srcs_.emplace_back(reset);
}

cdimpl::~cdimpl() {
  // detach registers
  while (!regs_.empty()) {
    regs_.front()->detach();
  }
}

void cdimpl::add_reg(tickable* reg) {
  regs_.push_back(reg);
}

void cdimpl::remove_reg(tickable* reg) {
  for (auto it = regs_.begin(), end = regs_.end(); it != end; ++it) {
    if (*it == reg) {
      regs_.erase(it);
      break;
    }
  }
}

void cdimpl::tick(ch_tick t) {
  bool value = srcs_[0].eval(t)[0];
  if (prev_val_ != value) {
    prev_val_ = value;
    if ((value && posedge_) || (!value && !posedge_)) {
      for (auto reg : regs_) {
        reg->tick(t);
      }
    }
  }
}

void cdimpl::tick_next(ch_tick t) {
  for (auto reg : regs_) {
    reg->tick_next(t);
  }
}

void cdimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->get_type() << "("
      << (posedge_ ? "posedge" : "negedge") << ", #"
      << srcs_[0].get_id() << ", #" << srcs_[1].get_id() << ")";
}
