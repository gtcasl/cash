#include "logic.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

logic_buffer::logic_buffer(uint32_t size,
                           const std::string& name,
                           const sloc_getter&)
  : lnode(size, name)
{}

logic_buffer::logic_buffer(const lnode& node,
                           const std::string& name,
                           const sloc_getter&)
  : lnode(node, name)
{}

logic_buffer::logic_buffer(uint32_t size,
                           const logic_buffer& src,
                           uint32_t src_offset,
                           const std::string& name,
                           const sloc_getter&) {
  auto sloc = get_source_location();
  auto full_name = (!src.name().empty() && !name.empty()) ? (src.name() + "." + name) : name;
  impl_ = src.impl()->ctx()->create_node<refimpl>(
        src, src_offset, size, sloc, full_name);
}

const logic_buffer& logic_buffer::source() const {
  assert(impl_);
  return reinterpret_cast<const logic_buffer&>(impl_->src(0));
}

logic_buffer& logic_buffer::source() {
  assert(impl_);
  return reinterpret_cast<logic_buffer&>(impl_->mutable_src(0));
}

lnode logic_buffer::clone() const {
  assert(impl_);
  auto sloc = get_source_location();
  return impl_->slice(0, impl_->size(), sloc);
}
