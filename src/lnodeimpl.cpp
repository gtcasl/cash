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

void lnodeimpl::print(std::ostream& out) const {
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
}

///////////////////////////////////////////////////////////////////////////////

undefimpl::undefimpl(context* ctx, uint32_t size) 
  : lnodeimpl(op_undef, ctx, size) 
{}

const bitvector& undefimpl::eval(ch_cycle t) {
  CH_UNUSED(t);
  CH_ABORT("undefined node: %d!", id_);
  return value_; 
}

void undefimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode() : impl_(nullptr) {}

lnode::lnode(const lnode& rhs) : impl_(nullptr) {
  this->assign(rhs.impl_, true);
}

lnode::lnode(lnode&& rhs) : impl_(nullptr) {
  this->move(rhs);
}

lnode::lnode(lnodeimpl* impl) : impl_(nullptr) { 
  this->assign(impl, true);
}

lnode::lnode(const data_type& data) : impl_(nullptr) {
  uint32_t dst_offset = 0;
  for (auto& d : data) {
    this->assign(dst_offset, d.src, d.offset, d.length, data.get_size(), true);
    dst_offset += d.length;
  }
}

lnode::lnode(const bitvector& value) : impl_(nullptr) {
  this->assign(ctx_curr()->create_literal(value), true);
}

lnode::~lnode() {
  impl_ = nullptr;
}

void lnode::assign(const bitvector& value) {
  this->assign(ctx_curr()->create_literal(value));
}

lnode& lnode::operator=(const lnode& rhs) {
  this->assign(rhs.impl_);
  return *this;
}

lnode& lnode::operator=(lnode&& rhs) {
  this->move(rhs);
  return *this;
}

lnode& lnode::operator=(lnodeimpl* rhs) {
  this->assign(rhs);
  return *this;
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

lnodeimpl* lnode::get_impl() const {
  return impl_;
}

void lnode::set_impl(lnodeimpl* impl) {
  impl_ = impl;
}

void lnode::move(lnode& rhs) {
  impl_ = rhs.impl_;
  rhs.impl_ = nullptr;
}

void lnode::assign(lnodeimpl* impl, bool initialization) {
  if (impl) {
    if (!initialization) {
      // resolve conditionals if inside a branch
      impl = impl->get_ctx()->resolve_conditional(impl_, impl);
      if (impl == impl_)
        return;
    }
  }
  impl_ = impl;
}

void lnode::read_data(data_type& inout, uint32_t offset, uint32_t length, uint32_t size) const {
  assert((offset + length) <= size);
  inout.push({impl_, offset, length});
}

void lnode::write_data(uint32_t dst_offset,
                       const data_type& in,
                       uint32_t src_offset,
                       uint32_t src_length,
                       uint32_t size) {
  assert(in.num_nodes() >= 1);
  assert((dst_offset + src_length) <= size);
  for (auto& d : in) {
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

void lnode::assign(uint32_t dst_offset,
                   lnodeimpl* src,
                   uint32_t src_offset,
                   uint32_t src_length,
                   uint32_t size,
                   bool initialization) {
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  context* const ctx = src->get_ctx();
  if (size == src_length) {
    if (src->get_size() > src_length) {
      assert(0 == dst_offset);
      proxyimpl* const proxy = new proxyimpl(ctx, src_length);
      proxy->add_node(0, src, src_offset, src_length);
      src = proxy;
    }
    this->assign(src, initialization);
  } else {
    assert(src_length < size);
    if (impl_) {
      // check if conditional handling is needed
      if (!initialization
       && ctx->conditional_enabled(impl_)) {
        if (src->get_size() > src_length) {
          proxyimpl* const proxy = new proxyimpl(ctx, src_length);
          proxy->add_node(dst_offset, src, src_offset, src_length);
          src = proxy;
        }

        lnodeimpl* const impl = impl_;
        proxyimpl* proxy = dynamic_cast<proxyimpl*>(impl_);
        if (nullptr == proxy) {
          proxy = new proxyimpl(ctx, size);
          this->assign(proxy, true);
          proxy->add_node(0, impl, 0, size);
        }

        proxyimpl* const proxy_sub = new proxyimpl(ctx, src_length);
        proxy_sub->add_node(0, impl, dst_offset, src_length);
        src = ctx->resolve_conditional(proxy_sub, src);

        proxy->add_node(dst_offset, proxy_sub, src_offset, src_length);
      } else {
        proxyimpl* proxy = dynamic_cast<proxyimpl*>(impl_);
        if (nullptr == proxy) {
          proxy = new proxyimpl(ctx, size);
          lnodeimpl* const impl = impl_;
          this->assign(proxy, initialization);
          proxy->add_node(0, impl, 0, size);
        }
        proxy->add_node(dst_offset, src, src_offset, src_length);
      }
    } else {
      proxyimpl* const proxy = new proxyimpl(ctx, size);
      proxy->add_node(dst_offset, src, src_offset, src_length);
      this->assign(proxy, initialization);
    }
  }
}
