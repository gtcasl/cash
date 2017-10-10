#include "ioimpl.h"
#include "port.h"
#include "context.h"

using namespace ch::internal;

inputimpl::inputimpl(lnodetype type, context* ctx, uint32_t size, const char* name)
  : ioimpl(type, ctx, size, name)
  , tick_(~0ull)
{}

const bitvector& inputimpl::eval(ch_tick t) {
  if (tick_ != t && !srcs_.empty()) {
    tick_ = t;
    value_ = srcs_[0].eval(t);
  }
  return value_;
}

void inputimpl::bind(const lnode& input) {
  assert(ctx_ != input.get_ctx());
  if (srcs_.empty()) {
    srcs_.emplace_back(input);
  } else {
    srcs_[0] = input;
  }
}

void inputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_type() << value_.get_size();
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

outputimpl::outputimpl(const lnode& src, const char* name)
  : ioimpl(type_output, src.get_ctx(), src.get_size(), name)
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
  out << "#" << id_ << " <- " << this->get_type() << value_.get_size();
  out << "(" << name_ << ", #" << srcs_[0].get_id() << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(const lnode& src, const char* name)
  : ioimpl(type_tap, src.get_ctx(), src.get_size(), name)
  , tick_(~0ull) {
  srcs_.emplace_back(src);
}

void tapimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_type() << value_.get_size();
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

lnodeimpl* ch::internal::createInputNode(const char* name, uint32_t size) {
  return new inputimpl(ctx_curr(), size, name);
}

lnodeimpl* ch::internal::createOutputNode(const char* name, const lnode& src) {
  return new outputimpl(src, name);
}

void ch::internal::bindInput(const lnode& input, const lnode& src) {
  dynamic_cast<inputimpl*>(input.get_impl())->bind(src);
}

void ch::internal::bindOutput(const lnode& dst, const lnode& output) {
  auto input = dynamic_cast<inputimpl*>(dst.get_impl());
  if (input) {
    input->bind(output);
  } else {
    nodelist data(dst.get_size(), false);
    data.push(output);
    const_cast<lnode&>(dst).write_data(0, data, 0, dst.get_size(), dst.get_size());
  }
  dynamic_cast<outputimpl*>(output.get_impl())->bind(dst);
}
