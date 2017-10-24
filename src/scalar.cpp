#include "scalar.h"

using namespace ch::internal;

scalar_buffer::scalar_buffer(unsigned size)
  : source_(std::make_shared<source_t>(size, 1))
  , offset_(0)
  , size_(size)  
  , version_(0)
{}

scalar_buffer::scalar_buffer(const scalar_buffer& rhs)
  : source_(rhs.source_)  
  , offset_(rhs.offset_)
  , size_(rhs.size_)
  , version_(0)
{}

scalar_buffer::scalar_buffer(scalar_buffer&& rhs)
  : source_(std::move(rhs.source_))
  , offset_(rhs.offset_)
  , size_(rhs.size_)
  , version_(0)
{}

scalar_buffer::scalar_buffer(const bitvector& data)
  : source_(std::make_shared<source_t>(data, 1))
  , offset_(0)
  , size_(source_->first.get_size())
  , version_(0)
{}

scalar_buffer::scalar_buffer(bitvector&& data)
  : source_(std::make_shared<source_t>(std::move(data), 1))
  , offset_(0)
  , size_(source_->first.get_size())
  , version_(0)
{}

scalar_buffer::scalar_buffer(unsigned size, const scalar_buffer& buffer, unsigned offset)
  : source_(buffer.source_)
  , offset_(buffer.offset_ + offset)
  , size_(size)
  , version_(0) {
  assert(offset_ + size_ <= source_->first.get_size());
}

scalar_buffer& scalar_buffer::operator=(const scalar_buffer& rhs) {
  source_ = rhs.source_;
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  cache_.clear();
  version_= 0;
  return *this;
}

scalar_buffer& scalar_buffer::operator=(scalar_buffer&& rhs) {
  source_ = std::move(rhs.source_);
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  cache_.clear();
  version_= 0;
  return *this;
}

void scalar_buffer::set_data(const bitvector& data) {
  source_->first.copy(offset_, data, 0, size_);
  ++source_->second;
}

const bitvector& scalar_buffer::get_data() const {
  if (source_->first.get_size() == size_)
    return source_->first;
  if (version_ != source_->second) {
    if (cache_.is_empty()) {
      cache_.resize(size_, 0, true);
    }
    cache_.copy(0, source_->first, offset_, size_);
    version_ = source_->second;
  }
  return cache_;
}

void scalar_buffer::read(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const {
  assert(src_offset + length <= size_);
  assert(offset_ + src_offset + length <= source_->first.get_size());
  source_->first.read(dst_offset, out, out_cbsize, offset_ + src_offset, length);
}

void scalar_buffer::write(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
  assert(dst_offset + length <= size_);
  assert(offset_ + dst_offset + length <= source_->first.get_size());
  source_->first.write(offset_ + dst_offset, in, in_cbsize, src_offset, length);
  ++source_->second;
}

bool scalar_buffer::is_slice() const {
  return (size_ < source_->first.get_size());
}
