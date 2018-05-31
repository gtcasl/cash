#include "cdimpl.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

cdimpl::cdimpl(context* ctx, const lnode& clk, const lnode& rst, bool posedge)
  : ioimpl(ctx, type_cd, 0)
  , posedge_(posedge)
  , prev_val_(false) {
  srcs_.emplace_back(clk);
  srcs_.emplace_back(rst);
}

cdimpl::~cdimpl() {}

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

void cdimpl::tick() {
  bool value = (this->clk().data().word(0) != 0);
  if (prev_val_ != value) {
    prev_val_ = value;
    if (0 == (value ^ posedge_)) {
      static int t = 0;
      ++t;
      for (auto reg : regs_) {
        reg->tick();
      }
    }
  }
}

void cdimpl::eval() {
  //--
}

void cdimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->type() << "("
      << (posedge_ ? "posedge" : "negedge") << ", #"
      << srcs_[0].id() << ", #" << srcs_[1].id() << ")";
}
