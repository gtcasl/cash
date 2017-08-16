#include "ioimpl.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

inputimpl::inputimpl(ch_operator op, context* ctx, uint32_t size) 
  : ioimpl(op, ctx, size)
  , bus_(nullptr)
  , ctime_(~0ull)
{}

inputimpl::~inputimpl() {
  if (bus_)
    bus_->release();
}

void inputimpl::bind(snodeimpl* bus) {
  assert(bus);
  bus->acquire();
  if (bus_)
    bus_->release();
  bus_ = bus;
}

const bitvector& inputimpl::eval(ch_cycle t) {
  assert(bus_);
  if (ctime_ != t) {
    ctime_ = t;
    value_ = bus_->read();
  }
  return value_;
}

void inputimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size() << "("; 
  if (bus_) {
    out << "$" << bus_->get_id();
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
  : ioimpl(op, src->get_ctx(), src->get_size())
  , bus_(nullptr)
  , ctime_(~0ull) {
  srcs_.reserve(1);
  srcs_.emplace_back(src);
}

outputimpl::~outputimpl() {
  if (bus_)
    bus_->release();
}

const bitvector& outputimpl::eval(ch_cycle t) {  
  if (ctime_ != t) {
    ctime_ = t;
    value_ = srcs_[0].eval(t);
    if (bus_)
      bus_->write(value_);
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
  srcs_.reserve(1);
  srcs_.emplace_back(src);
}

void tapimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
  out << "(#" << srcs_[0].get_id() << ", '" << tapName_ << "')";

  if (level == 2) {
    out << " = " << value_;
  }
}
