#include "logic.h"
#include "int.h"
#include "uint.h"
#include "proxyimpl.h"

using namespace ch::internal;

logic_buffer::logic_buffer(const lnode& node) : node_(node) {}

logic_buffer::logic_buffer(uint32_t size,
                           const source_location& sloc,
                           const std::string& name)
  : node_(size, sloc, name)
{}

logic_buffer::logic_buffer(const lnode& data,
                           const source_location& sloc,
                           const std::string& name)
  : node_(data, sloc, name)
{}

logic_buffer::logic_buffer(uint32_t size,
                           const logic_buffer& buffer,
                           uint32_t offset,
                           const source_location& sloc,
                           const std::string& name)
  : node_(size,
           buffer.data(),
           offset,
           sloc,
           (name.empty() ? "" : stringf("%s_%s", buffer.data().name().c_str(), name.c_str()))) {
  assert(offset + size <= buffer.size());
}

logic_buffer::logic_buffer(const logic_buffer& other,
                           const source_location& sloc)
  : node_(other.data(), sloc, other.data().name())
{}

logic_buffer::logic_buffer(const logic_buffer& other)
  : node_(other.node_)
{}

logic_buffer::logic_buffer(logic_buffer&& other)
  : node_(std::move(other.node_))
{}

logic_buffer& logic_buffer::operator=(const sdata_type& other) {
  this->write(0, other, 0, other.size(), source_location());
  return *this;
}

logic_buffer& logic_buffer::operator=(const logic_buffer& other) {
  this->write(0, other.data(), 0, other.size(), source_location());
  return *this;
}

logic_buffer& logic_buffer::operator=(logic_buffer&& other) {
  this->operator=(other);
  return *this;
}

void logic_buffer::write(uint32_t dst_offset,
                         const lnode& data,
                         uint32_t src_offset,
                         uint32_t length,
                         const source_location& sloc) {
  node_.write(dst_offset, data, src_offset, length, sloc);
}

logic_buffer logic_buffer::source() const {
  auto proxy = reinterpret_cast<proxyimpl*>(node_.impl());
  return logic_buffer(proxy->src(0));
}
