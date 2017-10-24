#include "scalar.h"

using namespace ch::internal;

scalar_buffer_impl::scalar_buffer_impl(unsigned size)
  : value_(size)
  , offset_(0)
  , size_(size)  
  , version_(0)
{}

scalar_buffer_impl::scalar_buffer_impl(const scalar_buffer_impl& rhs)
  : source_(rhs.source_)
  , offset_(rhs.offset_)
  , size_(rhs.size_)
  , version_(0) {
  if (!rhs.source_) {
    value_ = rhs.value_;
  }
}

scalar_buffer_impl::scalar_buffer_impl(scalar_buffer_impl&& rhs)
  : source_(std::move(rhs.source_))
  , value_(std::move(rhs.value_))
  , offset_(rhs.offset_)
  , size_(rhs.size_)
  , version_(rhs.version_)
{}

scalar_buffer_impl::scalar_buffer_impl(const bitvector& data)
  : value_(data)
  , offset_(0)
  , size_(value_.get_size())
  , version_(1)
{}

scalar_buffer_impl::scalar_buffer_impl(bitvector&& data)
  : value_(std::move(data))
  , offset_(0)
  , size_(value_.get_size())
  , version_(1)
{}

scalar_buffer_impl::scalar_buffer_impl(unsigned size,
                                       const scalar_buffer_ptr& buffer,
                                       unsigned offset)
  : source_(buffer)
  , offset_(offset)
  , size_(size)
  , version_(0) {
  assert(offset_ + size_ <= buffer->get_size());
}

scalar_buffer_impl& scalar_buffer_impl::operator=(const scalar_buffer_impl& rhs) {
  source_ = rhs.source_;
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  if (!rhs.source_) {
    value_ = rhs.value_;
  }
  ++version_;
  return *this;
}

scalar_buffer_impl& scalar_buffer_impl::operator=(scalar_buffer_impl&& rhs) {
  if (source_ || rhs.source_) {
    this->copy(rhs);
  } else {
    value_  = std::move(rhs.value_);
    offset_ = rhs.offset_;
    size_   = rhs.size_;
    ++version_;
  }
  return *this;
}

void scalar_buffer_impl::set_data(const bitvector& data) {
  this->write(0, data.get_words(), data.get_cbsize(), 0, size_);
}

const bitvector& scalar_buffer_impl::get_data() const {
  if (source_) {
    const auto& data = source_->get_data();
    if (source_->version_ != version_) {
      if (value_.is_empty()) {
        value_.resize(size_, 0, true);
      }
      value_.copy(0, data, offset_, size_);
      version_ = source_->version_;
    }
  }
  return value_;
}

void scalar_buffer_impl::copy(const scalar_buffer_impl& rhs) {
  this->write(0,
              rhs.get_data().get_words(),
              rhs.get_data().get_cbsize(),
              rhs.get_offset(),
              rhs.get_size());
}

void scalar_buffer_impl::read(uint32_t dst_offset,
                              void* out,
                              uint32_t out_cbsize,
                              uint32_t src_offset,
                              uint32_t length) const {
  if (source_) {
    source_->read(offset_ + dst_offset, out, out_cbsize, src_offset, length);
  } else {
    assert(dst_offset + length <= size_);
    value_.read(dst_offset, out, out_cbsize, src_offset, length);
  }
}

void scalar_buffer_impl::write(uint32_t dst_offset,
                               const void* in,
                               uint32_t in_cbsize,
                               uint32_t src_offset,
                               uint32_t length) {
  if (source_) {
    source_->write(offset_ + dst_offset, in, in_cbsize, src_offset, length);
  } else {
    assert(dst_offset + length <= size_);
    assert(0 == offset_);
    value_.write(dst_offset, in, in_cbsize, src_offset, length);
    ++version_;
  }
}
