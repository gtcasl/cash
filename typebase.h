#pragma once

#include "common.h"

namespace cash {
namespace detail {

template <typename T>
class nodeset {
public:
  nodeset(uint32_t max_size) : max_size_(max_size), size_(0) {}
  
  struct data_t {
    const T& src;
    uint32_t offset;
    uint32_t length;    
  };
  
  uint32_t get_size() const {
    return size_;
  }

  uint32_t get_max_size() const {
    return max_size_;
  }
  
  auto begin() const {
    return buffer_.begin(); 
  }
  
  auto end() const {
    return buffer_.end(); 
  }

  void push(const data_t& data) {
    buffer_.emplace_back(data);
    size_ += data.length;
    assert(size_ <= max_size_);
  }

private:
  std::vector<data_t> buffer_;
  uint32_t max_size_;
  uint32_t size_;
};

template <typename T, unsigned N> class const_slice_ref;
template <typename T, unsigned N> class slice_ref;

template <typename B, typename A> class const_concat_ref;
template <typename B, typename A> class concat_ref;

template <unsigned N, typename T>
class typebase {};

template <typename T>
void read_data(const T& b, typename T::data_type& inout, size_t offset, size_t length) {
  reinterpret_cast<const typebase<T::bit_count, typename T::data_type>&>(b).read(inout, offset, length);
}

template <typename T>
void write_data(T& b, size_t dst_offset, const typename T::data_type& in, size_t src_offset, size_t src_length) {
  reinterpret_cast<typebase<T::bit_count,typename T::data_type>&>(b).write(dst_offset, in, src_offset, src_length);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, typename T>
class  typeref: public typebase<N, T> {
public:   
  using base = typebase<N, T>;
  using base::operator=;
  using data_type = T;
  
  template <unsigned M> 
  concat_ref<base, typebase<M, T>> concat(typebase<M, T>& rhs) const {
    return concat_ref<base, typebase<M, T>>(*this, rhs);
  }
  
  template <unsigned M> 
  concat_ref<base, typebase<M, T>> concat(const typeref<M, T>& rhs) const {
    return concat_ref<base, typebase<M, T>>(*this, rhs);
  }
};

template <unsigned N, typename T>
class const_typeref: public typebase<N, T> {
public:   
  using base = typebase<N, T>;
  using data_type = T;
  
  const_slice_ref<base, 1> operator[](size_t index) {
    return const_slice_ref<base, 1>(index);  
  }
  
  template <unsigned M> 
  const_slice_ref<base, M> slice(size_t index = 0) {
    return const_slice_ref<base, M>(*this, index);
  }
  
  template <unsigned M> 
  const_slice_ref<base, M> aslice(size_t index = 0) {
    return const_slice_ref<base, M>(*this, index * M);
  }
  
  template <unsigned M>
  const_concat_ref<base, typebase<M, T>> concat(const typebase<M, T>& rhs) const {
    return const_concat_ref<base, typebase<M, T>>(*this, rhs);
  }
  
  template <unsigned M>
  const_concat_ref<base, typebase<M, T>> concat(const typebase<M, T>& rhs) {
    return const_concat_ref<base, typebase<M, T>>(*this, rhs);
  }
  
  template <unsigned M> 
  const_concat_ref<base, typebase<M, T>> concat(typebase<M, T>& rhs) {
    return const_concat_ref<base, typebase<M, T>>(*this, rhs);
  }
  
  template <unsigned M> 
  const_concat_ref<base, typebase<M, T>> concat(const typeref<M, T>& rhs) {
    return const_concat_ref<base, typebase<M, T>>(*this, rhs);
  }
  
private:
  void write(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    CH_UNUSED(dst_offset, in, src_offset, src_length);
    assert(false); // invalid call
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_slice_ref : public const_typeref<N, typename T::data_type> {
public:
  static_assert(N <= T::bit_count, "invalid slice size");
  using base = const_typeref<N, typename T::data_type>;
  using data_type = typename base::data_type;
  using container_type = T;
  
  const_slice_ref(const T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bit_count, "invalid slice range");
  }

protected:

  void read(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid slice read range");
    read_data(container_, inout, start_ + offset, length);
  }

  const T& container_;
  size_t start_;
  
  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class slice_ref : public typeref<N, typename T::data_type> {
public:
  static_assert(N <= T::bit_count, "invalid slice size");
  using base = typeref<N, typename T::data_type>;
  using base::operator=;
  using data_type = typename base::data_type;
  using container_type = T;
  
  slice_ref(T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bit_count, "invalid slice range");
  }
  
  slice_ref& operator=(const slice_ref& rhs) {
    data_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }

protected:

  void read(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid slice read range");
    read_data(container_, inout, start_ + offset, length);
  }

  void write(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    CH_CHECK(dst_offset + src_length <= N, "invalid slice write range");
    write_data(container_, start_ + dst_offset, in, src_offset, src_length);
  }

  T& container_;
  size_t start_;

  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class const_concat_ref : public const_typeref<B::bit_count + A::bit_count, typename A::data_type> {
public:
  static_assert(std::is_same<typename A::data_type, typename B::data_type>::value, "data type mismatch");
  using base = const_typeref<B::bit_count + A::bit_count, typename A::data_type>;
  using data_type = typename A::data_type;
  using first_container_type = A;
  using second_container_type = B;
  
  const_concat_ref(const B& b, const A& a)
    : b_(b)
    , a_(a)
  {}

protected:

  void read(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= const_concat_ref::bit_count, "invalid concat read range");
    if (offset + length <= A::bit_count)
      read_data(a_, inout, offset, length);
    else if (offset >= A::bit_count)
      read_data(b_, inout, offset - A::bit_count, length);
    else {
      size_t len = A::bit_count - offset;
      read_data(a_, inout, offset, len);
      read_data(b_, inout, 0, length - len);
    }
  }

  const B& b_;
  const A& a_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class concat_ref : public typeref<B::bit_count + A::bit_count, typename A::data_type> {
public:
  static_assert(std::is_same<typename A::data_type, typename B::data_type>::value, "data type mismatch");
  using base = typeref<B::bit_count + A::bit_count, typename A::data_type>;
  using base::operator=;
  using data_type = typename A::data_type;
  using first_container_type = A;
  using second_container_type = B;
  
  concat_ref(const B& b, const A& a)
    : b_(const_cast<B&>(b))
    , a_(const_cast<A&>(a))
  {}
  
  concat_ref& operator=(const concat_ref& rhs) {
    data_type data(base::bit_count);
    rhs.read(data, 0, base::bit_count);
    this->write(0, data, 0, base::bit_count);
    return *this;
  }

protected:

  void read(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= concat_ref::bit_count, "invalid concat read range");
    if (offset + length <= A::bit_count)
      read_data(a_, inout, offset, length);
    else if (offset >= A::bit_count)
      read_data(b_, inout, offset - A::bit_count, length);
    else {
      size_t len = A::bit_count - offset;
      read_data(a_, inout, offset, len);
      read_data(b_, inout, 0, length - len);
    }
  }
  
  void write(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override {
    CH_CHECK(dst_offset + src_length <= concat_ref::bit_count, "invalid concat write range");
    if (dst_offset + src_length <= A::bit_count)
      write_data(a_, dst_offset, in, src_offset, src_length);
    else if (dst_offset >= A::bit_count)
      write_data(b_, dst_offset - A::bit_count, in, src_offset, src_length);
    else {
      size_t len = A::bit_count - dst_offset;
      write_data(a_, dst_offset, in, src_offset, len);
      write_data(b_, 0, in, src_offset + len, src_length - len);
    }
  }

  B& b_;
  A& a_;
};

}
}
