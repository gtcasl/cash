#pragma once

#include "common.h"
#include "bitvector.h"

namespace cash {
namespace detail {

template <unsigned N>
class ch_literal {
public:
  ch_literal(const bitvector& value) : value_(value) {}
private:
  bitvector value_;
};

template <typename T>
class nodebuf {
public:

  struct entry_t {
    const T& src;
    uint32_t offset;
    uint32_t length;
  };

  nodebuf(uint32_t capacity)
    : capacity_(capacity)
    , size_(0)
  {}

  nodebuf(const T& src, uint32_t offset, uint32_t length)
    : capacity_(length)
    , size_(length) {
    buffer_.emplace_back(entry_t{src, offset, length});
  }

  uint32_t num_slices() const {
    return buffer_.size();
  }
  
  uint32_t size() const {
    return size_;
  }

  uint32_t capacity() const {
    return capacity_;
  }

  auto begin() const {
    return buffer_.begin();
  }

  auto end() const {
    return buffer_.end();
  }

  void push_back(const entry_t& data) {
    buffer_.emplace_back(data);
    size_ += data.length;
    assert(size_ <= capacity_);
  }

private:

  std::vector<entry_t> buffer_;
  uint32_t capacity_;
  uint32_t size_;
};

template <typename T>
class typebase_itf {
public:
  virtual void read_data(T& inout, size_t offset, size_t length) const = 0;
  virtual void write_data(size_t dst_offset, const T& in, size_t src_offset, size_t src_length) = 0;
};

template <typename T, unsigned N> class const_sliceref;
template <typename T, unsigned N> class sliceref;

template <typename B, typename A> class const_concatref;
template <typename B, typename A> class concatref;

template <unsigned N, typename T>
class typebase;

template <typename T>
void read_data(const T& b, typename T::data_type& inout, size_t offset, size_t length) {
  reinterpret_cast<const typebase<T::bit_count, typename T::data_type>&>(b).read_data(inout, offset, length);
}

template <typename T>
void write_data(T& b, size_t dst_offset, const typename T::data_type& in, size_t src_offset, size_t src_length) {
  reinterpret_cast<typebase<T::bit_count,typename T::data_type>&>(b).write_data(dst_offset, in, src_offset, src_length);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, typename T>
class  typeref: public typebase<N, T> {
public:   
  using base = typebase<N, T>;
  using base::operator=;
  using data_type = T;
  
  template <unsigned M>
  concatref<base, typebase<M, T>> concat(typebase<M, T>& rhs) const {
    return concatref<base, typebase<M, T>>(*this, rhs);
  }
  
  template <unsigned M>
  concatref<base, typebase<M, T>> concat(const typeref<M, T>& rhs) const {
    return concatref<base, typebase<M, T>>(*this, rhs);
  }
};

template <unsigned N, typename T>
class const_typeref: public typebase<N, T> {
public:   
  using base = typebase<N, T>;
  using data_type = T;
  
  const_sliceref<base, 1> operator[](size_t index) {
    return const_sliceref<base, 1>(*this, index);
  }

  const_sliceref<base, 1> operator[](size_t index) const {
    return const_sliceref<base, 1>(*this, index);
  }
  
  template <unsigned M>
  const_sliceref<base, M> slice(size_t index = 0) {
    return const_sliceref<base, M>(*this, index);
  }

  template <unsigned M>
  const_sliceref<base, M> slice(size_t index = 0) const {
    return const_sliceref<base, M>(*this, index);
  }
  
  template <unsigned M>
  const_sliceref<base, M> aslice(size_t index = 0) {
    return const_sliceref<base, M>(*this, index * M);
  }

  template <unsigned M>
  const_sliceref<base, M> aslice(size_t index = 0) const {
    return const_sliceref<base, M>(*this, index * M);
  }
  
  template <unsigned M>
  const_concatref<base, typebase<M, T>> concat(const typebase<M, T>& rhs) {
    return const_concatref<base, typebase<M, T>>(*this, rhs);
  }

  template <unsigned M>
  const_concatref<base, typebase<M, T>> concat(const typebase<M, T>& rhs) const {
    return const_concatref<base, typebase<M, T>>(*this, rhs);
  }
  
  template <unsigned M>
  const_concatref<base, typebase<M, T>> concat(typebase<M, T>& rhs) {
    return const_concatref<base, typebase<M, T>>(*this, rhs);
  }
  
  template <unsigned M>
  const_concatref<base, typebase<M, T>> concat(const typeref<M, T>& rhs) {
    return const_concatref<base, typebase<M, T>>(*this, rhs);
  }
  
private:

  void write_data(size_t dst_offset,
                  const data_type& in,
                  size_t src_offset, size_t src_length) override {
    CH_UNUSED(dst_offset, in, src_offset, src_length);
    assert(false); // invalid call
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_sliceref : public const_typeref<N, typename T::data_type> {
public:
  static_assert(N <= T::bit_count, "invalid slice size");
  using base = const_typeref<N, typename T::data_type>;
  using data_type = typename base::data_type;
  using container_type = T;
  
  const_sliceref(const T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bit_count, "invalid slice range");
  }

protected:

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid slice read range");
    detail::read_data(container_, inout, start_ + offset, length);
  }

  const T& container_;
  size_t start_;
  
  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class sliceref : public typeref<N, typename T::data_type> {
public:
  static_assert(N <= T::bit_count, "invalid slice size");
  using base = typeref<N, typename T::data_type>;
  using base::operator=;
  using data_type = typename base::data_type;
  using container_type = T;
  
  sliceref(T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bit_count, "invalid slice range");
  }
  
  sliceref& operator=(const sliceref& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }

protected:

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid slice read range");
    detail::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    CH_CHECK(dst_offset + src_length <= N, "invalid slice write range");
    detail::write_data(container_, start_ + dst_offset, in, src_offset, src_length);
  }

  T& container_;
  size_t start_;

  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class const_concatref : public const_typeref<B::bit_count + A::bit_count, typename A::data_type> {
public:
  static_assert(std::is_same<typename A::data_type, typename B::data_type>::value, "data type mismatch");
  using base = const_typeref<B::bit_count + A::bit_count, typename A::data_type>;
  using data_type = typename A::data_type;
  using first_container_type = A;
  using second_container_type = B;
  
  const_concatref(const B& b, const A& a)
    : b_(b)
    , a_(a)
  {}

protected:

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= const_concatref::bit_count, "invalid concat read range");
    if (offset + length <= A::bit_count) {
      detail::read_data(a_, inout, offset, length);
    } else if (offset >= A::bit_count) {
      detail::read_data(b_, inout, offset - A::bit_count, length);
    } else {
      size_t len = A::bit_count - offset;
      detail::read_data(a_, inout, offset, len);
      detail::read_data(b_, inout, 0, length - len);
    }
  }

