#include "logic.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

logic_buffer::logic_buffer(uint32_t size,  
                           const std::string& name,
                           const source_location& sloc)
  : lnode(ctx_curr()->create_node<proxyimpl>(size, name, sloc))
{}


logic_buffer::logic_buffer(uint32_t size,
                           const logic_buffer& src,
                           uint32_t src_offset,
                           const std::string& name,
                           const source_location& sloc)
  : lnode(ctx_curr()->create_node<refimpl>(
      src.impl(),
      src_offset,
      size,
      ((!src.name().empty() && !name.empty()) ? (src.name() + '.' + name) : ""),
      sloc))
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
  reinterpret_cast<proxyimpl*>(impl_)->write(dst_offset, src.impl(), src_offset, length, impl_->sloc());
}

lnodeimpl* logic_buffer::clone(const std::string& name,
                               const source_location& sloc) const {
  assert(impl_);  
  this->ensure_proxy();
  auto node = reinterpret_cast<proxyimpl*>(impl_)->source(0, impl_->size(), name, sloc);
  if (node != impl_->src(0).impl())
    return node;
  return ctx_curr()->create_node<proxyimpl>(node, name, sloc);
}

lnodeimpl* logic_buffer::sliceref(size_t size, 
                                  size_t start, 
                                  const std::string& name, 
                                  const source_location& sloc) const {
  const_cast<logic_buffer*>(this)->ensure_proxy();
  return ctx_curr()->create_node<refimpl>(impl_, start, size, name, sloc);
}

void logic_buffer::ensure_proxy() const {
  auto impl = impl_;
  if (type_proxy == impl->type())
    return;
  auto proxy = ctx_curr()->create_node<proxyimpl>(impl->size(), "", impl->sloc());
  impl->replace_uses(proxy);
  proxy->write(0, impl, 0, impl->size(), impl->sloc());
}
