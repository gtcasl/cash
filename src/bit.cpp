#include "bit.h"

using namespace ch::internal;

bit_buffer::bit_buffer(unsigned size)
  : src_(size)
  , offset_(0)
  , size_(size)
{}

bit_buffer::bit_buffer(const bit_buffer& rhs)
  : src_(rhs.src_.ensureInitialized(rhs.size_))
  , node_(rhs.node_)
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bit_buffer::bit_buffer(bit_buffer&& rhs)
  : src_(std::move(rhs.src_))
  , node_(std::move(rhs.node_))
  , offset_(rhs.offset_)
  , size_(rhs.size_)
{}

bit_buffer::bit_buffer(const lnode& data)
  : src_(data)
  , offset_(0)
  , size_(src_.get_size()) {
  assert(!data.is_empty());
}

bit_buffer::bit_buffer(lnode&& data)
  : src_(std::move(data))
  , offset_(0)
  , size_(src_.get_size())
{}

bit_buffer::bit_buffer(unsigned size, const bit_buffer& buffer, unsigned offset)
  : src_(buffer.src_.ensureInitialized(buffer.size_))
  , offset_(buffer.offset_ + offset)
  , size_(size) {
  assert(offset_ + size_ <= src_.get_size());
}

bit_buffer& bit_buffer::operator=(const bit_buffer& rhs) {
  src_    = rhs.src_.ensureInitialized(rhs.size_);
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

bit_buffer& bit_buffer::operator=(bit_buffer&& rhs) {
  src_   = std::move(rhs.src_);
  offset_ = rhs.offset_;
  size_   = rhs.size_;
  return *this;
}

void bit_buffer::set_data(const lnode& data) {  
  assert(!data.is_empty());
  src_.write(offset_, data, 0, size_, size_);
}

const lnode& bit_buffer::get_data() const {
  src_.ensureInitialized(size_);
  if (src_.get_size() == size_)
    return src_;
  if (node_.is_empty()) {
    node_ = lnode(size_, src_, offset_);
  }
  return node_;
}

void bit_buffer::write(uint32_t dst_offset, const lnode& data, uint32_t src_offset, uint32_t length) {
  assert(!data.is_empty());
  assert(dst_offset + length <= size_);
  src_.write(offset_ + dst_offset, data, src_offset, length, size_);
}

bit_buffer bit_buffer::clone() const {
  bit_buffer ret(size_);
  ret.write(0, src_.ensureInitialized(size_), offset_, size_);
  return ret;
}

void bit_buffer::copy(const bit_buffer& rhs) {
  assert(size_ == rhs.size_);
  this->write(0, rhs.src_.ensureInitialized(rhs.size_), rhs.offset_, size_);
}
