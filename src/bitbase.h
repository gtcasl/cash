#pragma once

#include "lnode.h"
#include "scalar.h"

namespace ch {
namespace internal {

template <typename LogicType, typename ConstType, typename ValueType, typename ScalarType>
struct logic_traits {
  using logic_type  = LogicType;
  using const_type  = ConstType;
  using value_type  = ValueType;
  using scalar_type = ScalarType;
};

template <typename T>
using logic_type_t = typename T::traits::logic_type;

template <typename T>
using value_type_t = typename logic_type_t<T>::traits::value_type;

template <typename T>
using const_type_t = typename logic_type_t<T>::traits::const_type;

template <typename T>
struct is_logic_traits : std::false_type {};

template <typename LogicType, typename ConstType, typename ValueType, typename ScalarType>
struct is_logic_traits<logic_traits<LogicType, ConstType, ValueType, ScalarType>> : std::true_type {};

template <typename T>
using is_logic_type = is_logic_traits<typename T::traits>;

template <unsigned N> class const_bit;

CH_DEF_SFINAE_CHECK(is_ch_bit, (std::is_base_of<const_bit<T::bitsize>, T>::value
                             || std::is_same<typename T::traits::value_type, ch_bit<T::bitsize>>::value));

static_assert(!is_ch_bit<int>::value, ":-(");

template <typename... Ts>
using deduce_ch_bit_t = std::conditional_t<
  is_ch_bit<deduce_type_t<Ts...>>::value, deduce_type_t<Ts...>, non_bitsize_type>;

template <typename T0, typename T1>
using deduce_first_ch_bit_t = std::conditional_t<
  (is_ch_bit<T0>::value || is_ch_bit<T1>::value), deduce_first_type_t<T0, T1>, non_bitsize_type>;

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> class bitbase;

template <unsigned N> class ch_bit;

template <typename T, unsigned N> class const_vec;

template <typename T, unsigned N> class ch_vec;

template <typename T> class refproxy;

template <typename T, unsigned N> class const_sliceref;

class bytes_accessor_if {
protected:
  virtual void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const  = 0;
  virtual void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) = 0;

  template <typename T> friend void read_bytes(const T& obj, uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length);
  template <typename T> friend void write_bytes(T& obj, uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length);
};

class lnode_accessor_if {
protected:
  virtual void read_lnode(nodelist& inout, size_t offset, size_t length) const = 0;
  virtual void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) = 0;

  template <typename T> friend void read_lnode(const T& obj, nodelist& inout, size_t offset, size_t length);
  template <typename T> friend void write_lnode(T& obj, size_t dst_offset, const nodelist& in, size_t src_offset, size_t length);
};

template <typename T>
void read_lnode(const T& obj, nodelist& inout, size_t offset, size_t length) {
  reinterpret_cast<const bitbase<T::bitsize>&>(obj).read_lnode(inout, offset, length);
}

template <typename T>
void write_lnode(T& obj, size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) {
  reinterpret_cast<bitbase<T::bitsize>&>(obj).write_lnode(dst_offset, in, src_offset, length);
}

template <typename T>
void read_bytes(const T& obj, uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) {
  reinterpret_cast<const bitbase<T::bitsize>&>(obj).read_bytes(dst_offset, out, out_cbsize, src_offset, length);
}

