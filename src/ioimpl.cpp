#include "ioimpl.h"
#include "snodeimpl.h"
#include "context.h"

using namespace cash::internal;

inputimpl::inputimpl(ch_operator op, context* ctx, uint32_t size) 
  : ioimpl(op, ctx, size)
  , tick_(~0ull)
{}

inputimpl::~inputimpl() {}

void inputimpl::bind(const snode& bus) {
  bus_ = bus;
}

const bitvector& inputimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = bus_.get_value();
  }
  return value_;
}

void inputimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
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
  , bus_(nullptr)
  , tick_(~0ull) {
  srcs_.emplace_back(src);
}

outputimpl::~outputimpl() {
  if (bus_)
    bus_->release();
}

const bitvector& outputimpl::eval(ch_tick t) {  
  if (tick_ != t) {
    tick_ = t;
    if (bus_) {
      bus_->set_value(srcs_[0].eval(t));
    }
  }
  return value_;
}

snodeimpl* outputimpl::get_bus() {
  if (nullptr == bus_) {
    bus_ = new snodeimpl(value_.get_size());
    bus_->acquire();
  }
  return bus_;
}

void outputimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
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

void tapimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
}
