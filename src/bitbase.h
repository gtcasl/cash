#pragma once

#include "lnode.h"

namespace ch {
namespace internal {

template <unsigned N> class ch_bit;

template <unsigned N>
struct ch_literal : public bitvector {
  static constexpr unsigned bitcount = N;
  using value_type = ch_bit<N>;
  constexpr ch_literal() : bitvector(N) {}
  constexpr ch_literal(const std::string& value) : bitvector(N, value) {}
};

template <typename T>
struct is_ch_literal : public std::false_type {};

template <unsigned N>
struct is_ch_literal< ch_literal<N> > : public std::true_type {};

template <typename T0, typename T1>
struct are_ch_literal {
  static constexpr bool value = (is_ch_literal<T0>::value && is_ch_literal<T1>::value);
};

template <typename T>
struct is_ch_scalar : std::integral_constant<bool,
  std::is_integral<T>::value ||
  std::is_enum<T>::value>
{};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class has_bitcount {
private:
    template <typename U, typename = typename std::enable_if<U::bitcount>::type>
    static std::true_type check(int);

    template <typename>
    static std::false_type check(...);
public:
    static const bool value = decltype(check<typename std::decay<T>::type>(0))::value;
};

static_assert(!has_bitcount<int>::value, ":-(");

struct non_bit_type {
  static constexpr unsigned bitcount = 0;
};

template <typename T0, typename T1>
struct deduce_type_helper {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;
  using U0 = typename std::conditional<has_bitcount<D0>::value, D0, non_bit_type>::type;
  using U1 = typename std::conditional<has_bitcount<D1>::value, D1, non_bit_type>::type;
  using type = typename std::conditional<
    ((int)U0::bitcount != 0) && ((int)U1::bitcount != 0),
    typename std::conditional<((int)U0::bitcount != (int)U1::bitcount), non_bit_type, U0>::type,
    typename std::conditional<((int)U0::bitcount != 0), U0, U1>::type>::type;
};

template <typename... Ts>
struct deduce_type;

template <typename T0, typename T1>
struct deduce_type<T0, T1> {
  using type = typename deduce_type_helper<T0, T1>::type;
  static constexpr unsigned bitcount = type::bitcount;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_type<T0, T1, Ts...> {
  using type = typename deduce_type<typename deduce_type_helper<T0, T1>::type, Ts...>::type;
  static constexpr unsigned bitcount = type::bitcount;
};

template <typename T0, typename T1>
struct deduce_first_type {
  using D0 = typename std::decay<T0>::type;
  using D1 = typename std::decay<T1>::type;
  using U0 = typename std::conditional<has_bitcount<D0>::value, D0, non_bit_type>::type;
  using U1 = typename std::conditional<has_bitcount<D1>::value, D1, non_bit_type>::type;
  using type = typename std::conditional<((int)U0::bitcount != 0), U0, U1>::type;
  static constexpr unsigned bitcount = type::bitcount;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_bitbase;

template <unsigned N>
class ch_bit;

template <typename T>
class refproxy;

template <typename T, unsigned N>
class const_sliceref;

class typebase_itf {
protected:
  virtual void read_data(nodelist& inout, size_t offset, size_t length) const = 0;
  virtual void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) = 0;

  virtual void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const  = 0;
  virtual void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) const = 0;

  friend void read_data(const typebase_itf& obj, nodelist& inout, size_t offset, size_t length);
  friend void write_data(typebase_itf& obj, size_t dst_offset, const nodelist& in, size_t src_offset, size_t length);

  friend void read_bytes(const typebase_itf& obj, uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length);
  friend void write_bytes(const typebase_itf& obj, uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length);
};

inline void read_data(const typebase_itf& obj, nodelist& inout, size_t offset, size_t length) {
  obj.read_data(inout, offset, length);
}

inline void write_data(typebase_itf& obj, size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) {
  obj.write_data(dst_offset, in, src_offset, length);
}

inline void read_bytes(const typebase_itf& obj, uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) {
  obj.read_bytes(dst_offset, out, out_cbsize, src_offset, length);
}

inline void write_bytes(const typebase_itf& obj, uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
  obj.write_bytes(dst_offset, in, in_cbsize, src_offset, length);
}

template <unsigned N>
const ch_bit<N> make_bit(const lnode& node);

template <typename T> const auto make_type(const lnode& node) {
  typename T::value_type ret;
  write_data(ret, 0, {node, 0 , T::bitcount}, 0, T::bitcount);
  return ret;
};

template <unsigned N>
class ch_bitbase : public typebase_itf {
public:
  static constexpr unsigned bitcount = N;
  static_assert(N > 0, "invalid size");

