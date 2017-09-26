#include "ioimpl.h"
#include "snodeimpl.h"
#include "context.h"

using namespace cash::internal;

inputimpl::inputimpl(ch_operator op, context* ctx, uint32_t size) 
  : ioimpl(op, ctx, size)
  , tick_(~0ull)
{}

inputimpl::inputimpl(context* ctx, const snode& node)
  : ioimpl(op_input, ctx, node.get_size())
  , tick_(~0ull) {
  this->bind(node);
}

void inputimpl::bind(const snode& node) {
  bus_ = node;
}

void inputimpl::unbind() {
  bus_.clear();
}

const bitvector& inputimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = bus_.get_value();
  }
  return value_;
}

void inputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size() << "("; 
  if (!bus_.is_empty()) {
    out << "$" << bus_.get_id();
  } else {
    out << "?";
  }
  out << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(ch_operator op, const lnode& src)
  : ioimpl(op, src.get_ctx(), src.get_size())
  , bus_(new snodeimpl(src.get_size()))
  , tick_(~0ull) {
  srcs_.emplace_back(src);
}

const bitvector& outputimpl::eval(ch_tick t) {  
  if (tick_ != t) {
    tick_ = t;
    bus_.set_value(srcs_[0].eval(t));
  }
  return value_;
}

void outputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
  out << "(" << "#" << srcs_[0].get_id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(const std::string& name, const lnode& src)
  : outputimpl(op_tap, src)
  , tapName_(name) {
  srcs_.emplace_back(src);
}

void tapimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
  out << "(#" << srcs_[0].get_id() << ", '" << tapName_ << "')";
  if (level == 2) {
    out << " = " << value_;
  }
}