template <typename T>
void write_bytes(T& obj, uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
  reinterpret_cast<bitbase<T::bitsize>&>(obj).write_bytes(dst_offset, in, in_cbsize, src_offset, length);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct make_type_impl {
  static const auto make(const nodelist& data) {
    T ret;
    write_lnode(ret, 0, data, 0, T::bitsize);
    return ret;
  }
};

template <typename T, unsigned N>
struct make_type_impl< ch_vec<T, N> > {
  static const auto make(const nodelist& data) {
    ch_vec<T, N> ret;
    unsigned src_offset = 0;
    for (unsigned i = 0; i < N; ++i) {
      ch::internal::write_lnode(ret[i], 0, data, src_offset, T::bitsize);
      src_offset += T::bitsize;
    }
    return ret;
  }
};

template <typename T>
const auto make_type(const lnode& node) {
  nodelist data(T::bitsize, true);
  data.push(node);
  return make_type_impl<value_type_t<T>>::make(data);
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class bitbase : public lnode_accessor_if, public bytes_accessor_if {
public:
  static constexpr unsigned bitsize = N;
  static_assert(N > 0, "invalid size");

protected:

  void assign(const bitbase& rhs) {
    nodelist data(N, false);
    ch::internal::read_lnode(rhs, data, 0, N);
    this->write_lnode(0, data, 0, N);
  }

  void assign(const ch_scalar<N>& rhs) {
    nodelist data(N, false);
    lnode node(rhs.get_value());    
    data.push(node);
    this->write_lnode(0, data, 0, N);
  }

  template <typename U,
            CH_REQUIRES(is_integral_or_enum<U>::value)>
  void assign(const U& rhs) {
    lnode node(bitvector(N, rhs));
    nodelist data(N, false);
    data.push(node);
    this->write_lnode(0, data, 0, N);
  }

  template <typename U,
            CH_REQUIRES(std::is_base_of<bitbase<U::bitsize>, U>::value)>
  void assign(const const_vec<U, (N / U::bitsize)>& rhs) {
    nodelist data(N, false);
    for (auto& item : rhs) {
      ch::internal::read_lnode(item, data, 0, U::bitsize);
    }
    this->write_lnode(0, data, 0, N);
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class refproxy : public bitbase<T::bitsize> {
public:
  refproxy() {}
  refproxy(const T& value) : value_(value) {}

protected:

  void read_lnode(nodelist& inout, size_t offset, size_t length) const override {
    ch::internal::read_lnode(value_, inout, offset, length);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    ch::internal::read_bytes(value_, dst_offset, out, out_cbsize, src_offset, length);
  }

  // LCOV_EXCL_START
  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    CH_UNUSED(dst_offset, in, src_offset, length);
    CH_ABORT("invalid call");
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) override {
    CH_UNUSED(dst_offset, in, in_cbsize, src_offset, length);
    CH_ABORT("invalid call");
  }
  // LCOV_EXCL_STOP

  const T& value_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class const_sliceref : public bitbase<N> {
public:
  using base = bitbase<N>;
  using traits = logic_traits<const_sliceref, const_sliceref, ch_bit<N>, ch_scalar<N>>;

  const_sliceref(const T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bitsize, "invalid slice range");
  }

  const_sliceref(const T&& container, size_t start = 0)
    : container_(std::move(const_cast<T&&>(container)))
    , start_(start) {
    CH_CHECK(start + N <= T::bitsize, "invalid slice range");
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

  void read_lnode(nodelist& inout, size_t offset, size_t length) const override {
    ch::internal::read_lnode(container_, inout, start_ + offset, length);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    ch::internal::read_bytes(container_, start_ + dst_offset, out, out_cbsize, src_offset, length);
  }

  // LCOV_EXCL_START
  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    CH_UNUSED(dst_offset, in, src_offset, length);
    CH_ABORT("invalid call");
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) override {
    CH_UNUSED(dst_offset, in, in_cbsize, src_offset, length);
    CH_ABORT("invalid call");
  }
  // LCOV_EXCL_STOP

  T container_;
  size_t start_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
class sliceref : public bitbase<N> {
public:
  using base = bitbase<N>;
  using traits = logic_traits<sliceref, const_sliceref<T, N>, ch_bit<N>, ch_scalar<N>>;

  sliceref(T& container, size_t start = 0)
    : container_(container)
    , start_(start) {
    CH_CHECK(start + N <= T::bitsize, "invalid slice range");
  }

  sliceref& operator=(const sliceref& rhs) {
    base::assign(rhs);
    return *this;
  }

  sliceref& operator=(const base& rhs) {
    base::assign(rhs);
    return *this;
  }

  sliceref& operator=(const ch_scalar<N>& rhs) {
    base::assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_integral_or_enum<U>::value)>
  sliceref& operator=(const U& rhs) {
    base::assign(rhs);
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

  void read_lnode(nodelist& inout, size_t offset, size_t length) const override {
    ch::internal::read_lnode(container_, inout, start_ + offset, length);
  }

  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    ch::internal::write_lnode(container_, start_ + dst_offset, in, src_offset, length);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    ch::internal::read_bytes(container_, start_ + dst_offset, out, out_cbsize, src_offset, length);
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) override {
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
  static constexpr unsigned bitsize = T::bitsize;
};

template <typename T0, typename... Ts>
struct concat_traits<T0, Ts...> {
  static constexpr unsigned bitsize = T0::bitsize + concat_traits<Ts...>::bitsize;
};

template <typename... Ts>
class concatref;

template <typename... Ts>
class concatref : public bitbase<concat_traits<Ts...>::bitsize> {
public:
  using base = bitbase<concat_traits<Ts...>::bitsize>;
  using traits = logic_traits<concatref, concatref, ch_bit<base::bitsize>, ch_scalar<base::bitsize>>;

  concatref(Ts&... args) : args_(args...) {}

  concatref& operator=(const concatref& rhs) {
    base::assign(rhs);
    return *this;
  }

  concatref& operator=(const base& rhs) {
    base::assign(rhs);
    return *this;
  }

  concatref& operator=(const ch_scalar<base::bitsize>& rhs) {
    base::assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_integral_or_enum<U>::value)>
  concatref& operator=(const U& rhs) {
    base::assign(rhs);
    return *this;
  }

protected:

  concatref(concatref&&) = default;
  concatref& operator=(concatref&&) = default;

  // LCOV_EXCL_START
  template <typename U>
  void read_lnode(nodelist& inout, size_t offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitsize);
    ch::internal::read_lnode(arg, inout, offset, len);
  }

  template <typename U0, typename... Us>
  void read_lnode(nodelist& inout, size_t offset, size_t length, U0& arg0, Us&... args) const {
    if (offset < U0::bitsize) {
      size_t len = std::min<size_t>(length, U0::bitsize);
      ch::internal::read_lnode(arg0, inout, offset, len);
      offset += len;
      length -= len;
    }
    if (length != 0) {
      this->read_lnode(inout, offset - U0::bitsize, length, args...);
    }
  }

  template <size_t... I>
  void read_lnode(nodelist& inout, size_t offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) const {
    this->read_lnode(inout, offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  void read_lnode(nodelist& inout, size_t offset, size_t length) const override {
    this->read_lnode(inout, offset, length, args_, std::index_sequence_for<Ts...>());
  }
  // LCOV_EXCL_STOP

  // LCOV_EXCL_START
  template <typename U>
  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, size_t length, U& arg) const {
    size_t len = std::min<size_t>(length, U::bitsize);
    ch::internal::read_bytes(arg, dst_offset, out, out_cbsize, src_offset, len);
  }

  template <typename U0, typename... Us>
  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, size_t length, U0& arg0, Us&... args) const {
    if (dst_offset < U0::bitsize) {
      size_t len = std::min<size_t>(length, U0::bitsize);
      ch::internal::read_bytes(arg0, dst_offset, out, out_cbsize, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length != 0) {
      this->read_bytes(dst_offset - U0::bitsize, out, out_cbsize, src_offset, length, args...);
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
  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length, U& arg) {
    size_t len = std::min<size_t>(length, U::bitsize);
    ch::internal::write_lnode(arg, dst_offset, in, src_offset, len);
  }

  template <typename U0, typename... Us>
  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length, U0& arg0, Us&... args) {
    if (dst_offset < U0::bitsize) {
      size_t len = std::min<size_t>(length, U0::bitsize);
      ch::internal::write_lnode(arg0, dst_offset, in, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length != 0) {
      this->write_lnode(dst_offset - U0::bitsize, in, src_offset, length, args...);
    }
  }

  template <size_t... I>
  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length, std::tuple<Ts&...>& args, std::index_sequence<I...>) {
    this->write_lnode(dst_offset, in, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    this->write_lnode(dst_offset, in, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }

  template <typename U>
  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, size_t length, U& arg) {
    size_t len = std::min<size_t>(length, U::bitsize);
    ch::internal::write_bytes(arg, dst_offset, in, in_cbsize, src_offset, len);
  }

  template <typename U0, typename... Us>
  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, size_t length, U0& arg0, Us&... args) {
    if (dst_offset < U0::bitsize) {
      size_t len = std::min<size_t>(length, U0::bitsize);
      ch::internal::write_bytes(arg0, dst_offset, in, in_cbsize, src_offset, len);
      dst_offset += len;
      src_offset += len;
      length -= len;
    }
    if (length != 0) {
      this->write_bytes(dst_offset - U0::bitsize, in, in_cbsize, src_offset, length, args...);
    }
  }

  template <size_t... I>
  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, size_t length, const std::tuple<Ts&...>& args, std::index_sequence<I...>) {
    this->write_bytes(dst_offset, in, in_cbsize, src_offset, length, std::get<sizeof...(Ts) - 1 - I>(args)...);
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) override {
    this->write_bytes(dst_offset, in, in_cbsize, src_offset, length, args_, std::index_sequence_for<Ts...>());
  }

  std::tuple<Ts&...> args_;

  template <typename... Ts2, typename> friend concatref<Ts2...> ch_tie(Ts2&... args);
};

}
}
