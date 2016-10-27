#pragma once

#include "common.h"

namespace chdl_internal {

template <typename T, unsigned N> class const_slice_ref;
template <typename T, unsigned N> class slice_ref;

template <typename T> class const_subscript_ref;
template <typename T> class subscript_ref;

template <typename T>
struct partition {
  const T& data;
  uint32_t offset;
  uint32_t length;
};


template <unsigned N> 
static uint32_t to_value(char value) {
  if (value == '0')
    return 0x0;
  if (value == '1')
    return 0x1;
  CHDL_ABORT("invalid character value");
}

template <unsigned N, typename T>
class typebase {
public:   
  static const unsigned bit_count = N;
  typedef T data_type;
  
  typebase() {}
  virtual ~typebase() {}
  
  template <unsigned M> const slice_ref<typebase, M>& slice(size_t index) const {
    return const_slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M> slice_ref<typebase, M>& slice(size_t index) {
    return slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M> const slice_ref<typebase, M>& aslice(size_t index) const {
    return const_slice_ref<typebase, M>(*this, index * M);
  }
  
  template <unsigned M> slice_ref<typebase, M>& aslice(size_t index) {
    return slice_ref<typebase, M>(*this, index * M);
  }
  
  const subscript_ref<typebase>& operator[](size_t index) const {
    return const_subscript_ref<typebase>(*this, index); 
  }
  
  subscript_ref<typebase>& operator[](size_t index) {
    return subscript_ref<typebase>(*this, index); 
  }
  
  typebase& operator=(const typebase& rhs) {
    std::vector< partition<data_type> > data;
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
  
protected:

  virtual void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) = 0;
  
  template <typename T_> friend void read_data(const T_& t, std::vector< partition<typename T_::data_type> >& out, size_t offset, size_t length);    
  template <typename T_> friend void write_data(T_& t, size_t dst_offset, const std::vector< partition<typename T_::data_type> >& data, size_t src_offset, size_t src_length);    
};

template <typename T>
void read_data(const T& t, std::vector< partition<typename T::data_type> >& out, size_t offset, size_t length) {
  reinterpret_cast<const typebase<T::bit_count, typename T::data_type>&>(t).read(out, offset, length);
}

template <typename T>
void write_data(T& t, size_t dst_offset, const std::vector< partition<typename T::data_type> >& data, size_t src_offset, size_t src_length) {
  reinterpret_cast<typebase<T::bit_count,typename T::data_type>&>(t).write(dst_offset, data, src_offset, src_length);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class const_subscript_ref : public typebase<1, typename T::data_type> {
public:
  using base = typebase<1, typename T::data_type>;
  typedef typename base::data_type data_type;
  typedef T container_type;
  
  const_subscript_ref& operator=(const const_subscript_ref& rhs) = delete;
  
  template <unsigned M> const_slice_ref<base, M> slice(size_t index) = delete;
  
  template <unsigned M> slice_ref<base, M> slice(size_t index) = delete;
  
  template <unsigned M> const_slice_ref<base, M> aslice(size_t index) const = delete;
  
  template <unsigned M> slice_ref<base, M> aslice(size_t index) = delete;
  
  const_subscript_ref<base> operator[](size_t index) const = delete;
  
  subscript_ref<base> operator[](size_t index) = delete;  

protected: 
  
  const_subscript_ref(const T& container, size_t index)
    : m_container(const_cast<T&>(container))
    , m_index(index) {
    CHDL_CHECK(index < T::bit_count, "invalid subscript index");
  } 
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    assert(offset == 0 && length == 1);
    read_data(m_container, out, m_index, 1);
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) override {
    CHDL_ABORT("invalid call!");
  }

  T& m_container;
  size_t m_index;   
  
  friend T;  
  template <typename T_> friend class subscript_ref;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class subscript_ref : public const_subscript_ref<T> {
public:
  using base = const_subscript_ref<T>;
  using base::base::operator=;
  typedef typename base::data_type data_type;
  typedef typename base::container_type container_type;
  
  subscript_ref& operator=(const subscript_ref& rhs) {
    base::base::operator=(rhs);
    return *this;
  }
  
protected:

  subscript_ref(const T& container, size_t index)
    : base(container, index) {}
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) override {
    assert(dst_offset == 0 && src_length == 1);
    write_data(m_container, m_index, data, src_offset, 1);
  }

  using base::m_container;
  using base::m_index;
  
  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_slice_ref : public typebase<N, typename T::data_type> {
public:
  using base = typebase<N, typename T::data_type>;
  typedef typename base::data_type data_type;
  typedef T container_type;
  
  const_slice_ref& operator=(const const_slice_ref& rhs) = delete;
  
  subscript_ref<base> operator[](size_t index) = delete;

protected:

  const_slice_ref(const T& container, size_t start)
    : m_container(const_cast<T&>(container))
    , m_start(start) {
    CHDL_CHECK(start + N <= T::bit_count, "invalid slice range");
  }
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    CHDL_CHECK(offset + length <= N, "invalid slice read range");
    read_data(m_container, out, m_start + offset, length);
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) override {
    CHDL_ABORT("invalid call!");
  }

  T& m_container;
  size_t m_start;
  
  friend T;
  template <typename T_, unsigned N_> friend class slice_ref;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class slice_ref : public const_slice_ref<T, N> {
public:
  using base = const_slice_ref<T, N>;
  using base::base::operator=;
  using base::base::operator[];
  typedef typename base::data_type data_type;
  typedef typename base::container_type container_type;
  
  slice_ref& operator=(const slice_ref& rhs) {
    base::base::operator=(rhs);
    return *this;
  }

protected:

  slice_ref(const T& container, size_t start)
    : base(container, start) {}

  void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) override {
    CHDL_CHECK(dst_offset + src_length <= N, "invalid slice write range");
    write_data(m_container, m_start + dst_offset, data, src_offset, src_length);
  }

  using base::m_container;
  using base::m_start;

  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class const_concat_ref : public typebase<B::bit_count + A::bit_count, typename A::data_type> {
public:
  static_assert(std::is_same<typename A::data_type, typename B::data_type>::value, "type mismatch!");
  using base = typebase<B::bit_count + A::bit_count, typename A::data_type>;
  typedef typename A::data_type data_type;
  typedef A first_container_type;
  typedef B second_container_type;
  
  const_concat_ref(const B& b, const A& a)
    : m_b(const_cast<B&>(b))
    , m_a(const_cast<A&>(a))
  {}
  
  const_concat_ref& operator=(const const_concat_ref& rhs) = delete;

  subscript_ref<base> operator[](size_t index) = delete;

protected:

  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    CHDL_CHECK(offset + length <= const_concat_ref::bit_count, "invalid concat read range");
    if (offset + length <= A::bit_count)
      read_data(m_a, out, offset, length);
    else if (offset >= A::bit_count)
      read_data(m_b, out, offset - A::bit_count, length);
    else {
      size_t len = A::bit_count - offset;
      read_data(m_a, out, offset, len);
      read_data(m_b, out, 0, length - len);
    }
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) override {
    CHDL_ABORT("invalid call!");
  }

  A& m_a;
  B& m_b;
};

///////////////////////////////////////////////////////////////////////////////

template <typename B, typename A>
class concat_ref : public const_concat_ref<B, A> {
public:
  using base = const_concat_ref<B, A>;
  using base::base::operator=;
  using base::base::operator[];
  typedef typename base::data_type data_type;
  typedef typename base::first_container_type first_container_type;
  typedef typename base::second_container_type second_container_type;
  
  concat_ref(const B& b, const A& a) : base(b, a) {}
  
  concat_ref& operator=(const concat_ref& rhs) {
    base::base::operator=(rhs);
    return *this;
  }

protected:
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& data, size_t src_offset, size_t src_length) override {
    CHDL_CHECK(dst_offset + src_length <= concat_ref::bit_count, "invalid concat write range");
    if (dst_offset + src_length <= A::bit_count)
      write_data(m_a, dst_offset, data, src_offset, src_length);
    else if (dst_offset >= A::bit_count)
      write_data(m_b, dst_offset - A::bit_count, data, src_offset, src_length);
    else {
      size_t len = A::bit_count - dst_offset;
      write_data(m_a, dst_offset, data, src_offset, len);
      write_data(m_b, 0, data, src_offset + len, src_length - len);
    }
  }

  using base::m_a;
  using base::m_b;
};

}
