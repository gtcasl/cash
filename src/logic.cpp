#include "logic.h"
#include "int.h"
#include "uint.h"
#include "lnodeimpl.h"

using namespace ch::internal;

static uint32_t make_id() {
  static uint32_t s_id(0);
  uint32_t var_id = ++s_id;
  return var_id;
}

logic_buffer::logic_buffer(uint32_t size,
                           const source_location& sloc,
                           const std::string& name)
  : id_(make_id())
  , value_(size, sloc, name, id_)
  , offset_(0)
{}

logic_buffer::logic_buffer(const lnode& data,
                           const source_location& sloc,
                           const std::string& name)
  : id_(make_id())
  , value_(data.size(), data, 0, sloc, name, id_)
  , offset_(0)
{}

logic_buffer::logic_buffer(uint32_t size,
                           const logic_buffer_ptr& buffer,
                           uint32_t offset,
                           const source_location& sloc,
                           const std::string& name)
  : id_(make_id())
  , value_(size,
           buffer->data(),
           offset,
           sloc,
           (name.empty() ? "" : stringf("%s_%s", buffer->data().name().c_str(), name.c_str())),
           id_)
  , source_(buffer)
  , offset_(offset) {
  assert(offset + size <= buffer->size());
}

logic_buffer::logic_buffer(const logic_buffer& other,
                           const source_location& sloc)
  : id_(make_id())
  , value_(other.size(), other.data(), 0, sloc, other.data().name(), id_)
  , source_(nullptr)
  , offset_(0)
{}

logic_buffer::logic_buffer(logic_buffer&& other)
  : id_(std::move(other.id_))
  , value_(std::move(other.value_))
  , source_(std::move(other.source_))
  , offset_(std::move(other.offset_))
{}

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
  if (source_) {
    source_->write(offset_ + dst_offset, data, src_offset, length, sloc);
  } else {
    value_.write(dst_offset, data, src_offset, length, sloc);
  }
}
