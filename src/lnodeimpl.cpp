#include "bit.h"
#include "lnodeimpl.h"
#include "ioimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "tickable.h"
#include "regimpl.h"
#include "cdomain.h"
#include "snodeimpl.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

lnodeimpl::lnodeimpl(ch_operator op, context* ctx, uint32_t size) 
  : op_(op)
  , ctx_(ctx)
  , value_(size) {
  id_ = ctx->add_node(this);  
}

lnodeimpl::~lnodeimpl() {
  ctx_->remove_node(this);  
}

const char* lnodeimpl::get_name() const {
  static const char* sc_names[] = {
    CH_OPERATOR_ENUM(CH_OPERATOR_NAME)
  };
  return sc_names[(int)op_];
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

void lnodeimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size();
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

const bitvector& undefimpl::eval(ch_cycle) {
  CH_ABORT("undefined node: %d!", id_);
  return value_;
}

void undefimpl::print_vl(std::ostream&) const {
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode() : impl_(nullptr) {}

lnode::lnode(uint32_t size) : impl_(nullptr) {
  // force initialization of objects inside control blocks
  if (ctx_curr()->conditional_enabled()) {
    this->ensureInitialized(size, true);
  }
}

lnode::lnode(lnodeimpl* impl) : impl_(impl) {
  assert(impl);
}

lnode::lnode(const bitvector& value) {
  impl_ = ctx_curr()->create_literal(value);
}

lnode::lnode(const data_type& data) : impl_(nullptr) {    
  if (data.num_slices() > 1) {
    uint32_t dst_offset = 0;
    this->ensureInitialized(data.capacity(), false);
    auto proxy = dynamic_cast<proxyimpl*>(impl_);
    for (auto& slice : data) {
      proxy->add_source(dst_offset, slice.src, slice.offset, slice.length);
      dst_offset += slice.length;
    }
  } else {
    const auto& slice = *data.begin();
    assert(slice.offset == 0);
    assert(slice.length == data.capacity());
    impl_ = slice.src.get_impl();
  }
}

lnode::lnode(const lnode& rhs, uint32_t size) : impl_(nullptr) {
  rhs.ensureInitialized(size, true);
  this->init(0, rhs, 0, size, size);
}

lnode::lnode(lnode&& rhs, uint32_t size) : impl_(nullptr) {
  this->move(rhs, size);
}

lnode::lnode(const lnode& rhs) : impl_(rhs.impl_) {}

lnode::~lnode() {
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
  auto impl = ctx_curr()->create_literal(value);
  this->assign(0, impl, 0, value.get_size(), value.get_size());
}

void lnode::move(lnode& rhs, uint32_t size) {
  assert(this != &rhs);
  rhs.ensureInitialized(size, true);
  auto proxy = dynamic_cast<proxyimpl*>(impl_);
  if (proxy) {
    proxy->add_source(0, rhs, 0, size);
  } else {
    impl_ = rhs.impl_;
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

const bitvector& lnode::eval(ch_cycle t) {
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
                 uint32_t src_length,
                 uint32_t size) {
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  this->ensureInitialized(size, src_length != size);
  auto proxy = dynamic_cast<proxyimpl*>(impl_);
  proxy->add_source(dst_offset, src, src_offset, src_length);
}

void lnode::assign(uint32_t dst_offset,
                   const lnode& src,
                   uint32_t src_offset,
                   uint32_t src_length,
                   uint32_t size) {
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  context* ctx = src.get_ctx();
  if (ctx->conditional_enabled(impl_)) {    
    this->ensureInitialized(size, true);
    auto proxy = dynamic_cast<proxyimpl*>(impl_);
    const auto& slices = proxy->get_update_slices(dst_offset, src_length);
    for (const auto& slice : slices) {
      proxyimpl* proxy_src = nullptr;
      if (slice.second != size) {
        proxy_src = new proxyimpl(ctx, slice.second);
        proxy_src->add_source(0, src, src_offset + (slice.first - dst_offset), slice.second);
      }
      ctx->conditional_assign(*this, (proxy_src ? lnode(proxy_src) : src), slice.first, slice.second);
    }
  } else {
    this->init(dst_offset, src, src_offset, src_length, size);
  }
}

void lnode::read_data(data_type& inout,
                      uint32_t offset,
                      uint32_t length,
                      uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size, true);
  inout.push_back({*this, offset, length});
}

void lnode::write_data(uint32_t dst_offset,
                       const data_type& in,
                       uint32_t src_offset,
                       uint32_t src_length,
                       uint32_t size) {
  assert((dst_offset + src_length) <= size);
  for (const auto& d : in) {
    if (src_offset < d.length) {
      uint32_t len = std::min(d.length - src_offset, src_length);
      this->assign(dst_offset, d.src, d.offset + src_offset, len, size);
      src_length -= len;
      if (0 == src_length)
        return;
      dst_offset += len;                
      src_offset = d.length;
    }
    src_offset -= d.length;
  }
}
