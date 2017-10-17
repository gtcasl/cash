#include "scalar.h"

using namespace ch::internal;

bytes_store::bytes_store(unsigned size)
  : buffer_(std::make_shared<bitvector>(size))
  , offset_(0)
  , size_(size)
{}

bytes_store::bytes_store(const bytes_store& rhs)
  : buffer_(rhs.buffer_)
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bytes_store::bytes_store(bytes_store&& rhs)
  : buffer_(std::move(rhs.buffer_))
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bytes_store::bytes_store(const bitvector& value)
  : buffer_(std::make_shared<bitvector>(value))
  , offset_(0)
  , size_(buffer_->get_size())
{}

bytes_store::bytes_store(bitvector&& value)
  : buffer_(std::make_shared<bitvector>(std::move(value)))
  , offset_(0)
  , size_(buffer_->get_size())
{}

bytes_store::bytes_store(unsigned size, const bytes_store& store, unsigned offset)
  : buffer_(store.buffer_)
  , offset_(store.offset_ + offset)
  , size_(size) {
  assert(offset_ + size_ <= buffer_->get_size());
}

bytes_store& bytes_store::operator=(const bytes_store& rhs) {
  buffer_ = rhs.buffer_;
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

bytes_store& bytes_store::operator=(bytes_store&& rhs) {
  buffer_ = std::move(rhs.buffer_);
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

void bytes_store::set_value(const bitvector& value) {
  buffer_->copy(offset_, value, 0, size_);
}

const bitvector& bytes_store::get_value() const {
  if (buffer_->get_size() == size_)
    return *buffer_;
  proxy_.resize(size_);
  proxy_.copy(0, *buffer_, offset_, size_);
  return proxy_;
}

void bytes_store::read(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const {
  assert(src_offset + length <= size_);
  assert(offset_ + src_offset + length <= buffer_->get_size());
  buffer_->read(dst_offset, out, out_cbsize, offset_ + src_offset, length);
}

void bytes_store::write(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
  assert(dst_offset + length <= size_);
  assert(offset_ + dst_offset + length <= buffer_->get_size());
  buffer_->write(offset_ + dst_offset, in, in_cbsize, src_offset, length);
}

bytes_store bytes_store::clone() const {
  bytes_store ret(size_);
  ret.write(0, buffer_->get_words(), buffer_->get_cbsize(), offset_, size_);
  return ret;
}

void bytes_store::copy(const bytes_store& rhs) {
  assert(size_ == rhs.size_);
  this->write(offset_, rhs.buffer_->get_words(), rhs.buffer_->get_cbsize(), rhs.offset_, size_);
}
