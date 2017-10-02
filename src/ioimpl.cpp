#include "ioimpl.h"
#include "context.h"

using namespace ch::internal;

inputimpl::inputimpl(ch_operator op, context* ctx, uint32_t size, const std::string& name)
  : ioimpl(op, ctx, size, name)
  , tick_(~0ull)
{}

const bitvector& inputimpl::eval(ch_tick t) {
  if (tick_ != t && !srcs_.empty()) {
    tick_ = t;
    value_ = srcs_[0].eval(t);
  }
  return value_;
}

void inputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_op() << value_.get_size();
  out << "(" << name_ << ", ";
  if (!srcs_.empty()) {
    out << "$" << srcs_[0].get_id();
  } else {
    out << "?";
  }
  out << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(const lnode& src, const std::string& name)
  : ioimpl(op_output, src.get_ctx(), src.get_size(), name)
  , tick_(~0ull) {
  srcs_.emplace_back(src);
}

const bitvector& outputimpl::eval(ch_tick t) {  
  if (tick_ != t) {
    tick_ = t;
    value_ = srcs_[0].eval(t);
  }
  return value_;
}

void outputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_op() << value_.get_size();
  out << "(" << name_ << ", #" << srcs_[0].get_id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(const lnode& src, const std::string& name)
  : ioimpl(op_tap, src.get_ctx(), src.get_size(), name)
  , tick_(~0ull) {}

void tapimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_op() << value_.get_size();
  out << "(" << name_ << ", #" << srcs_[0].get_id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

const bitvector& tapimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = srcs_[0].eval(t);
  }
  return value_;
}
