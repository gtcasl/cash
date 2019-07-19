#include "logic.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

logic_buffer::logic_buffer(uint32_t size, const std::string& name)
  : lnode(size, name)
{}

logic_buffer::logic_buffer(uint32_t size,
                           const logic_buffer& src,
                           uint32_t src_offset,
                           const std::string& name)
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

void logic_buffer::write(uint32_t dst_offset,
                         const lnode& src,
                         uint32_t src_offset,
                         uint32_t length) {
  assert(impl_);
  this->ensure_proxy();
  impl_->write(dst_offset, src.impl(), src_offset, length);
}

lnodeimpl* logic_buffer::clone() const {
  assert(impl_);  
  auto sloc = get_source_location();
  const_cast<logic_buffer*>(this)->ensure_proxy();
  auto source = reinterpret_cast<proxyimpl*>(impl_)->source(0, impl_->size(), sloc);
  return impl_->ctx()->create_node<proxyimpl>(source, impl_->name(), sloc);
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

void logic_buffer::ensure_proxy() {
  auto impl = impl_;
  if (type_proxy == impl->type())
    return;
  auto proxy = impl->ctx()->create_node<proxyimpl>(impl->size(), impl->name(), impl->sloc());
  impl->replace_uses(proxy);
  proxy->write(0, impl, 0, impl->size());
}
