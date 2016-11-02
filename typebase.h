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

template <typename T> class const_subscript_ref;
template <typename T> class subscript_ref;

template <unsigned N, typename T>
class typebase {
public:   
  static const unsigned bit_count = N;
  using bitstream_type = T;
  
  const const_subscript_ref<typebase>& operator[](size_t index) const {
    return const_subscript_ref<typebase>(*this, index); 
  }
  
  subscript_ref<typebase>& operator[](size_t index) {
    return subscript_ref<typebase>(*this, index); 
  }
  
  template <unsigned M> const const_slice_ref<typebase, M>& slice(size_t index) const {
    return const_slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M> slice_ref<typebase, M>& slice(size_t index) {
    return slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M> const const_slice_ref<typebase, M>& aslice(size_t index) const {
    return const_slice_ref<typebase, M>(*this, index * M);
  }
  
  template <unsigned M> slice_ref<typebase, M>& aslice(size_t index) {
    return slice_ref<typebase, M>(*this, index * M);
  }
  
  typebase& operator=(const typebase& rhs) {
    bitstream_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
  
protected:

  virtual void read(bitstream_type& inout, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) = 0;
  
  template <typename T_> friend void read_data(const T_& t, typename T_::bitstream_type& inout, size_t offset, size_t length);    
  template <typename T_> friend void write_data(T_& t, size_t dst_offset, const typename T_::bitstream_type& in, size_t src_offset, size_t src_length);    
};

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
class const_refbase: public typebase<N, T> {
public:   
  using base = typebase<N, T>;
  using bitstream_type = T;
  
  template <unsigned M> slice_ref<base, M> slice(size_t index) = delete;
  template <unsigned M> slice_ref<base, M> aslice(size_t index) = delete;
  subscript_ref<base> operator[](size_t index) = delete;  
  
private:
  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    assert(false); // invalid call
  }
};

template <unsigned N, typename T>
class  refbase: public typebase<N, T> {
public:   
  using base = typebase<N, T>;
  using base::operator=;
  using bitstream_type = T;  
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class const_subscript_ref : public const_refbase<1, typename T::bitstream_type> {
public:
  using base = const_refbase<1, typename T::bitstream_type>;
  using bitstream_type = typename base::bitstream_type;
  using container_type = T;
    
  template <unsigned M> const_slice_ref<base, M> slice(size_t index) const = delete;   
  template <unsigned M> const_slice_ref<base, M> aslice(size_t index) const = delete;    
  const_subscript_ref<base> operator[](size_t index) const = delete;  

protected: 
  
  const_subscript_ref(const T& container, size_t index)
    : m_container(container)
    , m_index(index) {
    CHDL_CHECK(index < T::bit_count, "invalid subscript index");
  } 
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    assert(offset == 0 && length == 1);
    read_data(m_container, inout, m_index, 1);
  }  

  const T& m_container;
  size_t m_index;
  
  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class subscript_ref : public refbase<1, typename T::bitstream_type> {
public:
  using base = refbase<1, typename T::bitstream_type>;
  using base::operator=;
  using bitstream_type = typename base::bitstream_type;
  using container_type = T;
    
  template <unsigned M> slice_ref<base, M> slice(size_t index) = delete;   
  template <unsigned M> slice_ref<base, M> aslice(size_t index) = delete;   
  subscript_ref<base> operator[](size_t index) = delete;  
  
  subscript_ref& operator=(const subscript_ref& rhs) {
    bitstream_type data(1);
    rhs.read(data, 0, 1);
    this->write(0, data, 0, 1);
    return *this;
  }

protected: 
  
  subscript_ref(T& container, size_t index)
    : m_container(container)
    , m_index(index) {
    CHDL_CHECK(index < T::bit_count, "invalid subscript index");
  } 
  
  void read(bitstream_type& inout, size_t offset, size_t length) const override {
    assert(offset == 0 && length == 1);
    read_data(m_container, inout, m_index, 1);
  }  
  
  void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override {
    assert(dst_offset == 0 && src_length == 1);
    write_data(m_container, m_index, in, src_offset, 1);
  }

  T& m_container;
  size_t m_index;
  
  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_slice_ref : public const_refbase<N, typename T::bitstream_type> {
public:
  using base = const_refbase<N, typename T::bitstream_type>;
  using bitstream_type = typename base::bitstream_type;
  using container_type = T;

protected:

  const_slice_ref(const T& container, size_t start)
    : m_container(container)
    , m_start(start) {
    CHDL_CHECK(start + N <= T::bit_count, "invalid slice range");
  }
  
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
class slice_ref : public refbase<N, typename T::bitstream_type> {
public:
  using base = refbase<N, typename T::bitstream_type>;
  using base::operator=;
  using bitstream_type = typename base::bitstream_type;
  using container_type = T;
  
  slice_ref& operator=(const slice_ref& rhs) {
    bitstream_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }

protected:

  slice_ref(T& container, size_t start)
    : m_container(container)
    , m_start(start) {
    CHDL_CHECK(start + N <= T::bit_count, "invalid slice range");
  }
  
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
class const_concat_ref : public const_refbase<B::bit_count + A::bit_count, typename A::bitstream_type> {
public:
  static_assert(std::is_same<typename A::bitstream_type, typename B::bitstream_type>::value, "type mismatch!");
  using base = const_refbase<B::bit_count + A::bit_count, typename A::bitstream_type>;
  using bitstream_type = typename A::bitstream_type;
  using first_container_type = A;
  using second_container_type = B;

protected:
   
  const_concat_ref(const B& b, const A& a)
    : m_b(b)
    , m_a(a)
  {}

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
  
  template <typename B_, typename A_>
  friend const_concat_ref<B_, A_> make_const_concat_ref(const B_& b, const A_& a);
};

template <typename B, typename A>
const_concat_ref<B, A> make_const_concat_ref(const B& b, const A& a) {
  return const_concat_ref<B, A>(b, a);
}

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class concat_ref : public refbase<B::bit_count + A::bit_count, typename A::bitstream_type> {
public:
  static_assert(std::is_same<typename A::bitstream_type, typename B::bitstream_type>::value, "type mismatch!");
  using base = refbase<B::bit_count + A::bit_count, typename A::bitstream_type>;
  using base::operator=;
  using bitstream_type = typename A::bitstream_type;
  using first_container_type = A;
  using second_container_type = B;
  
  concat_ref& operator=(const concat_ref& rhs) {
    bitstream_type data(base::bit_count);
    rhs.read(data, 0, base::bit_count);
    this->write(0, data, 0, base::bit_count);
    return *this;
  }

protected:
  
  concat_ref(const B& b, const A& a)
    : m_b(const_cast<B&>(b))
    , m_a(const_cast<A&>(a))
  {}
  
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
  
  template <typename B_, typename A_>
  friend concat_ref<B_, A_> make_concat_ref(const B_& b, const A_& a);
};

template <typename B, typename A>
concat_ref<B, A> make_concat_ref(const B& b, const A& a) {
  return concat_ref<B, A>(b, a);
}

}
