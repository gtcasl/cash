#include "ioimpl.h"
#include "ioport.h"
#include "context.h"

using namespace ch::internal;

inputimpl::inputimpl(context* ctx, uint32_t size, const std::string& name)
  : ioimpl(ctx, type_input, size, name)
  , tick_(~0ull)
{}

const bitvector& inputimpl::eval(ch_tick t) {
  if (tick_ != t && !input_.empty()) {
    tick_ = t;
    value_ = input_.eval(t);
  }
  return value_;
}

void inputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_type() << value_.size();
  out << "(" << name_;
  if (!input_.empty()) {
    out << ", $" << input_.get_id();
  }
  out << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(context* ctx, const lnode& src, const std::string& name)
  : ioimpl(ctx, type_output, src.size(), name)
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
  out << "#" << id_ << " <- " << this->get_type() << value_.size();
  out << "(" << name_ << ", #" << srcs_[0].get_id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(context* ctx, const lnode& src, const std::string& name)
  : ioimpl(ctx, type_tap, src.size(), name)
  , tick_(~0ull) {
  srcs_.emplace_back(src);
}

void tapimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_type() << value_.size();
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

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createInputNode(const std::string& name, uint32_t size) {
  return ctx_curr()->create_node<inputimpl>(size, name);
}

lnodeimpl* ch::internal::createOutputNode(const std::string& name, const lnode& src) {
  return src.get_ctx()->create_node<outputimpl>(src, name);
}
