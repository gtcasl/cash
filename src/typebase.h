#pragma once

#include "common.h"
#include "bitvector.h"

namespace cash {
namespace internal {

template <typename T>
struct data_traits;

template <typename T>
struct is_bit_scalar : std::integral_constant<bool,
  std::is_integral<T>::value ||
  std::is_enum<T>::value>
{};

///////////////////////////////////////////////////////////////////////////////

struct non_bit_type {
  static constexpr unsigned bitcount = 0;
};

template <typename T>
class has_bitcount {
private:
    template <typename U, typename = typename std::enable_if<!std::is_member_pointer<decltype(&U::bitcount)>::value>::type>
    static std::true_type check(int);

    template <typename>
    static std::false_type check(...);
public:
    static const bool value = decltype(check<T>(0))::value;
};

template <typename T0, typename T1>
struct deduce_type_helper2 {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;
  using U0 = typename std::conditional<has_bitcount<D0>::value, D0, non_bit_type>::type;
  using U1 = typename std::conditional<has_bitcount<D1>::value, D1, non_bit_type>::type;
  using type = typename std::conditional<
    (U0::bitcount != 0) && (U1::bitcount != 0),
    typename std::conditional<(U0::bitcount != U1::bitcount), non_bit_type, U0>::type,
    typename std::conditional<(U0::bitcount != 0), U0, U1>::type>::type;
};

template <typename T0, typename... Ts>
struct deduce_type_helper;

template <typename T0, typename T1>
struct deduce_type_helper<T0, T1> {
  using type = typename deduce_type_helper2<T0, T1>::type;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_type_helper<T0, T1, Ts...> {
  using type = typename deduce_type_helper<typename deduce_type_helper2<T0, T1>::type, Ts...>::type;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_type {
  using type = typename deduce_type_helper<T0, T1, Ts...>::type;
  static constexpr unsigned bitcount = type::bitcount;
};

template <typename T0, typename T1>
struct deduce_first_type {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;  
  using U0 = typename std::conditional<has_bitcount<D0>::value, D0, non_bit_type>::type;
  using U1 = typename std::conditional<has_bitcount<D1>::value, D1, non_bit_type>::type;
  using type = typename std::conditional<(U0::bitcount != 0), U0, U1>::type;
  static constexpr unsigned bitcount = type::bitcount;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class nodelist {
public:
  using data_t = T;

  nodelist(uint32_t capacity) : capacity_(capacity), size_(0) {}

  nodelist(const T& src, uint32_t offset, uint32_t length)
    : nodelist(length) {
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

  void push(const T& src, uint32_t offset, uint32_t length) {
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
    const T& src;
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
protected:

  virtual void read_data(nodelist<T>& inout, size_t offset, size_t length) const = 0;
  virtual void write_data(size_t dst_offset, const nodelist<T>& in, size_t src_offset, size_t length) = 0;

  template <typename U> friend void read_data(const typebase_itf<U>& node, nodelist<U>& inout, size_t offset, size_t length);
  template <typename U> friend void write_data(typebase_itf<U>& node, size_t dst_offset, const nodelist<U>& in, size_t src_offset, size_t length);
};

template <typename T>
void read_data(const typebase_itf<T>& node, nodelist<T>& inout, size_t offset, size_t length) {
  node.read_data(inout, offset, length);
}

template <typename T>
void write_data(typebase_itf<T>& node, size_t dst_offset, const nodelist<T>& in, size_t src_offset, size_t length) {
  node.write_data(dst_offset, in, src_offset, length);
}

template <unsigned N, typename T> class typebase;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class refproxy : public typebase_itf<typename T::data_t> {
public:
  static constexpr unsigned bitcount = T::bitcount;
  using data_t = typename T::data_t;

  refproxy() {}
  refproxy(const T& value) : value_(value) {}

protected:

  void read_data(nodelist<data_t>& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= bitcount, "invalid read range");
    cash::internal::read_data(value_, inout, offset, length);
  }

  void write_data(size_t dst_offset, const nodelist<data_t>& in, size_t src_offset, size_t length) override {
    CH_UNUSED(dst_offset, in, src_offset, length);
    CH_ABORT("invalid call");
  }

  const T& value_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_sliceref : public typebase<N, typename T::data_t> {
public:
  static_assert(N <= T::bitcount, "invalid slice size");
  using base = typebase<N, typename T::data_t>;
  using data_t  = typename base::data_t;
  using value_t = typename data_traits<data_t>:: template device_t<base::bitcount>;

  const_sliceref(const T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bitcount, "invalid slice range");
  }

  const_sliceref(const T&& container, size_t start = 0)
    : container_(std::move(const_cast<T&&>(container)))
    , start_(start) {
    CH_CHECK(start + N <= T::bitcount, "invalid slice range");
  }

  const auto operator[](size_t index) const & {
    return const_sliceref<T, 1>(container_, start_ + index);
  }

  const auto operator[](size_t index) const && {
    return const_sliceref<T, 1>(std::move(container_), start_ + index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const & {
    return const_sliceref<T, M>(container_, start_ + index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(container_), start_ + index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const & {
    return const_sliceref<T, M>(container_, start_ + index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const && {
    return const_sliceref<T, M>(std::move(container_), start_ + index * M);
  }

protected:

  void read_data(nodelist<data_t>& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid read range");
    cash::internal::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const nodelist<data_t>& in, size_t src_offset, size_t length) override {
    CH_CHECK(dst_offset + length <= N, "invalid write range");
    cash::internal::write_data(container_, start_ + dst_offset, in, src_offset, length);
  }

  T container_;
  size_t start_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class sliceref : public typebase<N, typename T::data_t> {
public:
  static_assert(N <= T::bitcount, "invalid slice size");
  using base = typebase<N, typename T::data_t>;
  using data_t  = typename base::data_t;
  using value_t = typename data_traits<data_t>:: template device_t<base::bitcount>;

  sliceref(T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bitcount, "invalid slice range");
  }

  sliceref& operator=(const sliceref& rhs) {
    this->assign(rhs);
    return *this;
  }

  sliceref& operator=(const base& rhs) {
    this->assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_bit_scalar<U>::value)>
  sliceref& operator=(U rhs) {
    this->assign(rhs);
    return *this;
  }

  const auto operator[](size_t index) const {
    return sliceref<T, 1>(container_, start_ + index);
  }

  auto operator[](size_t index) {
    return sliceref<T, 1>(container_, start_ + index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const {
    return sliceref<T, M>(container_, start_ + index);
  }

  template <unsigned M>
  auto slice(size_t index = 0) {
    return sliceref<T, M>(container_, start_ + index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const {
    return sliceref<T, M>(container_, start_ + index * M);
  }

  template <unsigned M>
  auto aslice(size_t index = 0) {
    return sliceref<T, M>(container_, start_ + index * M);
  }

protected:

  void read_data(nodelist<data_t>& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= N, "invalid read range");
    cash::internal::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const nodelist<data_t>& in, size_t src_offset, size_t length) override {
    CH_CHECK(dst_offset + length <= N, "invalid write range");
    cash::internal::write_data(container_, start_ + dst_offset, in, src_offset, length);
  }

  T& container_;
  size_t start_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename... Ts>
struct concat_info;

template <typename T>
struct concat_info<T> {
  static constexpr unsigned bitcount = T::bitcount;
  using data_t = typename T::data_t;
};

template <typename T0, typename... Ts>
struct concat_info<T0, Ts...> {
    static constexpr unsigned bitcount = T0::bitcount + concat_info<Ts...>::bitcount;
    using data_t = typename T0::data_t;
};

template <typename... Ts>
class concatref;

template <typename... Ts>
class concatref : public typebase<concat_info<Ts...>::bitcount, typename concat_info<Ts...>::data_t> {
public:
  using base = typebase<concat_info<Ts...>::bitcount, typename concat_info<Ts...>::data_t>;
  using data_t  = typename base::data_t;
  using value_t = typename data_traits<data_t>:: template device_t<base::bitcount>;

  concatref(Ts&... args) : args_(args...) {}

  concatref& operator=(const concatref& rhs) {
    this->assign(rhs);
    return *this;
  }

  concatref& operator=(const base& rhs) {
    this->assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_bit_scalar<U>::value)>
  concatref& operator=(U rhs) {
    this->assign(rhs);
    return *this;
  }

protected:

  concatref(concatref&&) = default;
  concatref& operator=(concatref&&) = default;

  void read_data(nodelist<data_t>& inout, size_t offset, size_t length) const override {
    CH_CHECK(offset + length <= base::bitcount, "invalid read range");
    this->read_data(inout, offset, length, args_, std::index_sequence_for<Ts...>());
  }

  void write_data(size_t dst_offset, const nodelist<data_t>& in, size_t src_offset, size_t length) override {
    CH_CHECK(dst_offset + length <= base::bitcount, "invalid write range");
    this->write_data(dst_offset, in, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }

  template <size_t... I>
  void read_data(nodelist<data_t>& inout, size_t offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) const {
    this->read_data(inout, offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  template <size_t... I>
  void write_data(size_t dst_offset, const nodelist<data_t>& in, size_t src_offset, size_t length, std::tuple<Ts&...>& args, std::index_sequence<I...>) {
    this->write_data(dst_offset, in, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  template <typename U>
  void read_data(nodelist<data_t>& inout, size_t offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitcount);
    cash::internal::read_data(arg, inout, offset, len);
  }

  template <typename U0, typename... Us>
  void read_data(nodelist<data_t>& inout, size_t offset, size_t length, U0& arg0, Us&... args) const {
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
  void write_data(size_t dst_offset, const nodelist<data_t>& in, size_t src_offset, size_t length, U& arg) {
    size_t len = std::min<size_t>(length, U::bitcount);
    cash::internal::write_data(arg, dst_offset, in, src_offset, len);
  }

  template <typename U0, typename... Us>
  void write_data(size_t dst_offset, const nodelist<data_t>& in, size_t src_offset, size_t length, U0& arg0, Us&... args) {
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

  template <typename... Ts2, typename> friend concatref<Ts2...> ch_tie(Ts2&... args);
};

}
}
