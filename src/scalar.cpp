#include "scalar.h"
#include "scint.h"
#include "scuint.h"

using namespace ch::internal;

scalar_buffer::scalar_buffer(unsigned size)
  : value_(size)
  , offset_(0)
  , size_(size)
{}

scalar_buffer::scalar_buffer(const scalar_buffer& rhs)
  : source_(rhs.source_)
  , offset_(rhs.offset_)
  , size_(rhs.size_) {
  if (!rhs.source_) {
    value_ = rhs.value_;
  }
}

scalar_buffer::scalar_buffer(scalar_buffer&& rhs)
  : value_(std::move(rhs.value_))
  , source_(std::move(rhs.source_))
  , offset_(std::move(rhs.offset_))
  , size_(std::move(rhs.size_))
{}

scalar_buffer::scalar_buffer(const bitvector& data)
  : value_(data)
  , offset_(0)
  , size_(value_.size())
{}

scalar_buffer::scalar_buffer(bitvector&& data)
  : value_(std::move(data))
  , offset_(0)
  , size_(value_.size())
{}

scalar_buffer::scalar_buffer(unsigned size,
                             const scalar_buffer_ptr& buffer,
                             unsigned offset)
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
