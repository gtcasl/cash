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

lnode::lnode(const sdata_type& value) {
  impl_ = ctx_curr()->create_literal(value);
}

lnode::lnode(uint32_t size, const std::string& name) {
  auto sloc = get_source_location();
  impl_ = ctx_curr()->create_node<proxyimpl>(size, name, sloc);
}

lnode::lnode(const lnode& src, const std::string& name) {
  auto sloc = get_source_location();
  impl_ = src.impl()->ctx()->create_node<proxyimpl>(
                src, (name.empty() ? src.name() : name), sloc);
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

const source_location& lnode::sloc() const {
  assert(impl_);
  return impl_->sloc();
}

void lnode::write(uint32_t dst_offset,
                  const lnode& src,
                  uint32_t src_offset,
                  uint32_t length) {
  assert(impl_);
  impl_->write(dst_offset, src, src_offset, length);
}

std::ostream& ch::internal::operator<<(std::ostream& out, lnodetype type) {
  out << to_string(type);
  return out;
}
