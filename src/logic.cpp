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

logic_buffer::logic_buffer(const lnode& value,
                           const logic_buffer_ptr& source,
                           uint32_t offset)
  : id_(make_id())
  , value_(value)
  , source_(source)
  , offset_(offset)
{}

logic_buffer::logic_buffer(uint32_t size,
                           const source_location& sloc,
                           const std::string& name)
  : id_(make_id())
  , value_(size, id_, name, sloc)
  , offset_(0)
{}

logic_buffer::logic_buffer(const logic_buffer& rhs,
                           const source_location& sloc,
                           const std::string& name)
  : id_(make_id())
  , value_(rhs.size(), rhs.data(), 0, id_, name, sloc)
  , offset_(0) {
  if (!sloc.empty()) {
    this->update_sloc(sloc);
  }
}

logic_buffer::logic_buffer(logic_buffer&& rhs)
  : id_(std::move(rhs.id_))
  , value_(std::move(rhs.value_))
  , source_(std::move(rhs.source_))
  , offset_(std::move(rhs.offset_))
{}

logic_buffer::logic_buffer(const lnode& data,
                           const source_location& sloc,
                           const std::string& name)
  : id_(make_id())
  , value_(data.size(), data, 0, id_, name, sloc)
  , offset_(0) {
  if (!sloc.empty()) {
    this->update_sloc(sloc);
  }
}

logic_buffer::logic_buffer(uint32_t size,
                           const logic_buffer_ptr& buffer,
                           uint32_t offset,
                           const source_location& sloc,
                           const std::string& name)
  : id_(make_id())
  , value_(size,
           buffer->data(),
           offset,
           id_,
           (name.empty() ? "" : stringf("%s_%s", buffer->data().name().c_str(), name.c_str())),
           sloc)
  , source_(buffer)
  , offset_(offset) {
  assert(offset + size <= buffer->size());  
  if (!sloc.empty()) {
    this->update_sloc(sloc);
  }
}

void logic_buffer::update_sloc(const source_location& sloc) {
  value_.impl()->update_sloc(sloc);
  if (!!source_) {
    source_->update_sloc(sloc);
  }
}

logic_buffer& logic_buffer::operator=(const logic_buffer& rhs) {
  this->write(0, rhs.data(), 0, rhs.size());
  return *this;
}

logic_buffer& logic_buffer::operator=(logic_buffer&& rhs) {
  this->write(0, rhs.data(), 0, rhs.size());
  return *this;
}

void logic_buffer::write(uint32_t dst_offset,
                         const lnode& data,
                         uint32_t src_offset,
                         uint32_t length) {
  if (source_) {
    source_->write(offset_ + dst_offset, data, src_offset, length);
  } else {
    value_.write(dst_offset, data, src_offset, length);
  }
}