  const B& b_;
  const A& a_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class concatref : public typeref<B::bit_count + A::bit_count, typename A::data_type> {
public:
  static_assert(std::is_same<typename A::data_type, typename B::data_type>::value, "data type mismatch");
  using base = typeref<B::bit_count + A::bit_count, typename A::data_type>;
  using base::operator=;
  using data_type = typename A::data_type;
  using first_container_type = A;
  using second_container_type = B;
  
  concatref(const B& b, const A& a)
    : b_(const_cast<B&>(b))
    , a_(const_cast<A&>(a))
  {}
  
  concatref& operator=(const concatref& rhs) {
    data_type data(base::bit_count);
    rhs.read_data(data, 0, base::bit_count);
    this->write_data(0, data, 0, base::bit_count);
    return *this;
  }

protected:

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= concatref::bit_count, "invalid concat read range");
    if (offset + length <= A::bit_count) {
      detail::read_data(a_, inout, offset, length);
    } else if (offset >= A::bit_count) {
      detail::read_data(b_, inout, offset - A::bit_count, length);
    } else {
      size_t len = A::bit_count - offset;
      detail::read_data(a_, inout, offset, len);
      detail::read_data(b_, inout, 0, length - len);
    }
  }
  
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    CH_CHECK(dst_offset + src_length <= concatref::bit_count, "invalid concat write range");
    if (dst_offset + src_length <= A::bit_count) {
      detail::write_data(a_, dst_offset, in, src_offset, src_length);
    } else if (dst_offset >= A::bit_count) {
      detail::write_data(b_, dst_offset - A::bit_count, in, src_offset, src_length);
    } else {
      size_t len = A::bit_count - dst_offset;
      detail::write_data(a_, dst_offset, in, src_offset, len);
      detail::write_data(b_, 0, in, src_offset + len, src_length - len);
    }
  }

  B& b_;
  A& a_;
};

}
}
