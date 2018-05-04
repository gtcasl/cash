#include "lnodeimpl.h"
#include "ioimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "tickable.h"
#include "regimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(lnodetype type) {
  static const char* sc_names[] = {
    CH_LNODE_ENUM(CH_LNODE_NAME)
  };
  return sc_names[CH_LNODE_INDEX(type)];
}

lnodeimpl::lnodeimpl(context* ctx,
                     lnodetype type,
                     uint32_t size,
                     unsigned var_id,
                     const std::string& name,
                     const source_location& sloc)
  : ctx_(ctx)
  , id_(ctx->node_id())
  , type_(type)
  , value_(size)
  , var_id_(var_id)
  , name_(to_string(type))
  , sloc_(sloc) {
  if (!name.empty()) {
    name_ = name;
  }
}

lnodeimpl::~lnodeimpl() {}

unsigned lnodeimpl::add_src(unsigned index, const lnode& src) {
  if (0xffffffff == index) {
    // add first entry
    index = srcs_.size();
    srcs_.push_back(src);
  } else {
    // override existing entry
    srcs_[index] = src;
  }
  return index;
}

bool lnodeimpl::equals(const lnodeimpl& rhs) const {
  if (this->type() == rhs.type()
   && this->size() == rhs.size()
   && this->srcs().size() == rhs.srcs().size()) {
    for (unsigned i = 0, n = this->srcs().size(); i < n; ++i) {
      if (this->src(i).id() != rhs.src(i).id())
        return false;
    }
    return true;
  }
  return false;
}

lnodeimpl* lnodeimpl::slice(uint32_t offset, uint32_t length) {
  assert(length <= value_.size());
  if (value_.size() == length)
    return this;
  return ctx_->create_node<proxyimpl>(this, offset, length);
}

void lnodeimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << this->type() << value_.size();
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0)
        out << ", ";
      out << "#" << srcs_[i].id();
    }
    out << ")";
  }
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

undefimpl::undefimpl(context* ctx, uint32_t size)
  : lnodeimpl(ctx, type_undef, size)
{}

const bitvector& undefimpl::eval(ch_tick) {
  CH_ABORT("undefined node: %s!", name_.c_str());
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

lnode::lnode() : impl_(nullptr) {}

lnode::lnode(const lnode& rhs) : impl_(rhs.impl_) {}

lnode::lnode(uint32_t size,
             unsigned var_id,
             const std::string& name,
             const source_location& sloc) {
  impl_ = ctx_curr()->create_node<proxyimpl>(
            ctx_curr()->create_node<undefimpl>(size), 0, size, var_id, name, sloc);
}

lnode::lnode(uint32_t size,
             const lnode& src,
             unsigned src_offset,
             unsigned var_id,
             const std::string& name,
             const source_location& sloc) {
  assert(!src.empty());
  impl_ = src.ctx()->create_node<proxyimpl>(
        src, src_offset, size, var_id, name, sloc);
}

lnode::lnode(lnodeimpl* impl) : impl_(impl) {
  assert(impl);
}

lnode::lnode(const bitvector& value) {
  impl_ = ctx_curr()->literal(value);
}

lnode::~lnode() {
  this->clear();
}

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

context* lnode::ctx() const {
  assert(impl_);
  return impl_->ctx();
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

void lnode::clear() {
  impl_ = nullptr;
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
  auto ctx = src.ctx();

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

const bitvector& lnode::eval(ch_tick t) const {
  assert(impl_);
  return impl_->eval(t);
}

std::ostream& ch::internal::operator<<(std::ostream& out, lnodetype type) {
  out << to_string(type);
  return out;
}

std::ostream& ch::internal::operator<<(std::ostream& out, const lnode& node) {
  out << node.data();
  return out;
}
