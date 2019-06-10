#include "lnode.h"
#include "lnodeimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(ch_op op) {
  static const char* sc_names[] = {
    CH_OP_ENUM(CH_OP_NAME)
  };
  return sc_names[CH_OP_INDEX(op)];
}

std::ostream& ch::internal::operator<<(std::ostream& out, ch_op op) {
  out << to_string(op);
  return out;
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode(lnodeimpl* impl) : impl_(impl), next_(nullptr) {
  assert(impl);
  impl->add_user(this);
}

lnode::lnode(const sdata_type& value)
  : lnode(ctx_curr()->create_literal(value))
{}

lnode::lnode(uint32_t size, const std::string& name)
  : lnode(ctx_curr()->create_node<proxyimpl>(size, name, get_source_location()))
{}

lnode::lnode(const lnode& src, const std::string& name)
: lnode(src.impl()->ctx()->create_node<proxyimpl>(
    src.impl(), (name.empty() ? src.name() : name), get_source_location()))
{}

lnode::~lnode() {
  if (impl_) {
    impl_->remove_user(this);
  }
}

lnode& lnode::operator=(const lnode& other) {
  if (impl_) {
    impl_->remove_user(this);
  }
  impl_ = other.impl();
  impl_->add_user(this);
  return *this;
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

const source_location& lnode::sloc() const {
  assert(impl_);
  return impl_->sloc();
}

void lnode::write(uint32_t dst_offset,
                  const lnode& src,
                  uint32_t src_offset,
                  uint32_t length) {
  assert(impl_);
  this->ensure_proxy();
  impl_->write(dst_offset, src.impl(), src_offset, length);
}

void lnode::ensure_proxy() {
  auto impl = impl_;
  if (type_proxy == impl->type())
    return;
  auto proxy = impl->ctx()->create_node<proxyimpl>(impl->size(), impl->name(), impl->sloc());
  impl->replace_uses(proxy);
  proxy->write(0, impl, 0, impl->size());
}

std::ostream& ch::internal::operator<<(std::ostream& out, lnodetype type) {
  out << to_string(type);
  return out;
}
