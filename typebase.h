#pragma once

#include "common.h"

namespace chdl_internal {

template <typename T>
class bitstream {
public:
  bitstream(uint32_t capacity) : m_capacity(capacity), m_size(0) {}
  
  struct partition {
    T*       data;
    uint32_t offset;
    uint32_t length;    
  };
  
  void push(const partition& p) {
    m_buffer.emplace_back(p);
    m_size += p.length;
    assert(m_size <= m_capacity);
  }
  
  uint32_t get_size() const {
    return m_size;
  }
  
  typename std::vector<partition>::const_iterator begin() const { 
    return m_buffer.begin(); 
  }
  
  typename std::vector<partition>::const_iterator end() const { 
    return m_buffer.end(); 
  }

private:
  std::vector<partition> m_buffer; 
  uint32_t m_capacity;
  uint32_t m_size;
};

template <typename T, unsigned N> class const_slice_ref;
template <typename T, unsigned N> class slice_ref;

template <typename B, typename A> class const_concat_ref;
template <typename B, typename A> class concat_ref;

template <unsigned N, typename T>
class typebase {};

template <typename T>
void read_data(const T& t, typename T::bitstream_type& inout, size_t offset, size_t length) {
  reinterpret_cast<const typebase<T::bit_count, typename T::bitstream_type>&>(t).read(inout, offset, length);
}

template <typename T>
void write_data(T& t, size_t dst_offset, const typename T::bitstream_type& in, size_t src_offset, size_t src_length) {
  reinterpret_cast<typebase<T::bit_count,typename T::bitstream_type>&>(t).write(dst_offset, in, src_offset, src_length);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, typename T>
class  typeref: public typebase<N, T> {
public:   
  using base = typebase<N, T>;
  using base::operator=;
  using bitstream_type = T;  
  
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
  using bitstream_type = T;
  
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
  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    assert(false); // invalid call
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_slice_ref : public const_typeref<N, typename T::bitstream_type> {
public:
  static_assert(N <= T::bit_count, "invalid slice size");
  using base = const_typeref<N, typename T::bitstream_type>;
  using bitstream_type = typename base::bitstream_type;
  using container_type = T;
  
  const_slice_ref(const T& container, size_t start = 0)
    : m_container(container)
    , m_start(start) {
    CHDL_CHECK(start + N <= T::bit_count, "invalid slice range");
  }

protected:
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    CHDL_CHECK(offset + length <= N, "invalid slice read range");
    read_data(m_container, inout, m_start + offset, length);
  }

  const T& m_container;
  size_t m_start;
  
  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class slice_ref : public typeref<N, typename T::bitstream_type> {
public:
  static_assert(N <= T::bit_count, "invalid slice size");
  using base = typeref<N, typename T::bitstream_type>;
  using base::operator=;
  using bitstream_type = typename base::bitstream_type;
  using container_type = T;
  
  slice_ref(T& container, size_t start = 0)
    : m_container(container)
    , m_start(start) {
    CHDL_CHECK(start + N <= T::bit_count, "invalid slice range");
  }
  
  slice_ref& operator=(const slice_ref& rhs) {
    bitstream_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }

protected:
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    CHDL_CHECK(offset + length <= N, "invalid slice read range");
    read_data(m_container, inout, m_start + offset, length);
  }

  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    CHDL_CHECK(dst_offset + src_length <= N, "invalid slice write range");
    write_data(m_container, m_start + dst_offset, in, src_offset, src_length);
  }

  T& m_container;
  size_t m_start;

  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class const_concat_ref : public const_typeref<B::bit_count + A::bit_count, typename A::bitstream_type> {
public:
  static_assert(std::is_same<typename A::bitstream_type, typename B::bitstream_type>::value, "bitstream type mismatch");
  using base = const_typeref<B::bit_count + A::bit_count, typename A::bitstream_type>;
  using bitstream_type = typename A::bitstream_type;
  using first_container_type = A;
  using second_container_type = B;
  
  const_concat_ref(const B& b, const A& a)
    : m_b(b)
    , m_a(a)
  {}

protected:

  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    CHDL_CHECK(offset + length <= const_concat_ref::bit_count, "invalid concat read range");
    if (offset + length <= A::bit_count)
      read_data(m_a, inout, offset, length);
    else if (offset >= A::bit_count)
      read_data(m_b, inout, offset - A::bit_count, length);
    else {
      size_t len = A::bit_count - offset;
      read_data(m_a, inout, offset, len);
      read_data(m_b, inout, 0, length - len);
    }
  }

  const A& m_a;
  const B& m_b;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class concat_ref : public typeref<B::bit_count + A::bit_count, typename A::bitstream_type> {
public:
  static_assert(std::is_same<typename A::bitstream_type, typename B::bitstream_type>::value, "bitstream type mismatch");
  using base = typeref<B::bit_count + A::bit_count, typename A::bitstream_type>;
  using base::operator=;
  using bitstream_type = typename A::bitstream_type;
  using first_container_type = A;
  using second_container_type = B;
  
  concat_ref(const B& b, const A& a)
    : m_b(const_cast<B&>(b))
    , m_a(const_cast<A&>(a))
  {}
  
  concat_ref& operator=(const concat_ref& rhs) {
    bitstream_type data(base::bit_count);
    rhs.read(data, 0, base::bit_count);
    this->write(0, data, 0, base::bit_count);
    return *this;
  }

protected:
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    CHDL_CHECK(offset + length <= concat_ref::bit_count, "invalid concat read range");
    if (offset + length <= A::bit_count)
      read_data(m_a, inout, offset, length);
    else if (offset >= A::bit_count)
      read_data(m_b, inout, offset - A::bit_count, length);
    else {
      size_t len = A::bit_count - offset;
      read_data(m_a, inout, offset, len);
      read_data(m_b, inout, 0, length - len);
    }
  }
  
  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    CHDL_CHECK(dst_offset + src_length <= concat_ref::bit_count, "invalid concat write range");
    if (dst_offset + src_length <= A::bit_count)
      write_data(m_a, dst_offset, in, src_offset, src_length);
    else if (dst_offset >= A::bit_count)
      write_data(m_b, dst_offset - A::bit_count, in, src_offset, src_length);
    else {
      size_t len = A::bit_count - dst_offset;
      write_data(m_a, dst_offset, in, src_offset, len);
      write_data(m_b, 0, in, src_offset + len, src_length - len);
    }
  }

  A& m_a;
  B& m_b;
};

}
