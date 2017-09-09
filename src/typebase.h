#pragma once

#include "common.h"
#include "bitvector.h"

namespace cash {
namespace internal {

template <typename T>
class has_bitcount {
private:
    template<typename U, typename = typename std::enable_if<!std::is_member_pointer<decltype(&U::bitcount)>::value>::type>
    static std::true_type check(int);

    template <typename>
    static std::false_type check(...);
public:
    static const bool value = decltype(check<T>(0))::value;
};

struct zero_bitcount {
  static const unsigned bitcount = 0;
};

template <typename T0, typename T1>
struct deduce_bitcount_helper2 {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;
  using U0 = typename std::conditional<has_bitcount<D0>::value, D0, zero_bitcount>::type;
  using U1 = typename std::conditional<has_bitcount<D1>::value, D1, zero_bitcount>::type;
  using type = typename std::conditional<
    (U0::bitcount != 0) && (U1::bitcount != 0),
    typename std::conditional<(U0::bitcount != U1::bitcount), zero_bitcount, U0>::type,
    typename std::conditional<(U0::bitcount != 0), U0, U1>::type>::type;
};

template <typename T0, typename... Ts>
struct deduce_bitcount_helper;

template <typename T0, typename T1>
struct deduce_bitcount_helper<T0, T1> {
  using type = typename deduce_bitcount_helper2<T0, T1>::type;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_bitcount_helper<T0, T1, Ts...> {
  using type = typename deduce_bitcount_helper<typename deduce_bitcount_helper2<T0, T1>::type, Ts...>::type;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_bitcount {
  using type = typename deduce_bitcount_helper<T0, T1, Ts...>::type;
  static const unsigned value = type::bitcount;
};

template <typename T0, typename T1>
struct first_bitcount {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;
  using U0 = typename std::conditional<has_bitcount<D0>::value, D0, zero_bitcount>::type;
  using U1 = typename std::conditional<has_bitcount<D1>::value, D1, zero_bitcount>::type;
  using type = typename std::conditional<(U0::bitcount != 0), U0, U1>::type;
  static const unsigned value = type::bitcount;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class nodebuf {
public:
  nodebuf(uint32_t capacity)
    : capacity_(capacity)
    , size_(0)
  {}

  nodebuf(uint32_t capacity, T src, uint32_t offset, uint32_t length)
    : nodebuf(capacity) {
    this->push(src, offset, length);
  }

  uint32_t get_capacity() const {
    return capacity_;
  }

  uint32_t get_size() const {
    return size_;
  }

  uint32_t get_num_slices() const {
    return slices_.size();
  }

  bool is_srccopy() const {
    return (1 == slices_.size()) && (slices_[0].src.get_size() == size_);
  }

  void push(T src, uint32_t offset, uint32_t length) {
    slices_.emplace_back(slice_t{src, offset, length});
    size_ += length;
    assert(size_ <= capacity_);
  }

  auto begin() const {
    assert(size_ == capacity_);
    return slices_.begin();
  }

  auto end() const {
    return slices_.end();
  }

private:

  struct slice_t {
    T src;
    uint32_t offset;
    uint32_t length;
  };

  std::vector<slice_t> slices_;
  uint32_t capacity_;    
  uint32_t size_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class typebase_itf {
public:
  virtual void read_data(T& inout, size_t offset, size_t length) const = 0;
  virtual void write_data(size_t dst_offset, const T& in, size_t src_offset, size_t length) = 0;
};

template <unsigned N, typename T> class typebase;

template <typename T>
void read_data(const T& node, typename T::data_type& inout, size_t offset, size_t length) {
  reinterpret_cast<const typebase<T::bitcount, typename T::data_type>&>(node).read_data(inout, offset, length);
}

template <typename T>
void write_data(T& node, size_t dst_offset, const typename T::data_type& in, size_t src_offset, size_t length) {
  reinterpret_cast<typebase<T::bitcount,typename T::data_type>&>(node).write_data(dst_offset, in, src_offset, length);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class sliceref : public typebase<N, typename T::data_type> {
public:
  static_assert(N <= T::bitcount, "invalid slice size");
  using base = typebase<N, typename T::data_type>;
  using base::operator=;
  using data_type = typename base::data_type;
  using container_type = T;

  sliceref(T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bitcount, "invalid slice range");
  }

  auto operator[](size_t index) const {
    return sliceref<base, 1>(const_cast<sliceref&>(*this), index);
  }

  template <unsigned M>
  auto slice(size_t index = 0) const {
    return sliceref<base, M>(const_cast<sliceref&>(*this), index);
  }

  template <unsigned M>
  auto aslice(size_t index = 0) const {
    return sliceref<base, M>(const_cast<sliceref&>(*this), index * M);
  }

  sliceref& operator=(const sliceref& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }

protected:

  sliceref(sliceref&&) = default;
  sliceref& operator=(sliceref&&) = default;

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid read range");
    cash::internal::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override {
    CH_CHECK(dst_offset + length <= N, "invalid write range");
    cash::internal::write_data(container_, start_ + dst_offset, in, src_offset, length);
  }

  T& container_;
  size_t start_;

  template <unsigned M, typename Q> friend class typebase;
  template <typename Q, unsigned M> friend class sliceref;
};

///////////////////////////////////////////////////////////////////////////////

template <typename... Ts>
struct concat_size;

template <typename T>
struct concat_size<T> {
  const static unsigned value = T::bitcount;
};

template <typename T0, typename... Ts>
struct concat_size<T0, Ts...> {
    const static unsigned value = T0::bitcount + concat_size<Ts...>::value;
};

template <typename... Ts>
struct concat_type;

template <typename T>
struct concat_type<T> {
  using type = typename T::data_type;
};

template <typename T0, typename... Ts>
struct concat_type<T0, Ts...> {
    using type = typename T0::data_type;
};

template<typename... Ts>
class concatref : protected typebase<concat_size<Ts...>::value, typename concat_type<Ts...>::type> {
public:
  using base = typebase<concat_size<Ts...>::value, typename concat_type<Ts...>::type>;
  using base::operator=;
  using data_type = typename base::data_type;

  concatref(Ts&... args) : args_(args...) {}

  concatref& operator=(const concatref& rhs) {
    data_type data(base::bitcount);
    rhs.read_data(data, 0, base::bitcount);
    this->write_data(0, data, 0, base::bitcount);
    return *this;
  }

protected:

  concatref(concatref&&) = default;
  concatref& operator=(concatref&&) = default;

  void read_data(data_type& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= base::bitcount, "invalid read range");
    this->read_data(inout, offset, length, args_, std::index_sequence_for<Ts...>());
  }

  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override {
    CH_CHECK(dst_offset + length <= base::bitcount, "invalid write range");
    this->write_data(dst_offset, in, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }

  template <size_t ...I>
  void read_data(data_type& inout, size_t offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) const {
    this->read_data(inout, offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  template <size_t ...I>
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length, std::tuple<Ts&...>& args, std::index_sequence<I...>) {
    this->write_data(dst_offset, in, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  template <typename U>
  void read_data(data_type& inout, size_t offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitcount);
    cash::internal::read_data(arg, inout, offset, len);
  }

  template <typename U0, typename... Us>
  void read_data(data_type& inout, size_t offset, size_t length, U0& arg0, Us&... args) const {
    if (offset < U0::bitcount) {
      size_t len = std::min<size_t>(length, U0::bitcount);
      cash::internal::read_data(arg0, inout, offset, len);
      offset += len;
      length -= len;
    }
    if (length > 0) {
      this->read_data(inout, offset - U0::bitcount, length, args...);
    }
  }

  template <typename U>
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length, U& arg) {
    size_t len = std::min<size_t>(length, U::bitcount);
    cash::internal::write_data(arg, dst_offset, in, src_offset, len);
  }

  template <typename U0, typename... Us>
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length, U0& arg0, Us&... args) {
    if (dst_offset < U0::bitcount) {
      size_t len = std::min<size_t>(length, U0::bitcount);
      cash::internal::write_data(arg0, dst_offset, in, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length > 0) {
      this->write_data(dst_offset - U0::bitcount, in, src_offset, length, args...);
    }
  }

  std::tuple<Ts&...> args_;

  template <unsigned M, typename Q> friend class typebase;
  template<typename... Ts2, typename> friend concatref<Ts2...> ch_tie(Ts2&... args);
};

}
}
