#include "scalar.h"

using namespace ch::internal;

scalar_buffer::scalar_buffer(unsigned size)
  : buffer_(std::make_shared<bitvector>(size))
  , offset_(0)
  , size_(size)
{}

scalar_buffer::scalar_buffer(const scalar_buffer& rhs)
  : buffer_(rhs.buffer_)
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

scalar_buffer::scalar_buffer(scalar_buffer&& rhs)
  : buffer_(std::move(rhs.buffer_))
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

scalar_buffer::scalar_buffer(const bitvector& value)
  : buffer_(std::make_shared<bitvector>(value))
  , offset_(0)
  , size_(buffer_->get_size())
{}

scalar_buffer::scalar_buffer(bitvector&& value)
  : buffer_(std::make_shared<bitvector>(std::move(value)))
  , offset_(0)
  , size_(buffer_->get_size())
{}

scalar_buffer::scalar_buffer(unsigned size, const scalar_buffer& buffer, unsigned offset)
  : buffer_(buffer.buffer_)
  , offset_(buffer.offset_ + offset)
  , size_(size) {
  assert(offset_ + size_ <= buffer_->get_size());
}

scalar_buffer& scalar_buffer::operator=(const scalar_buffer& rhs) {
  buffer_ = rhs.buffer_;
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

scalar_buffer& scalar_buffer::operator=(scalar_buffer&& rhs) {
  buffer_ = std::move(rhs.buffer_);
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

void scalar_buffer::set_value(const bitvector& value) {
  buffer_->copy(offset_, value, 0, size_);
}

const bitvector& scalar_buffer::get_value() const {
  if (buffer_->get_size() == size_)
    return *buffer_;
  proxy_.resize(size_);
  proxy_.copy(0, *buffer_, offset_, size_);
  return proxy_;
}

void scalar_buffer::read(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const {
  assert(src_offset + length <= size_);
  assert(offset_ + src_offset + length <= buffer_->get_size());
  buffer_->read(dst_offset, out, out_cbsize, offset_ + src_offset, length);
}

void scalar_buffer::write(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
  assert(dst_offset + length <= size_);
  assert(offset_ + dst_offset + length <= buffer_->get_size());
  buffer_->write(offset_ + dst_offset, in, in_cbsize, src_offset, length);
}

scalar_buffer scalar_buffer::clone() const {
  scalar_buffer ret(size_);
  ret.write(0, buffer_->get_words(), buffer_->get_cbsize(), offset_, size_);
  return ret;
}

void scalar_buffer::copy(const scalar_buffer& rhs) {
  assert(size_ == rhs.size_);
  this->write(offset_, rhs.buffer_->get_words(), rhs.buffer_->get_cbsize(), rhs.offset_, size_);
}
