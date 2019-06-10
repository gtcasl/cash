#include "logic.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

logic_buffer::logic_buffer(uint32_t size,
                           const std::string& name,
                           const sloc_getter&)
  : lnode(size, name)
{}

logic_buffer::logic_buffer(uint32_t size,
                           const logic_buffer& src,
                           uint32_t src_offset,
                           const std::string& name,
                           const sloc_getter&)
  : lnode(src.impl()->ctx()->create_node<refimpl>(
      src.impl(),
      src_offset,
      size,
      ((!src.name().empty() && !name.empty()) ? (src.name() + "." + name) : name),
      get_source_location()))
{}

const logic_buffer& logic_buffer::source() const {
  assert(impl_);
  return reinterpret_cast<const logic_buffer&>(impl_->src(0));
}

logic_buffer& logic_buffer::source() {
  assert(impl_);
  return reinterpret_cast<logic_buffer&>(impl_->mutable_src(0));
}

lnodeimpl* logic_buffer::clone() const {
  assert(impl_);  
  auto sloc = get_source_location();
  const_cast<logic_buffer*>(this)->ensure_proxy();
  if (reinterpret_cast<proxyimpl*>(impl_)->is_identity()) {
    return impl_->ctx()->create_node<proxyimpl>(impl_->src(0).impl(), impl_->name(), sloc);
  } else {
    return impl_->ctx()->create_node<proxyimpl>(impl_, impl_->name(), sloc);
  }
}

lnodeimpl* logic_buffer::sliceref(size_t size, size_t start) const {
  auto sloc = get_source_location();
  const_cast<logic_buffer*>(this)->ensure_proxy();
  return impl_->ctx()->create_node<refimpl>(
        impl_,
        start,
        size,
        (impl_->name() + ".sliceref"),
        sloc);
}
