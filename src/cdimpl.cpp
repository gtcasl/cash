#include "cdimpl.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

cdimpl::cdimpl(context* ctx,
               const lnode& clk,
               bool posedge,
               const source_location& sloc)
  : ioimpl(ctx, type_cd, 1, sloc)
  , posedge_(posedge)
  , prev_val_(false) {
  srcs_.emplace_back(clk);
}

void cdimpl::eval() {
  bool value = (this->clk().data().word(0) != 0);
  data_.word(0) = (prev_val_ != value) && (0 == (value ^ posedge_));
  prev_val_ = value;
}

void cdimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->type() << "("
      << (posedge_ ? "posedge" : "negedge")
      << ", #" << srcs_[0].id() << ")";
}
