#include "scalar.h"
#include "scint.h"
#include "scuint.h"

using namespace ch::internal;

scalar_buffer::scalar_buffer(uint32_t size)
  : value_(size)
  , offset_(0)
  , size_(size)
{}

scalar_buffer::scalar_buffer(const scalar_buffer& other)
  : source_(other.source_)
  , offset_(other.offset_)
  , size_(other.size_) {
  if (!other.source_) {
    value_ = other.value_;
  }
}

scalar_buffer::scalar_buffer(const bitvector& value,
                             const scalar_buffer_ptr& source,
                             uint32_t offset,
                             uint32_t size)
  : value_(value)
  , source_(source)
  , offset_(offset)
  , size_(size)
{}

scalar_buffer::scalar_buffer(const bitvector& data)
  : value_(data)
  , offset_(0)
  , size_(data.size())
{}

scalar_buffer::scalar_buffer(bitvector&& data)
  : value_(std::move(data))
  , offset_(0)
  , size_(value_.size())
{}

void scalar_buffer::copy(const scalar_buffer& other) {
  this->write(0,
              other.data().words(),
              other.data().cbsize(),
              other.offset(),
              other.size());
}

void scalar_buffer::move(scalar_buffer&& other) {
  // disable move for indirect nodes
  if (source_ || size_ != value_.size()) {
    this->copy(other);
  } else {
    value_  = std::move(other.value_);
    source_ = std::move(other.source_);
    offset_ = std::move(other.offset_);
    size_   = std::move(other.size_);
  }
}

void scalar_buffer::write(uint32_t dst_offset,
                          const bitvector& src,
                          uint32_t src_offset,
                          uint32_t length) {
  this->write(dst_offset, src.words(), src.cbsize(), src_offset, length);
}

scalar_buffer::scalar_buffer(uint32_t size,
                             const scalar_buffer_ptr& buffer,
                             uint32_t offset)
  : source_(buffer)
  , offset_(offset)
  , size_(size) {
  assert(offset_ + size_ <= buffer->size());
}

const bitvector& scalar_buffer::data() const {
  if (source_) {
    if (value_.empty()) {
      value_.resize(size_, 0, true);
    }
    source_->read(0, value_.words(), value_.cbsize(), offset_, size_);
  }
  return value_;
}

void scalar_buffer::read(uint32_t dst_offset,
                         void* out,
                         uint32_t out_cbsize,
                         uint32_t src_offset,
                         uint32_t length) const {
  if (source_) {
    source_->read(dst_offset, out, out_cbsize, offset_ + src_offset, length);
  } else {
    assert(dst_offset + length <= size_);
    value_.read(dst_offset, out, out_cbsize, src_offset, length);
  }
}

void scalar_buffer::write(uint32_t dst_offset,
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
  }
}
