#include "bit.h"

using namespace ch::internal;

bit_buffer_impl::bit_buffer_impl(unsigned size,
                                 const source_location& sloc,
                                 const std::string& name)
  : value_(size)
  , offset_(0) {
  value_.set_source_location(sloc);  
  if (!name.empty())
    value_.set_name(name);
}

bit_buffer_impl::bit_buffer_impl(const bit_buffer_impl& rhs,
                                 const source_location& sloc,
                                 const std::string& name)
  : value_(rhs.get_size(), rhs.get_data())
  , offset_(0) {
  value_.set_source_location(sloc);
  if (!name.empty())
    value_.set_name(name);
}

bit_buffer_impl::bit_buffer_impl(bit_buffer_impl&& rhs)
  : value_(std::move(rhs.value_))
  , source_(std::move(rhs.source_))
  , offset_(std::move(offset_))
{}

bit_buffer_impl::bit_buffer_impl(const lnode& data,
                                 const source_location& sloc,
                                 const std::string& name)
  : value_(data.get_size(), data)
  , offset_(0) {
  value_.set_source_location(sloc);
  if (!name.empty())
    value_.set_name(name);
}

bit_buffer_impl::bit_buffer_impl(unsigned size,
                                 const bit_buffer_ptr& buffer,
                                 unsigned offset,
                                 const std::string& name)
  : value_(size, buffer->get_data(), offset)
  , source_(buffer)
  , offset_(offset) {
  assert(offset + size <= buffer->get_size());
  value_.set_source_location(buffer->get_data().get_source_location());
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
