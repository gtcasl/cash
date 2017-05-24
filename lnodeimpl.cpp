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
  for (auto iter = refs_.begin(), iterEnd = refs_.end(); iter != iterEnd;) {
    (*iter++).node->clear();
  }
  ctx_->remove_node(this);  
}

void lnodeimpl::add_ref(const lnode* node, const lnode* owner) {
  refs_.emplace(node, owner);  
}

void lnodeimpl::remove_ref(const lnode* node) {
  refs_.erase(node);
}

void lnodeimpl::update_ref(const lnode* node, lnodeimpl* impl) {
  CH_UNUSED(node, impl);
  CH_TODO();
}

const lnode* lnodeimpl::get_ref_owner(const lnode* node) {
  auto iter = refs_.find(node);
  if (iter != refs_.end()) {
    return iter->owner;
  }
  return nullptr;
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

lnode::lnode(uint32_t size) : impl_(nullptr) {
  // force initialization of nested objects
  if (ctx_curr()->conditional_enabled()) {
    this->ensureInitialized(size);
  }
}

lnode::lnode(const lnode& rhs) : impl_(nullptr) { 
  this->assign(rhs.impl_, &rhs, true);
}

lnode::lnode(lnode&& rhs) : impl_(nullptr) {
  this->move(rhs);
}

lnode::lnode(lnodeimpl* impl) : impl_(nullptr) { 
  this->assign(impl, nullptr, true);
}

lnode::lnode(const data_type& data) : impl_(nullptr) {
  uint32_t dst_offset = 0;
  for (auto& d : data) {
    this->assign(dst_offset, d.src, d.offset, d.length, data.get_size(), true);
    dst_offset += d.length;
  }
}

lnode::lnode(const bitvector& value) : impl_(nullptr) {
  this->assign(ctx_curr()->create_literal(value), nullptr, true);
}

lnode::~lnode() {
  this->clear();
}

void lnode::assign(const bitvector& value) {
  this->assign(ctx_curr()->create_literal(value), nullptr);
}

lnode& lnode::operator=(const lnode& rhs) {
  this->assign(rhs.impl_, &rhs);
  return *this;
}

lnode& lnode::operator=(lnode&& rhs) {
  this->move(rhs);
  return *this;
}

lnode& lnode::operator=(lnodeimpl* rhs) {
  this->assign(rhs, nullptr);
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

const lnode& lnode::ensureInitialized(uint32_t size) const {
  if (impl_ == nullptr) {
    impl_ = new undefimpl(ctx_curr(), size);
  }
  assert(impl_->get_size() == size);
  return *this;
}

void lnode::clear() const {
  if (impl_)
    impl_->remove_ref(this);
  impl_ = nullptr;
}

lnodeimpl* lnode::get_impl() const {
  assert(impl_);
  return impl_;
}

void lnode::move(lnode& rhs) {
  assert(rhs.impl_);
  assert(rhs.impl_ != impl_);
  if (impl_ != rhs.impl_) {
    this->clear();
    impl_ = rhs.impl_;
    impl_->add_ref(this, rhs.impl_->get_ref_owner(&rhs));
  }
  rhs.clear();
}

void lnode::assign(lnodeimpl* impl, const lnode* src, bool initialization) const {
  if (impl) {
    if (!initialization) {
      // resolve conditionals if inside a branch
      impl = impl->get_ctx()->resolve_conditional(impl_, impl);
      if (impl == impl_)
        return;
    } 
    impl->add_ref(this, src);
  }
  if (impl_) {
    CH_CHECK(impl != impl_, "redundant assignment for node %s%d(#%d)!\n", impl_->get_name(), impl_->get_size(), impl_->get_id());    
    impl_->remove_ref(this);
    impl_->update_ref(this, impl);
  }  
  impl_ = impl;
}

void lnode::read(data_type& inout, uint32_t offset, uint32_t length, uint32_t size) const {
  assert((offset + length) <= size);
  this->ensureInitialized(size);
  inout.push({*this, offset, length});
}

void lnode::write(uint32_t dst_offset, const data_type& in, uint32_t src_offset, uint32_t src_length, uint32_t size) {
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

void lnode::assign(uint32_t dst_offset, const lnode& src, uint32_t src_offset, uint32_t src_length, uint32_t size, bool initialization) {
  assert(size > dst_offset);
  assert(size >= dst_offset + src_length);
  
  const lnode* src_node = &src;
  lnodeimpl* src_impl = src_node->get_impl();    
  context* const ctx = src_impl->get_ctx();
  
  // check if full assignment
  if (src_length == size) {
    assert(0 == dst_offset);
    // check if partial source
    if (src_impl->get_size() > src_length) {
      proxyimpl* const proxy = new proxyimpl(ctx, src_length);
      proxy->add_node(0, src, src_offset, src_length);
      src_impl = proxy;
      src_node = nullptr;
    }
  } else {
    // partial assignment using proxy
    assert(src_length < size);    
    proxyimpl* const proxy = new proxyimpl(ctx, size);  
    this->ensureInitialized(size);
    proxy->add_node(0, *this, 0, size);      
    proxy->add_node(dst_offset, src, src_offset, src_length);
    src_impl = proxy;
    src_node = nullptr;
  }
  
  this->assign(src_impl, src_node, initialization);
}
