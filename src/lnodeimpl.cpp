#include "lnodeimpl.h"
#include "bit.h"
#include "ioimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "tickable.h"
#include "regimpl.h"
#include "cdomain.h"
#include "context.h"

using namespace cash::internal;

const char* cash::internal::to_string(ch_operator op) {
  static const char* sc_names[] = {
    CH_OPERATOR_ENUM(CH_OPERATOR_NAME)
  };
  return sc_names[(int)op];
}

lnodeimpl::lnodeimpl(ch_operator op, context* ctx, uint32_t size) 
  : op_(op)
  , ctx_(ctx)
  , value_(size) {
  id_ = ctx->add_node(this);  
}

lnodeimpl::~lnodeimpl() {
  ctx_->remove_node(this);  
}

bool lnodeimpl::ready() const {
  for (auto& src : srcs_) {
    if (!src.ready())
      return false;
  }
  return true;
}

bool lnodeimpl::valid() const {
  for (auto& src : srcs_) {
    if (!src.valid())
      return false;
  }
  return true;
}

lnodeimpl* lnodeimpl::get_slice(uint32_t offset, uint32_t length) {
  assert(length <= value_.get_size());
  if (value_.get_size() == length)
    return this;
  return new proxyimpl(lnode(this), offset, length);
}

void lnodeimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_op() << value_.get_size();
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << srcs_[i].get_id();
    }
    out << ")";
  }

  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

undefimpl::undefimpl(context* ctx, uint32_t size)
  : lnodeimpl(op_undef, ctx, size)
{}

const bitvector& undefimpl::eval(ch_tick) {
  CH_ABORT("undefined node: %d!", id_);
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode() : impl_(nullptr) {}

lnode::lnode(uint32_t size) : impl_(nullptr) {
  // force initialization inside conditional blocks
  if (ctx_curr()->conditional_enabled()) {
    this->ensureInitialized(size, true);
  }
}

lnode::lnode(lnodeimpl* impl) : impl_(impl) {
  assert(impl);
}

lnode::lnode(const bitvector& value) {
  impl_ = ctx_curr()->get_literal(value);
}

lnode::lnode(const nodelist& data) : impl_(nullptr) {
  if (data.is_srccopy())  {
    impl_ = data.begin()->src.get_impl();
  } else {
    uint32_t dst_offset = 0;
    this->ensureInitialized(data.get_size(), false);
    auto proxy = dynamic_cast<proxyimpl*>(impl_);
    for (const auto& slice : data) {
      proxy->add_source(dst_offset, slice.src, slice.offset, slice.length);
      dst_offset += slice.length;
    }
  }
}

lnode::lnode(const lnode& rhs, uint32_t size) : impl_(nullptr) {
  rhs.ensureInitialized(size, true);
  this->init(0, rhs, 0, size, size);
}

lnode::lnode(lnode&& rhs, uint32_t size) {
  rhs.ensureInitialized(size, true);
  impl_ = rhs.impl_;
  rhs.impl_ = nullptr;
}

lnode::lnode(const lnode& rhs) : impl_(rhs.impl_) {}

lnode::~lnode() {
  this->clear();
}

void lnode::clear() {
  impl_ = nullptr;
}

lnode& lnode::operator=(const lnode& rhs) {
  impl_ = rhs.impl_;
  return *this;
}

void lnode::assign(const lnode& rhs, uint32_t size) {
  rhs.ensureInitialized(size, true);
  this->assign(0, rhs, 0, size, size);
}

void lnode::assign(const bitvector& value) {
  auto impl = ctx_curr()->get_literal(value);
  this->assign(0, impl, 0, value.get_size(), value.get_size());
}

void lnode::move(lnode& rhs, uint32_t size) {
  assert(this != &rhs);
  rhs.ensureInitialized(size, true);
  if (ctx_curr()->conditional_enabled(impl_)) {
    this->assign(0, rhs, 0, size, size);
  } else {
    auto proxy = dynamic_cast<proxyimpl*>(impl_);
    if (proxy) {
      proxy->add_source(0, rhs, 0, size);
    } else {
      impl_ = rhs.impl_;
    }
  }
  rhs.impl_ = nullptr;
}

bool lnode::is_empty() const {
  return (nullptr == impl_);
}

uint32_t lnode::get_id() const {
  return impl_ ? impl_->get_id() : 0; 
}

context* lnode::get_ctx() const {
  assert(impl_);
  return impl_->get_ctx();
}

uint32_t lnode::get_size() const {
  return impl_ ? impl_->get_size() : 0;
}

bool lnode::ready() const {
  return impl_ ? impl_->ready() : true;
}

bool lnode::valid() const {
  return impl_ ? impl_->valid() : true;
}

const bitvector& lnode::eval(ch_tick t) {
  assert(impl_);
  return impl_->eval(t);
}

void lnode::set_impl(lnodeimpl* impl) {
  assert(impl);
  impl_ = impl;
}

lnodeimpl* lnode::get_impl() const {
  assert(impl_);
  return impl_;
}

bool lnode::operator==(const lnode& rhs) const {
  return this->get_impl() == rhs.get_impl();
}

bool lnode::operator<(const lnode& rhs) const {
  return this->get_impl() < rhs.get_impl();
}

void lnode::ensureInitialized(uint32_t size, bool initialize) const {
  if (nullptr == impl_) {
    if (initialize) {
      impl_ = new proxyimpl(new undefimpl(ctx_curr(), size));
    } else {
      impl_ = new proxyimpl(ctx_curr(), size);
    }
  }
  assert(impl_->get_size() == size);
}

void lnode::init(uint32_t dst_offset,
                 const lnode& src,
                 uint32_t src_offset,
                 uint32_t length,
                 uint32_t size) {
  assert(size > dst_offset);
  assert(size >= dst_offset + length);
  this->ensureInitialized(size, length != size);
  auto proxy = dynamic_cast<proxyimpl*>(impl_);
  proxy->add_source(dst_offset, src, src_offset, length);
}

void lnode::assign(uint32_t dst_offset,
                   const lnode& src,
                   uint32_t src_offset,
                   uint32_t length,
                   uint32_t size) {
  assert(size > dst_offset);
  assert(size >= dst_offset + length);
  context* ctx = src.get_ctx();  

  auto proxy = dynamic_cast<proxyimpl*>(impl_);
  if (nullptr == proxy) {
    lnodeimpl* impl = nullptr;
    std::swap<lnodeimpl*>(impl, impl_);
    this->ensureInitialized(size, nullptr == impl);
    proxy = dynamic_cast<proxyimpl*>(impl_);
    if (impl) {
      proxy->add_source(0, impl, 0, size);
    }
    ctx->remove_from_locals(impl_);
  }

  if (ctx->conditional_enabled(impl_)) {
    const auto& slices = proxy->get_update_slices(dst_offset, length);
    for (const auto& slice : slices) {
      lnodeimpl* src_impl = src.get_impl();
      if (slice.second != src.get_size()) {
        assert(slice.first >= dst_offset);
        uint32_t offset = src_offset + (slice.first - dst_offset);
        src_impl = new proxyimpl(src, offset, slice.second);
      }
      ctx->conditional_assign(*this, src_impl, slice.first, slice.second);
    }
  } else {
    proxy->add_source(dst_offset, src, src_offset, length);
  }
}

void lnode::read_data(nodelist& inout,
                      uint32_t offset,
                      uint32_t length,
                      uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size, true);
  inout.push(*this, offset, length);
}

