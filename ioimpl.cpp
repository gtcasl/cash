#include "ioimpl.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

inputimpl::inputimpl(ch_operator op, context* ctx, uint32_t size) 
  : ioimpl(op, ctx, size)
  , bus_(nullptr)
{}

inputimpl::~inputimpl() {
  if (bus_)
    bus_->release();
}

void inputimpl::bind(snodeimpl* bus) {
  bus->acquire();
  if (bus_)
    bus_->release();
  bus_ = bus;
}

const bitvector& inputimpl::eval(ch_cycle t) {
  CH_UNREFERENCED_PARAMETER(t);
  assert(bus_);
  return bus_->read();
}

void inputimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size() << "("; 
  if (bus_) {
    out << "$" << bus_->get_id();
  } else {
    out << "?";
  }
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////

outputimpl::outputimpl(ch_operator op, lnodeimpl* src) 
  : ioimpl(op, src->get_ctx(), src->get_size())
  , bus_(nullptr) {
  srcs_.reserve(1);
  srcs_.emplace_back(src);
}

outputimpl::~outputimpl() {
  if (bus_)
    bus_->release();
}

const bitvector& outputimpl::eval(ch_cycle t) {
  const bitvector& bits = srcs_[0].eval(t);
  if (bus_)
    bus_->write(bits);
  return bits;
}

snodeimpl* outputimpl::get_bus() {
  if (bus_ == nullptr) {
    bus_ = new snodeimpl(value_.get_size());
    bus_->acquire();
  }
  return bus_;
}

void outputimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
  out << "(" << "#" << srcs_[0].get_id() << ")";
}

///////////////////////////////////////////////////////////////////////////////

tapimpl::tapimpl(const std::string& name, lnodeimpl* src) 
  : outputimpl(op_tap, src)
  , tapName_(name) {
  srcs_.reserve(1);
  srcs_.emplace_back(src);
}

void tapimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
  out << "(#" << srcs_[0].get_id() << ", '" << tapName_ << "')";
}
