#include "system.h"
#include "scint.h"
#include "scuint.h"

using namespace ch::internal;

system_buffer::system_buffer(uint32_t size)
  : value_(size)
  , offset_(0)
  , size_(size)
{}

system_buffer::system_buffer(const bitvector& value,
                             const system_buffer_ptr& source,
                             uint32_t offset,
                             uint32_t size)
  : source_(source)
  , value_(value)
  , offset_(offset)
  , size_(size)
{}

system_buffer::system_buffer(const bitvector& data)
  : value_(data)
  , offset_(0)
  , size_(data.size())
{}

system_buffer::system_buffer(bitvector&& data)
  : value_(std::move(data))
  , offset_(0)
  , size_(value_.size())
{}

system_buffer::system_buffer(uint32_t size,
                             const system_buffer_ptr& buffer,
                             uint32_t offset)
  : source_(buffer)
  , offset_(offset)
  , size_(size) {
  assert(offset_ + size_ <= buffer->size());
}

system_buffer::system_buffer(const system_buffer& other)
  : source_(other.source_)
  , offset_(other.offset_)
  , size_(other.size_) {  
  if (!other.source_)
    value_ = other.value_;
}

system_buffer::system_buffer(system_buffer&& other)
  : source_(std::move(other.source_))
  , value_(std::move(other.value_))
  , offset_(std::move(other.offset_))
  , size_(std::move(other.size_))
{}

system_buffer& system_buffer::operator=(const system_buffer& other) {
  this->copy(0, other, 0, size_);
  return *this;
}

system_buffer& system_buffer::operator=(system_buffer&& other) {
  // disable move for indirect nodes
  if (source_ || value_.size() != size_)
    return this->operator=(other);
  value_  = std::move(other.value_);
  source_ = std::move(other.source_);
  offset_ = std::move(other.offset_);
  size_   = std::move(other.size_);
  return *this;
}

const bitvector& system_buffer::data() const {
  if (source_) {
    if (value_.empty()) {
      value_.resize(size_, 0, true);
    }
    source_->read(offset_, value_.data(), value_.num_bytes(), 0, size_);
  }
  return value_;
}

void system_buffer::copy(uint32_t dst_offset,
                         const system_buffer& src,
                         uint32_t src_offset,
                         uint32_t length) {
  if (src.source()) {
    this->copy(dst_offset, *src.source(), src.offset() + src_offset, length);
  } else {
    this->write(dst_offset,
                src.data().data(),
                src.data().num_bytes(),
                src_offset,
                length);
  }
}

void system_buffer::read(uint32_t src_offset,
                         void* out,
                         uint32_t out_cbsize,
                         uint32_t dst_offset,
                         uint32_t length) const {
  if (source_) {
    source_->read(offset_ + src_offset, out, out_cbsize, dst_offset, length);
  } else {
    assert(src_offset + length <= size_);
    value_.read(src_offset, out, out_cbsize, dst_offset, length);
  }
}

void system_buffer::write(uint32_t dst_offset,
                          const void* in,
                          uint32_t in_cbsize,
                          uint32_t src_offset,
                          uint32_t length) {
  if (source_) {
    source_->write(offset_ + dst_offset, in, in_cbsize, src_offset, length);
  } else {
    assert(dst_offset + length <= size_);
    value_.write(dst_offset, in, in_cbsize, src_offset, length);
  }
}

void system_buffer::write(uint32_t dst_offset,
                          const bitvector& src,
                          uint32_t src_offset,
                          uint32_t length) {
  this->write(dst_offset, src.data(), src.num_bytes(), src_offset, length);
}
