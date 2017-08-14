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

void lnodeimpl::add_ref(const lnode* node, const lnode* src) {
  auto it = std::find(refs_.begin(), refs_.end(), node);
  if (it != refs_.end()) {
      it->src = src;
  } else {
    refs_.emplace_back(node, src);
  }
}

void lnodeimpl::remove_ref(const lnode* node) {
  auto it = std::find(refs_.begin(), refs_.end(), node);
  if (it != refs_.end()) {
    this->replace_refs(it->node, it->src);
    refs_.erase(it);
  }
}

void lnodeimpl::update_refs(const lnode* node) {
  for (auto& ref: refs_) {
    if (ref.src == node) {
      const_cast<lnode*>(ref.src)->set_impl(this);
    }
  }
}

void lnodeimpl::replace_refs(const lnode* old_node, const lnode* new_node) {
  for (auto& ref: refs_) {
    if (ref.src == old_node) {
      ref.src = new_node;
    }
  }
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

lnode::lnode(uint32_t size) : lnode() {
  // force initialization of objects inside control blocks
  if (ctx_curr()->conditional_enabled()) {
    this->ensureInitialized(size);
  }
}

lnode::lnode(lnodeimpl* impl) : lnode() {
  assert(impl);
  this->init(0, impl, nullptr, 0, impl->get_size(), impl->get_size());
}

lnode::lnode(const bitvector& value) : lnode() {
  auto impl = ctx_curr()->create_literal(value);
  this->init(0, impl, nullptr, 0, value.get_size(), value.get_size());
}

lnode::lnode(const data_type& data) : lnode() {
  uint32_t dst_offset = 0;
  for (auto& d : data) {
    this->init(dst_offset, d.src.impl_, &d.src, d.offset, d.length, data.capacity());
    dst_offset += d.length;
  }
}

lnode::lnode(const lnode& rhs, uint32_t size) : lnode() {
  rhs.ensureInitialized(size);
  this->init(0, rhs.impl_, &rhs, 0, size, size);
}

lnode::lnode(const lnode& rhs)
  : impl_(rhs.impl_)
{}

lnode::lnode(lnode&& rhs) : lnode() {
  this->move(rhs);
}

lnode::~lnode() {
  this->clear();
}

lnode& lnode::operator=(const lnode& rhs) {
  assert(rhs.impl_);
  this->assign(0, rhs.impl_, &rhs, 0, rhs.impl_->get_size(), rhs.impl_->get_size());
  return *this;
}

lnode& lnode::operator=(lnode&& rhs) {
  this->move(rhs);
  return *this;
}

lnode& lnode::operator=(lnodeimpl* impl) {
  this->init(0, impl, nullptr, 0, impl->get_size(), impl->get_size());
  return *this;
}

void lnode::assign(const lnode& rhs, uint32_t size) {
  rhs.ensureInitialized(size);
  this->assign(0, rhs.impl_, &rhs, 0, size, size);
}

void lnode::assign(const bitvector& value) {
  auto impl = ctx_curr()->create_literal(value);
  this->assign(0, impl, nullptr, 0, value.get_size(), value.get_size());
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

void lnode::clear() {
  if (impl_) {
    impl_->remove_ref(this);
  }
  impl_ = nullptr;
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

void lnode::move(lnode& rhs) {
  this->clear();
  if (rhs.impl_) {
    impl_ = rhs.impl_;
    impl_->replace_refs(&rhs, this);
    rhs.clear();
  }
}

void lnode::ensureInitialized(uint32_t size) const {
  if (nullptr == impl_) {
    impl_ = new undefimpl(ctx_curr(), size);
  }
  assert(impl_->get_size() == size);
}

void lnode::init(uint32_t dst_offset,
                 lnodeimpl* src_impl,
                 const lnode* src_node,
                 uint32_t src_offset,
                 uint32_t src_length,
                 uint32_t size) {
  assert(src_impl);
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  context* ctx = src_impl->get_ctx();

  if (src_length == size) {
    impl_ = src_impl;
  } else {
    auto proxy = dynamic_cast<proxyimpl*>(impl_);
    if (nullptr == proxy) {
      proxy = new proxyimpl(ctx, size);
      if (impl_) {
        proxy->add_source(0, impl_, 0, size);
      }
      impl_ = proxy;
    }
    proxy->add_source(dst_offset, src_impl, src_offset, src_length);
  }
  if (src_node) {
    impl_->add_ref(this, src_node);
  }
}

void lnode::assign(uint32_t dst_offset,
                   lnodeimpl* src_impl,
                   const lnode* src_node,
                   uint32_t src_offset,
                   uint32_t src_length,
                   uint32_t size) {
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  context* ctx = src_impl->get_ctx();

  if (ctx->conditional_enabled(impl_)) {
    if (src_length != src_impl->get_size()) {
      proxyimpl* const proxy = new proxyimpl(ctx, src_length);
      proxy->add_source(0, src_impl, src_offset, src_length);
      src_offset = 0;
      src_impl = proxy;
    }

    if (src_length != size) {
      proxyimpl* proxy = dynamic_cast<proxyimpl*>(impl_);
      if (nullptr == proxy) {
        proxy = new proxyimpl(ctx, size);
        ctx->erase_block_local(proxy, impl_);
        if (impl_) {
          proxy->add_source(0, impl_, 0, size);
        }
        impl_ = proxy;
      }

      lnodeimpl* const dst = proxy->get_slice(dst_offset, src_length);
      ctx->erase_block_local(dst, proxy);
      src_impl = ctx->resolve_conditional(src_impl, dst);
      if (src_impl == dst)
        return;
      proxy->add_source(dst_offset, src_impl, src_offset, src_length);
      if (src_node) {
        impl_->add_ref(this, src_node);
      }
    } else {
      lnodeimpl* dst = impl_;
      if (nullptr == dst) {
        dst = new undefimpl(ctx, size);
        ctx->erase_block_local(dst, nullptr);
      }
      src_impl = ctx->resolve_conditional(src_impl, dst);
      if (src_impl == dst)
        return;
      impl_ = src_impl;
    }
  } else {
    this->init(dst_offset, src_impl, src_node, src_offset, src_length, size);
  }  
  if (src_node) {
    impl_->update_refs(this);
  }
}

void lnode::read_data(data_type& inout,
                      uint32_t offset,
                      uint32_t length) const {
  assert((offset + length) <= inout.capacity());
  this->ensureInitialized(inout.capacity());
  inout.push_back({*this, offset, length});
}

void lnode::write_data(uint32_t dst_offset,
                       const data_type& in,
                       uint32_t src_offset,
                       uint32_t src_length) {
  assert((dst_offset + src_length) <= in.capacity());
  for (const auto& d : in) {
    if (src_offset < d.length) {
      uint32_t len = std::min(d.length - src_offset, src_length);
      this->assign(dst_offset, d.src.impl_, &d.src, d.offset + src_offset, len, in.capacity());
      src_length -= len;
      if (0 == src_length)
        return;
      dst_offset += len;                
      src_offset = d.length;
    }
    src_offset -= d.length;
  }
}