  const auto operator[](size_t index) const {
    return const_sliceref<refproxy<ch_bitbase>, 1>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const {
    return const_sliceref<refproxy<ch_bitbase>, M>(*this, index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const {
    return const_sliceref<refproxy<ch_bitbase>, M>(*this, index * M);
  }

protected:

  void assign(const ch_bitbase& rhs) {
    nodelist data(N);
    ch::internal::read_data(rhs, data, 0, N);
    this->write_data(0, data, 0, N);
  }

  void assign(const ch_literal<N>& rhs) {
    lnode node(rhs);
    this->write_data(0, {node, 0 , N}, 0, N);
  }

  template <typename U,
            CH_REQUIRES(is_ch_scalar<U>::value)>
  void assign(U rhs) {
    lnode node(bitvector(N, rhs));
    this->write_data(0, {node, 0 , N}, 0, N);
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class refproxy : public ch_bitbase<T::bitcount> {
public:
  refproxy() {}
  refproxy(const T& value) : value_(value) {}

protected:

  void read_data(nodelist& inout, size_t offset, size_t length) const override {
    ch::internal::read_data(value_, inout, offset, length);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    ch::internal::read_bytes(value_, dst_offset, out, out_cbsize, src_offset, length);
  }

  // LCOV_EXCL_START
  void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    CH_UNUSED(dst_offset, in, src_offset, length);
    CH_ABORT("invalid call");
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) const override {
    CH_UNUSED(dst_offset, in, in_cbsize, src_offset, length);
    CH_ABORT("invalid call");
  }
  // LCOV_EXCL_STOP

  const T& value_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_sliceref : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  using value_type = ch_bit<N>;

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

  void read_data(nodelist& inout, size_t offset, size_t length) const override {
    ch::internal::read_data(container_, inout, start_ + offset, length);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    ch::internal::read_bytes(container_, start_ + dst_offset, out, out_cbsize, src_offset, length);
  }

  // LCOV_EXCL_START
  void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    CH_UNUSED(dst_offset, in, src_offset, length);
    CH_ABORT("invalid call");
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) const override {
    CH_UNUSED(dst_offset, in, in_cbsize, src_offset, length);
    CH_ABORT("invalid call");
  }
  // LCOV_EXCL_STOP

  T container_;
  size_t start_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class sliceref : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  using value_type = ch_bit<N>;

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

  sliceref& operator=(const ch_literal<N>& rhs) {
    this->assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_ch_scalar<U>::value)>
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

  void read_data(nodelist& inout, size_t offset, size_t length) const override {
    ch::internal::read_data(container_, inout, start_ + offset, length);
  }

  void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    ch::internal::write_data(container_, start_ + dst_offset, in, src_offset, length);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    ch::internal::read_bytes(container_, start_ + dst_offset, out, out_cbsize, src_offset, length);
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) const override {
    ch::internal::write_bytes(container_, start_ + dst_offset, in, in_cbsize, src_offset, length);
  }

  T& container_;
  size_t start_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename... Ts>
struct concat_traits;

template <typename T>
struct concat_traits<T> {
  static constexpr unsigned bitcount = T::bitcount;
};

template <typename T0, typename... Ts>
struct concat_traits<T0, Ts...> {
  static constexpr unsigned bitcount = T0::bitcount + concat_traits<Ts...>::bitcount;
};

template <typename... Ts>
class concatref;

template <typename... Ts>
class concatref : public ch_bitbase<concat_traits<Ts...>::bitcount> {
public:
  using base = ch_bitbase<concat_traits<Ts...>::bitcount>;
  using value_type = ch_bit<base::bitcount>;

  concatref(Ts&... args) : args_(args...) {}

  concatref& operator=(const concatref& rhs) {
    this->assign(rhs);
    return *this;
  }

  concatref& operator=(const base& rhs) {
    this->assign(rhs);
    return *this;
  }

  concatref& operator=(const ch_literal<base::bitcount>& rhs) {
    this->assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_ch_scalar<U>::value)>
  concatref& operator=(U rhs) {
    this->assign(rhs);
    return *this;
  }

protected:

  concatref(concatref&&) = default;
  concatref& operator=(concatref&&) = default;

  // LCOV_EXCL_START
  template <typename U>
  void read_data(nodelist& inout, size_t offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitcount);
    ch::internal::read_data(arg, inout, offset, len);
  }

  template <typename U0, typename... Us>
  void read_data(nodelist& inout, size_t offset, size_t length, U0& arg0, Us&... args) const {
    if (offset < U0::bitcount) {
      size_t len = std::min<size_t>(length, U0::bitcount);
      ch::internal::read_data(arg0, inout, offset, len);
      offset += len;
      length -= len;
    }
    if (length != 0) {
      this->read_data(inout, offset - U0::bitcount, length, args...);
    }
  }

  template <size_t... I>
  void read_data(nodelist& inout, size_t offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) const {
    this->read_data(inout, offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  void read_data(nodelist& inout, size_t offset, size_t length) const override {
    this->read_data(inout, offset, length, args_, std::index_sequence_for<Ts...>());
  }
  // LCOV_EXCL_STOP

  // LCOV_EXCL_START
  template <typename U>
  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitcount);
    ch::internal::read_bytes(arg, dst_offset, out, out_cbsize, src_offset, len);
  }

  template <typename U0, typename... Us>
  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, size_t length, U0& arg0, Us&... args) const {
    if (dst_offset < U0::bitcount) {
      size_t len = std::min<size_t>(length, U0::bitcount);
      ch::internal::read_bytes(arg0, dst_offset, out, out_cbsize, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length != 0) {
      this->read_bytes(dst_offset - U0::bitcount, out, out_cbsize, src_offset, length, args...);
    }
  }

  template <size_t... I>
  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) const {
    this->read_bytes(dst_offset, out, out_cbsize, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    this->read_bytes(dst_offset, out, out_cbsize, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }
  // LCOV_EXCL_STOP

  template <typename U>
  void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length, U& arg) {
    size_t len = std::min<size_t>(length, U::bitcount);
    ch::internal::write_data(arg, dst_offset, in, src_offset, len);
  }

  template <typename U0, typename... Us>
  void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length, U0& arg0, Us&... args) {
    if (dst_offset < U0::bitcount) {
      size_t len = std::min<size_t>(length, U0::bitcount);
      ch::internal::write_data(arg0, dst_offset, in, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length != 0) {
      this->write_data(dst_offset - U0::bitcount, in, src_offset, length, args...);
    }
  }

  template <size_t... I>
  void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length, std::tuple<Ts&...>& args, std::index_sequence<I...>) {
    this->write_data(dst_offset, in, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  void write_data(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    this->write_data(dst_offset, in, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }

  template <typename U>
  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitcount);
    ch::internal::write_bytes(arg, dst_offset, in, in_cbsize, src_offset, len);
  }

  template <typename U0, typename... Us>
  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, size_t length, U0& arg0, Us&... args) const {
    if (dst_offset < U0::bitcount) {
      size_t len = std::min<size_t>(length, U0::bitcount);
      ch::internal::write_bytes(arg0, dst_offset, in, in_cbsize, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length != 0) {
      this->write_bytes(dst_offset - U0::bitcount, in, in_cbsize, src_offset, length, args...);
    }
  }

  template <size_t... I>
  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) const {
    this->write_bytes(dst_offset, in, in_cbsize, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) const override {
    this->write_bytes(dst_offset, in, in_cbsize, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }

  std::tuple<Ts&...> args_;

  template <typename... Ts2, typename> friend concatref<Ts2...> ch_tie(Ts2&... args);
};

}
}
