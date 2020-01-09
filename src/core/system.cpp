#include "system.h"

using namespace ch::internal;

system_buffer_impl::system_buffer_impl(const sdata_type& data)
  : value_(data)
  , offset_(0)
  , size_(data.size())
{}

system_buffer_impl::system_buffer_impl(sdata_type&& data)
  : value_(std::move(data))
  , offset_(0)
  , size_(value_.size())
{}

system_buffer_impl::system_buffer_impl(uint32_t size, const std::string& name)
  : value_(size)
  , offset_(0)
  , size_(size)
  , name_(name)
{}

system_buffer_impl::system_buffer_impl(uint32_t size,
                             const system_buffer& buffer,
                             uint32_t offset,
                             const std::string& name)
  : source_(buffer)
  , offset_(offset)
  , size_(size)
  , name_(((!buffer->name().empty() && !name.empty()) ? (buffer->name() + '.' + name) : name)) {
  assert(offset_ + size_ <= buffer->size());
}

system_buffer_impl::system_buffer_impl(const system_buffer_impl& other)
  : source_(other.source_)
  , offset_(other.offset_)
  , size_(other.size_) {  
  if (!other.source_) {
    value_ = other.value_;
  }
}

system_buffer_impl::system_buffer_impl(system_buffer_impl&& other)
  : source_(std::move(other.source_))
  , value_(std::move(other.value_))
  , offset_(std::move(other.offset_))
  , size_(std::move(other.size_))
{}

system_buffer_impl& system_buffer_impl::operator=(const system_buffer_impl& other) {
  this->copy(0, other, 0, size_);
  return *this;
}

system_buffer_impl& system_buffer_impl::operator=(system_buffer_impl&& other) {
  // disable move for indirect nodes
  if (source_ || value_.size() != size_) {
    return this->operator=(other);
  }
  value_  = std::move(other.value_);
  source_ = std::move(other.source_);
  offset_ = std::move(other.offset_);
  size_   = std::move(other.size_);
  return *this;
}

const sdata_type& system_buffer_impl::data() const {
  if (source_) {
    if (value_.empty()) {
      value_.resize(size_);
    }
    source_->read(offset_, value_, 0, size_);
  }
  return value_;
}

void system_buffer_impl::copy(uint32_t dst_offset,
                         const system_buffer_impl& src,
                         uint32_t src_offset,
                         uint32_t length) {
  if (src.source()) {
    this->copy(dst_offset, *src.source(), src.offset() + src_offset, length);
  } else {
    this->write(dst_offset, src.data(), src_offset, length);
  }
}

void system_buffer_impl::read(uint32_t src_offset,
                         sdata_type& dst,
                         uint32_t dst_offset,
                         uint32_t length) const {
  if (source_) {
    source_->read(offset_ + src_offset, dst, dst_offset, length);
  } else {
    dst.copy(dst_offset, value_, src_offset, length);
  }
}

void system_buffer_impl::write(uint32_t dst_offset,
                          const sdata_type& src,
                          uint32_t src_offset,
                          uint32_t length) {
  if (source_) {
    source_->write(offset_ + dst_offset, src, src_offset, length);
  } else {
    value_.copy(dst_offset, src, src_offset, length);
  }
}

void system_buffer_impl::read(uint32_t src_offset,
                         void* out,
                         uint32_t byte_alignment,
                         uint32_t dst_offset,
                         uint32_t length) const {
  if (source_) {
    source_->read(offset_ + src_offset, out, byte_alignment, dst_offset, length);
  } else {
    value_.read(src_offset, out, byte_alignment, dst_offset, length);
  }
}

void system_buffer_impl::write(uint32_t dst_offset,
                          const void* in,
                          uint32_t byte_alignment,
                          uint32_t src_offset,
                          uint32_t length) {
  if (source_) {
    source_->write(offset_ + dst_offset, in, byte_alignment, src_offset, length);
  } else {
    value_.write(dst_offset, in, byte_alignment, src_offset, length);
  }
}

std::string system_buffer_impl::to_verilog() const {
  if (source_) {
    return source_->to_verilog() + stringf("[%d:%d]", (offset_ + size_ - 1), offset_);
  } else {
    return "$" + name_;
  }
}

///////////////////////////////////////////////////////////////////////////////

sdata_type ch::internal::sdata_from_fill(uint64_t value, uint32_t size, uint32_t count) {
  sdata_type src(size, value);
  sdata_type out(size * count);
  for (uint32_t i = 0; i < count; ++i) {
    out.copy(i * size, src, 0, size);
  }
  return out;
}
