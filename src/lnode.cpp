#include "lnode.h"
#include "lnodeimpl.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

lnode::lnode() : impl_(nullptr) {}

lnode::lnode(const lnode& rhs) : impl_(rhs.impl_) {}

lnode::lnode(uint32_t size,
             uint32_t var_id,
             const std::string& name,
             const source_location& sloc) {
  impl_ = ctx_curr()->create_node<proxyimpl>(
            ctx_curr()->create_node<undefimpl>(size), 0, size, var_id, name, sloc);
}

lnode::lnode(uint32_t size,
             const lnode& src,
             uint32_t src_offset,
             uint32_t var_id,
             const std::string& name,
             const source_location& sloc) {
  assert(!src.empty());
  impl_ = src.impl()->ctx()->create_node<proxyimpl>(
        src, src_offset, size, var_id, name, sloc);
}

lnode::lnode(lnodeimpl* impl) : impl_(impl) {
  assert(impl);
}

lnode::lnode(const bitvector& value) {
  impl_ = ctx_curr()->literal(value);
}

lnode::~lnode() {}

lnode& lnode::operator=(const lnode& rhs) {
  impl_ = rhs.impl_;
  return *this;
}

bool lnode::empty() const {
  return (nullptr == impl_);
}

uint32_t lnode::id() const {
  assert(impl_);
  return impl_->id();
}

const std::string& lnode::name() const {
  assert(impl_);
  return impl_->name();
}

uint32_t lnode::size() const {
  return impl_ ? impl_->size() : 0;
}

lnodeimpl* lnode::impl() const {
  assert(impl_);
  return impl_;
}

const bitvector& lnode::data() const {
  assert(impl_);
  return impl_->value();
}

bitvector& lnode::data() {
  assert(impl_);
  return impl_->value();
}

void lnode::write(uint32_t dst_offset,
                  const lnode& src,
                  uint32_t src_offset,
                  uint32_t length) {
  assert(impl_);
  auto size = impl_->size();
  assert(this != &src);
  assert(!src.empty());
  assert(size > dst_offset);
  assert(size >= dst_offset + length);
  auto ctx = src.impl()->ctx();

  auto proxy = dynamic_cast<proxyimpl*>(impl_);
  if (nullptr == proxy) {
    proxy = ctx->create_node<proxyimpl>(size);
    // remove new proxy from current block's local list and
    if (ctx->conditional_enabled()) {
      // move it into the local list of the node's def block
      ctx->remove_local_variable(proxy, impl_);
    }
    proxy->add_source(0, impl_, 0, size);
    impl_ = proxy;
  }

  if (ctx->conditional_enabled(proxy)) {
    auto src_impl = src.impl();
    if (src_offset != 0 || src.size() != length) {
      src_impl = ctx->create_node<proxyimpl>(src, src_offset, length);
    }
    ctx->conditional_assign(proxy, dst_offset, length, src_impl);
  } else {
    proxy->add_source(dst_offset, src, src_offset, length);
  }
}

uint32_t lnode::var_id() const {
  assert(impl_);
  return impl_->var_id();
}

const source_location& lnode::sloc() const {
  assert(impl_);
  return impl_->sloc();
}

lnodeimpl* lnode::clone() const {
  assert(impl_);
  return impl_->slice(0, impl_->size());
}

std::ostream& ch::internal::operator<<(std::ostream& out, lnodetype type) {
  out << to_string(type);
  return out;
}

std::ostream& ch::internal::operator<<(std::ostream& out, const lnode& node) {
  out << node.data();
  return out;
}
