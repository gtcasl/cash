#include "bit.h"

using namespace ch::internal;

bit_buffer::bit_buffer(unsigned size)
  : source_(size)
  , offset_(0)
  , size_(size)
{}

bit_buffer::bit_buffer(const bit_buffer& rhs)
  : source_(rhs.source_.ensureInitialized(rhs.size_))
  , proxy_(rhs.proxy_)
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bit_buffer::bit_buffer(bit_buffer&& rhs)
  : source_(std::move(rhs.source_))
  , proxy_(std::move(rhs.proxy_))
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bit_buffer::bit_buffer(const lnode& data)
  : source_(data)
  , offset_(0)
  , size_(source_.get_size()) {
  assert(!data.is_empty());
}

bit_buffer::bit_buffer(lnode&& data)
  : source_(std::move(data))
  , offset_(0)
  , size_(source_.get_size())
{}

bit_buffer::bit_buffer(unsigned size, const bit_buffer& buffer, unsigned offset)
  : source_(buffer.source_.ensureInitialized(buffer.size_))
  , offset_(buffer.offset_ + offset)
  , size_(size) {
  assert(offset_ + size_ <= source_.get_size());
}

bit_buffer& bit_buffer::operator=(const bit_buffer& rhs) {
  source_ = rhs.source_.ensureInitialized(rhs.size_);
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

bit_buffer& bit_buffer::operator=(bit_buffer&& rhs) {
  source_ = std::move(rhs.source_);
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

const lnode& bit_buffer::get_source() const {
  source_.ensureInitialized(size_);
  return source_;
}

lnode& bit_buffer::get_source() {
  source_.ensureInitialized(size_);
  return source_;
}

void bit_buffer::set_data(const lnode& data) {  
  assert(!data.is_empty());
  source_.write(offset_, data, 0, size_, size_);
}

const lnode& bit_buffer::get_data() const {
  source_.ensureInitialized(size_);
  if (source_.get_size() == size_)
    return source_;
  if (proxy_.is_empty()) {
    proxy_ = lnode(size_, source_, offset_);
  }
  return proxy_;
}

void bit_buffer::write(uint32_t dst_offset, const lnode& data, uint32_t src_offset, uint32_t length) {
  assert(!data.is_empty());
  assert(dst_offset + length <= size_);
  source_.write(offset_ + dst_offset, data, src_offset, length, size_);
}
