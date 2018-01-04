#include "bit.h"

using namespace ch::internal;

static uint32_t make_id() {
  static uint32_t s_id(0);
  uint32_t var_id = ++s_id;
  return var_id;
}

bit_buffer_impl::bit_buffer_impl(const lnode& value,
                                 const bit_buffer_ptr& source,
                                 unsigned offset)
  : id_(make_id())
  , value_(value)
  , source_(source)
  , offset_(offset)
{}

bit_buffer_impl::bit_buffer_impl(unsigned size,
                                 const source_location& sloc,
                                 const std::string& name)
  : id_(make_id())
  , value_(size)
  , offset_(0) {
  value_.set_var_id(id_);
  value_.set_source_location(sloc);  
  if (!name.empty())
    value_.set_name(name);
}

bit_buffer_impl::bit_buffer_impl(const bit_buffer_impl& rhs,
                                 const source_location& sloc,
                                 const std::string& name)
  : id_(make_id())
  , value_(rhs.get_size(), rhs.get_data())
  , offset_(0) {
  value_.set_var_id(id_);
  value_.set_source_location(sloc);
  if (!name.empty())
    value_.set_name(name);
}

bit_buffer_impl::bit_buffer_impl(bit_buffer_impl&& rhs)
  : id_(std::move(rhs.id_))
  , value_(std::move(rhs.value_))
  , source_(std::move(rhs.source_))
  , offset_(std::move(rhs.offset_))
{}

bit_buffer_impl::bit_buffer_impl(const lnode& data,
                                 const source_location& sloc,
                                 const std::string& name)
  : id_(make_id())
  , value_(data.get_size(), data)
  , offset_(0) {
  value_.set_var_id(id_);
  value_.set_source_location(sloc);
  if (!name.empty())
    value_.set_name(name);
}

bit_buffer_impl::bit_buffer_impl(unsigned size,
                                 const bit_buffer_ptr& buffer,
                                 unsigned offset,
                                 const source_location& sloc,
                                 const std::string& name)
  : id_(make_id())
  , value_(size, buffer->get_data(), offset)
  , source_(buffer)
  , offset_(offset) {
  assert(offset + size <= buffer->get_size());
  value_.set_var_id(id_);
  value_.set_source_location(sloc);
  if (!name.empty()) {
    assert(!buffer->get_data().get_name().empty());
    value_.set_name(fstring("%s_%s", buffer->get_data().get_name().c_str(), name.c_str()));
  }
}

bit_buffer_impl& bit_buffer_impl::operator=(const bit_buffer_impl& rhs) {
  this->copy(rhs);
  return *this;
}

bit_buffer_impl& bit_buffer_impl::operator=(bit_buffer_impl&& rhs) {
  this->copy(rhs);
  return *this;
}

void bit_buffer_impl::write(uint32_t dst_offset,
                            const lnode& data,
                            uint32_t src_offset,
                            uint32_t length) {
  if (source_) {
    source_->write(offset_ + dst_offset, data, src_offset, length);
  } else {
    value_.write(dst_offset, data, src_offset, length);
  }
}
