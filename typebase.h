#pragma once

namespace chdl_internal {

template <unsigned N, typename T> class const_slice_ref;
template <unsigned N, typename T> class slice_ref;

template <typename T> class const_subscript_ref;
template <typename T> class subscript_ref;

template <typename T>
struct partition {
  const T& data;
  size_t offset;
  size_t length;
};

template <unsigned N, typename T>
class typebase {
public:   
  static const unsigned bit_count = N;
  typedef T data_type;
  
  typebase() {}
  virtual ~typebase() {}
  
  template <unsigned M>
  const_slice_ref<M, typebase> slice(size_t index) const {
    return const_slice_ref<M, typebase>(*this, index);
  }
  
  template <unsigned M>
  slice_ref<M, typebase> slice(size_t index) {
    return slice_ref<M, typebase>(*this, index);
  }
  
  template <unsigned M>
  const_slice_ref<M, typebase> aslice(size_t index) const {
    return const_slice_ref<M, typebase>(*this, index * M);
  }
  
  template <unsigned M>
  slice_ref<M, typebase> aslice(size_t index) {
    return slice_ref<M, typebase>(*this, index * M);
  }
  
  const_subscript_ref<typebase> operator[](size_t index) const {
    return const_subscript_ref<typebase>(*this, index); 
  }
  
  subscript_ref<typebase> operator[](size_t index) {
    return subscript_ref<typebase>(*this, index); 
  }
  
  typebase& operator=(const typebase& rhs) {
    std::vector< partition<data_type> > data;
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
  
protected:

  template <typename T_> 
  friend void read_data(const T_& t, std::vector< partition<typename T_::data_type> >& out, size_t offset, size_t length);
  
  template <typename T_>
  friend void write_data(T_& t, size_t dst_offset, const std::vector< partition<typename T_::data_type> >& src, size_t src_offset, size_t src_length);
  
  virtual void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) = 0;
};

template <typename T>
void read_data(const T& t, std::vector< partition<typename T::data_type> >& out, size_t offset, size_t length) {
  reinterpret_cast<const typebase<T::bit_count, typename T::data_type>&>(t).read(out, offset, length);
}

template <typename T>
void write_data(T& t, size_t dst_offset, const std::vector< partition<typename T::data_type> >& src, size_t src_offset, size_t src_length) {
  reinterpret_cast<typebase<T::bit_count, typename T::data_type>&>(t).write(dst_offset, src, src_offset, src_length);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class const_subscript_ref : public typebase<1, typename T::data_type> {
public:
  using base = typebase<1, typename T::data_type>;
  typedef typename base::data_type data_type;
  typedef T container_type;
  
  template <unsigned M>
  const_slice_ref<M, base> slice(size_t index) = delete;
  
  template <unsigned M>
  slice_ref<M, base> slice(size_t index) = delete;
  
  template <unsigned M>
  const_slice_ref<M, base> aslice(size_t index) const = delete;
  
  template <unsigned M>
  slice_ref<M, base> aslice(size_t index) = delete;
  
  const_subscript_ref<base> operator[](size_t index) const = delete;
  
  subscript_ref<base> operator[](size_t index) = delete;

protected:
  
  const_subscript_ref(const T& container, size_t index)
    : m_container(const_cast<T&>(container))
    , m_index(index) {
    if (index >= T::bit_count)
      CHDL_ABORT("invalid subscript index");
  } 

  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    assert(offset == 0 && length == 1);
    read_data(m_container, out, m_index, 1);
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {}

  friend T;
  
  template <typename T_> friend class subscript_ref;

  T& m_container;
  size_t m_index;   
};

template <typename T>
class subscript_ref : public const_subscript_ref<T> {
public:
  using base = const_subscript_ref<T>;
  using base::base::operator=;
  typedef typename base::data_type data_type;
  typedef typename base::container_type container_type;
  
protected:

  subscript_ref(const T& container, size_t index)
    : base(container, index) {}
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    assert(dst_offset == 0 && src_length == 1);
    write_data(m_container, m_index, src, src_offset, 1);
  }

  using base::m_container;
  using base::m_index;
  
  friend T;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, typename T>
class const_slice_ref : public typebase<N, typename T::data_type> {
public:
  using base = typebase<N, typename T::data_type>;
  typedef typename base::data_type data_type;
  typedef T container_type;
  
  subscript_ref<base> operator[](size_t index) = delete;

protected:

  const_slice_ref(const T& container, size_t start)
    : m_container(const_cast<T&>(container))
    , m_start(start) {
    if (start + N > T::bit_count)
      CHDL_ABORT("invalid slice range");
  }
  
  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    if (offset + length > N)
      CHDL_ABORT("invalid slice read range");
    read_data(m_container, out, m_start + offset, length);
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {}

  friend T;
  template <unsigned N_, typename T_> friend class slice_ref;

  T& m_container;
  size_t m_start;
};

template <unsigned N, typename T>
class slice_ref : public const_slice_ref<N, T> {
public:
  using base = const_slice_ref<N, T>;
  using base::base::operator=;
  using base::base::operator[];
  typedef typename base::data_type data_type;
  typedef typename base::container_type container_type;

protected:

  slice_ref(const T& container, size_t start)
    : base(container, start) {}

  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    if (dst_offset + src_length > N)
      CHDL_ABORT("invalid slice write range");
    write_data(m_container, m_start + dst_offset, src, src_offset, src_length);
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
  using base = typebase< B::bit_count + A::bit_count, typename A::data_type >;
  typedef typename base::data_type data_type;
  typedef typebase<A::bit_count, typename A::data_type> A_typebase;
  typedef typebase<B::bit_count, typename B::data_type> B_typebase;  
  typedef A A_type;
  typedef B B_type;

  const_concat_ref(const B& b, const A& a)
    : m_b(const_cast<B&>(b))
    , m_a(const_cast<A&>(a))
  {}
  
  subscript_ref<base> operator[](size_t index) = delete;

protected:

  void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const override {
    if (offset + length > const_concat_ref::bit_count)
      CHDL_ABORT("invalid concat read range");
    if (offset + length <= A::bit_count)
      read_data(m_a, out, offset, length);
    else if (offset >= A::bit_count)
      read_data(m_b, out, offset - A::bit_count, length);
    else {
      read_data(m_a, out, offset, A::bit_count - offset);
      read_data(m_b, out, 0, length - (A::bit_count - offset));
    }
  }
  
  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {}

  A& m_a;
  B& m_b;
};

template <typename B, typename A>
class concat_ref : public const_concat_ref<B, A> {
public:
  static_assert(std::is_same<typename A::data_type, typename B::data_type>::value, "type mismatch!");
  using base = const_concat_ref<B, A>;
  using base::base::operator=;
  using base::base::operator[];
  typedef typename base::data_type data_type;
  typedef typename base::A_type A_type;
  typedef typename base::B_type B_type;

  concat_ref(const B& b, const A& a) : base(b, a) {}

protected:

  void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) override {
    if (dst_offset + src_length > concat_ref::bit_count)
      CHDL_ABORT("invalid concat write range");
    if (dst_offset + src_length <= A::bit_count)
      write_data(m_a, dst_offset, src, src_offset, src_length);
    else if (dst_offset >= A::bit_count)
      write_data(m_b, dst_offset - A::bit_count, src, src_offset, src_length);
    else {
      size_t length = A::bit_count - dst_offset;
      write_data(m_a, dst_offset, src, src_offset, length);
      write_data(m_b, 0, src, src_offset + length, src_length - length);
    }
  }

  using base::m_a;
  using base::m_b;
};

}
