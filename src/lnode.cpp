#include "lnode.h"
#include "lnodeimpl.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(ch_op op) {
  static const char* sc_names[] = {
    CH_OP_ENUM(CH_OP_NAME)
  };
  return sc_names[CH_OP_INDEX(op)];
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode() : impl_(nullptr) {}

lnode::lnode(lnodeimpl* impl) : impl_(impl) {
  assert(impl);
}

lnode::lnode(const bitvector& value) {
  impl_ = ctx_curr()->literal(value);
}

lnode::lnode(uint32_t size,
             const source_location& sloc,
             const std::string& name,
             uint32_t var_id) {
  impl_ = ctx_curr()->create_node<proxyimpl>(
            ctx_curr()->create_node<undefimpl>(size, sloc),
            0, size, sloc, name, var_id);
}

lnode::lnode(const lnode& src,
             const source_location& sloc,
             const std::string& name,
             uint32_t var_id) {
  impl_ = src.impl()->ctx()->create_node<proxyimpl>(
                src, 0, src.size(), sloc, name, var_id);
}

lnode::lnode(uint32_t size,
             const lnode& src,
             uint32_t src_offset,
             const source_location& sloc,
             const std::string& name,
             uint32_t var_id) {
  impl_ = src.impl()->ctx()->create_node<refimpl>(
            src, src_offset, size, sloc, name, var_id);
}

lnode::lnode(const lnode& other) : impl_(other.impl_) {}

lnode::~lnode() {}

lnode& lnode::operator=(const lnode& other) {
  impl_ = other.impl_;
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
                  uint32_t length,
                  const source_location& sloc) {
  assert(impl_);
  impl_->write(dst_offset, src, src_offset, length, sloc);
}

uint32_t lnode::var_id() const {
  assert(impl_);
  return impl_->var_id();
}

const source_location& lnode::sloc() const {
  assert(impl_);
  return impl_->sloc();
}

lnodeimpl* lnode::clone(const source_location& sloc) const {
  assert(impl_);
  return impl_->slice(0, impl_->size(), sloc);
}

std::ostream& ch::internal::operator<<(std::ostream& out, lnodetype type) {
  out << to_string(type);
  return out;
}