void lnode::write_data(uint32_t dst_offset,
                       const nodelist& in,
                       uint32_t src_offset,
                       uint32_t length,
                       uint32_t size) {
  assert((dst_offset + length) <= size);
  for (const auto& d : in) {
    if (src_offset < d.length) {
      uint32_t len = std::min(d.length - src_offset, length);
      this->assign(dst_offset, d.src, d.offset + src_offset, len, size);
      length -= len;
      if (0 == length)
        return;
      dst_offset += len;                
      src_offset = d.length;
    }
    src_offset -= d.length;
  }
}

void lnode::read_bytes(uint32_t dst_offset,
                       void* out,
                       uint32_t out_cbsize,
                       uint32_t src_offset,
                       uint32_t length,
                       uint32_t size) const {
  this->ensureInitialized(size, false);
  impl_->read_bytes(dst_offset, out, out_cbsize, src_offset, length);
}

void lnode::write_bytes(uint32_t dst_offset,
                        const void* in,
                        uint32_t in_cbsize,
                        uint32_t src_offset,
                        uint32_t length,
                        uint32_t size) const {
  this->ensureInitialized(size, false);
  impl_->write_bytes(dst_offset, in, in_cbsize, src_offset, length);
}

const bitvector& lnode::get_value() const {
  assert(impl_);
  return impl_->get_value();
}

void lnode::set_value(const bitvector& value) {
  assert(impl_);
  impl_->set_value(value);
}

bool lnode::get_bool(unsigned i) const {
  assert(impl_);
  return impl_->get_bool(i);
}

void lnode::set_bool(unsigned i, bool value) {
  assert(impl_);
  impl_->set_bool(i, value);
}

lnodeimpl* lnode::clone(uint32_t size) const {
  return impl_ ? impl_->get_slice(0, size) : nullptr;
}

std::ostream& cash::internal::operator<<(std::ostream& out, ch_operator op) {
  out << to_string(op);
  return out;
}

std::ostream& cash::internal::operator<<(std::ostream& out, const lnode& node) {
  out << node.get_value();
  return out;
}
