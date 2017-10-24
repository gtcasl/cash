#include "bit.h"

using namespace ch::internal;

bit_buffer_impl::bit_buffer_impl(unsigned size)
  : value_(size)
  , offset_(0)
  , size_(size)
{}

bit_buffer_impl::bit_buffer_impl(const bit_buffer_impl& rhs)
  : source_(rhs.source_)
  , value_(rhs.value_)
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bit_buffer_impl::bit_buffer_impl(bit_buffer_impl&& rhs)
  : source_(std::move(rhs.source_))
  , value_(std::move(rhs.value_))
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bit_buffer_impl::bit_buffer_impl(const lnode& data)
  : value_(data)
  , offset_(0)
  , size_(value_.get_size())
{}

bit_buffer_impl::bit_buffer_impl(lnode&& data)
  : value_(std::move(data))
  , offset_(0)
  , size_(value_.get_size())
{}

bit_buffer_impl::bit_buffer_impl(unsigned size,
                                 const bit_buffer_ptr& buffer,
                                 unsigned offset)
  : source_(buffer)
  , offset_(offset)
  , size_(size) {
  assert(offset_ + size_ <= buffer->get_size());
}

bit_buffer_impl& bit_buffer_impl::operator=(const bit_buffer_impl& rhs) {
  source_ = rhs.source_;
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  if (source_) {
    value_.clear();
  } else {
    value_ = rhs.value_;
  }
  return *this;
}

bit_buffer_impl& bit_buffer_impl::operator=(bit_buffer_impl&& rhs) {
  if (source_ || rhs.source_) {
    this->write(0, rhs, 0, size_);
  } else {
    value_.move(rhs.value_);
    offset_ = rhs.offset_;
    size_   = rhs.size_;
  }
  return *this;
}

void bit_buffer_impl::set_data(const lnode& data) {
  this->write(0, data, 0, size_);
}

const lnode& bit_buffer_impl::get_data() const {
  if (source_) {
    if (value_.is_empty()) {
      value_ = lnode(size_, source_->get_data(), offset_);
    }
  } else {
    value_.ensureInitialized(size_);
  }
  return value_;
}

void bit_buffer_impl::write(uint32_t dst_offset,
                            const lnode& data,
                            uint32_t src_offset,
                            uint32_t length) {
  if (source_) {
    source_->write(offset_ + dst_offset, data, src_offset, length);
  } else {
    assert(dst_offset + length <= size_);
    assert(0 == offset_);
    value_.write(dst_offset, data, src_offset, length, size_);
  }
}

void bit_buffer_impl::write(uint32_t dst_offset,
                            const bit_buffer_impl& src,
                            uint32_t src_offset,
                            uint32_t length) {
  this->write(dst_offset, src.get_data(), src_offset, length);
}
