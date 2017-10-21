#pragma once

#include "lnode.h"
#include "scalar.h"

namespace ch {
namespace internal {

void registerTap(const std::string& name, const lnode& node);

void createPrintNode(const std::string& format, const std::initializer_list<lnode>& args);

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> class const_bit;

template <unsigned N> class const_bit_slice;

template <unsigned N> class bit_slice;

template <unsigned N> class bit_concat;

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

CH_DEF_SFINAE_CHECK(is_logic_type, is_logic_traits<typename T::traits>::value);

CH_DEF_SFINAE_CHECK(is_bit_compatible, (!is_scalar_type<T>::value
                                     && std::is_same<ch_bit<T::bitwidth>, value_type_t<T>>::value));

template <typename... Ts>
using deduce_ch_bit_t = std::conditional_t<
  is_bit_compatible<deduce_type_t<Ts...>>::value,
  deduce_type_t<Ts...>,
  non_bitsize_type>;

template <typename T0, typename T1>
using deduce_first_ch_bit_t = std::conditional_t<
  (is_bit_compatible<T0>::value || is_bit_compatible<T1>::value),
  deduce_first_type_t<T0, T1>,
  non_bitsize_type>;

template <typename T, unsigned N = std::decay_t<T>::bitwidth>
using is_bit_convertible = is_cast_convertible<ch_bit<N>, T>;

template <typename... Ts>
using are_all_bit_convertible = conjunction<is_bit_convertible<Ts>::value...>;

template <typename... Ts>
using are_all_logic_type = conjunction<is_logic_type<Ts>::value...>;

///////////////////////////////////////////////////////////////////////////////

template <typename... Ts>
struct concat_traits;

template <typename T>
struct concat_traits<T> {
  static constexpr unsigned bitwidth = T::bitwidth;
};

template <typename T0, typename... Ts>
struct concat_traits<T0, Ts...> {
  static constexpr unsigned bitwidth = T0::bitwidth + concat_traits<Ts...>::bitwidth;
};

///////////////////////////////////////////////////////////////////////////////

class bit_buffer {
public:
  bit_buffer(unsigned size);

  bit_buffer(const bit_buffer& rhs);

  bit_buffer(bit_buffer&& rhs);

  bit_buffer(const lnode& data);

  bit_buffer(lnode&& data);

  bit_buffer(unsigned size, const bit_buffer& buffer, unsigned offset = 0);

  bit_buffer& operator=(const bit_buffer& rhs);

  bit_buffer& operator=(bit_buffer&& rhs);

  void write(uint32_t dst_offset, const lnode& data, uint32_t src_offset, uint32_t length);

  void set_data(const lnode& data);

  const lnode& get_data() const;

  const lnode& get_source() const;

  lnode& get_source();

  auto get_offset() const {
    return offset_;
  }

  auto get_size() const {
    return size_;
  }

private:

  lnode    source_;
  mutable lnode proxy_;
  unsigned offset_;
  unsigned size_;
};

struct bit_accessor {
  template <typename T>
  static const auto& get_buffer(const T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static auto& get_buffer(T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static const auto& get_data(const T& obj) {
    return obj.get_buffer().get_data();
  }

  template <typename U, typename V,
            CH_REQUIRES(U::bitwidth == V::bitwidth)>
  static void copy(U& dst, const V& src) {
    auto& d = dst.get_buffer().get_source();
    auto d_offset = dst.get_buffer().get_offset();
    const auto& s = src.get_buffer().get_source();
    auto s_offset = src.get_buffer().get_offset();
    d.write(d_offset, s, s_offset, U::bitwidth, U::bitwidth);
  }

  template <typename T>
  static auto cloneBuffer(const T& obj) {
    bit_buffer ret(T::bitwidth);
    auto& s = obj.get_buffer().get_source();
    auto s_offset = obj.get_buffer().get_offset();
    ret.write(0, s, s_offset, T::bitwidth);
    return ret;
  }

  template <typename T>
  static const auto clone(const T& obj) {
    T tmp(bit_buffer(T::bitwidth, obj.get_buffer(), 0));
    return value_type_t<T>(bit_buffer(tmp.get_data().clone()));
  }

  template <typename D, typename T>
  static auto cast(const T& obj) {
    return D(bit_buffer(T::bitwidth, obj.get_buffer(), 0));
  }
};

#define CH_BIT_READONLY_INTERFACE(type) \
  template <typename R> \
  auto as() const { \
    return ch::internal::bit_accessor::cast<R>(*this); \
  } \
  auto asBits() const { \
    return this->as<ch_bit<type::bitwidth>>(); \
  }

#define CH_BIT_WRITABLE_INTERFACE(type)

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class const_bit {
public:
  static constexpr unsigned bitwidth = N;
  using traits = logic_traits<const_bit, const_bit, ch_bit<N>, ch_scalar<N>>;

  const_bit() : buffer_(N) {}

  const_bit(const const_bit& rhs) : buffer_(bit_accessor::cloneBuffer(rhs)) {}

  const_bit(const_bit&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  explicit const_bit(const ch_scalar<N>& rhs) : buffer_(scalar_accessor::get_data(rhs)) {}

  explicit const_bit(const bit_buffer& buffer) : buffer_(buffer) {
    assert(N == buffer.get_size());
  }

  template <typename T,
            CH_REQUIRES(is_logic_type<T>::value),
            CH_REQUIRES(N == T::bitwidth)>
  explicit const_bit(const T& rhs) : buffer_(bit_accessor::cloneBuffer(rhs)) {}

  template <typename U,
            CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  explicit const_bit(const U& rhs) : buffer_(bitvector(N, rhs)) {}

  const auto operator[](size_t index) const {
    return const_bit_slice<1>(buffer_, index);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return const_bit_slice<M>(buffer_, start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return const_bit_slice<M>(buffer_, start * M);
  }

  CH_BIT_READONLY_INTERFACE(const_bit)

protected:

  const bit_buffer& get_buffer() const {
    return buffer_;
  }

  bit_buffer& get_buffer() {
    return buffer_;
  }

  bit_buffer buffer_;

  friend class bit_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_bit : public const_bit<N> {
public:
  using base = const_bit<N>;
  using traits = logic_traits<ch_bit, const_bit<N>, ch_bit, ch_scalar<N>>;
  using base::buffer_;
      
  ch_bit() {}
  
  ch_bit(const ch_bit& rhs) : base(rhs) {}

  ch_bit(ch_bit&& rhs) : base(rhs) {}

  ch_bit(const const_bit<N>& rhs) : base(rhs) {}

  ch_bit(const ch_scalar<N>& rhs) : base(rhs) {}

  template <typename T,
            CH_REQUIRES(is_logic_type<T>::value),
            CH_REQUIRES(N == T::bitwidth)>
  explicit ch_bit(const T& rhs) : base(rhs) {}

  explicit ch_bit(const bit_buffer& buffer) : base(buffer) {}

  template <typename U,
            CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  explicit ch_bit(const U& rhs) : base(rhs) {}

  ch_bit& operator=(const ch_bit& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    buffer_ = std::move(rhs.buffer_);
    return *this;
  }

  ch_bit& operator=(const const_bit<N>& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  template <typename T,
            CH_REQUIRES(is_logic_type<T>::value),
            CH_REQUIRES(N == T::bitwidth)>
  ch_bit& operator=(const T& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_bit& operator=(const ch_scalar<N>& rhs) {
    buffer_.set_data(scalar_accessor::get_data(rhs));
    return *this;
  }

  template <typename T, CH_REQUIRES(is_integral_or_enum<T>::value)>
  ch_bit& operator=(const T& rhs) {
    buffer_.set_data(bitvector(N, rhs));
    return *this;
  }

  const auto operator[](size_t index) const {
    return const_bit_slice<1>(buffer_, index);
  }

  auto operator[](size_t index) {
    return ch::internal::bit_slice<1>(buffer_, index); \
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return const_bit_slice<M>(buffer_, start);
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return ch::internal::bit_slice<M>(buffer_, start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return const_bit_slice<M>(buffer_, start * M);
  }

  template <unsigned M>
  auto aslice(size_t start = 0) {
   return ch::internal::bit_slice<M>(buffer_, start * M);
  }

  CH_BIT_WRITABLE_INTERFACE(ch_bit)
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N = T::bitwidth>
using bit_cast_t = std::conditional_t<is_logic_type<T>::value, const T&, ch_bit<N>>;

template <typename T, unsigned N = T::bitwidth,
          CH_REQUIRES(is_bit_convertible<T, N>::value)>
lnode get_lnode(const T& rhs) {
  bit_cast_t<T, N> x(rhs);
  return bit_accessor::get_data(x);
}

template <typename T>
const auto make_type(const lnode& node) {
  return T(bit_buffer(node));
};

// concatenation functions

template <unsigned N, typename T>
unsigned cat_impl(ch_bit<N>& inout, unsigned offset, const T& arg) {
  bit_accessor::get_buffer(inout).write(offset, bit_accessor::get_data(arg), 0, T::bitwidth);
  return offset + T::bitwidth;
}

template <unsigned N, typename T0, typename... Ts>
unsigned cat_impl(ch_bit<N>& inout, unsigned offset, const T0& arg0, const Ts&... args) {
  offset = cat_impl(inout, offset, args...);
  bit_accessor::get_buffer(inout).write(offset, bit_accessor::get_data(arg0), 0, T0::bitwidth);
  return offset + T0::bitwidth;
}

template <typename... Ts,
         CH_REQUIRES(are_all_bit_convertible<Ts...>::value)>
const auto ch_cat(const Ts&... args) {
  ch_bit<concat_traits<Ts...>::bitwidth> ret;
  cat_impl(ret, 0, static_cast<bit_cast_t<Ts>>(args)...);
  return ret;
}

template <typename B, typename A,
          CH_REQUIRES(is_bit_convertible<B>::value),
          CH_REQUIRES(is_bit_convertible<A>::value)>
const auto operator,(const B& b, const A& a) {
  return ch_cat(b, a);
}

template <typename... Ts,
         CH_REQUIRES(are_all_logic_type<Ts...>::value)>
auto ch_tie(Ts&... args) {
  return bit_concat<concat_traits<Ts...>::bitwidth>({
        bit_accessor::get_buffer(args)...});
}

// clone function

template <typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
const auto ch_clone(const T& obj) {
  return bit_accessor::clone(obj);
}

// slice functions

template <unsigned N, typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
const auto ch_slice(const T& obj, size_t start = 0) {
  return const_bit_slice<N>(bit_accessor::get_buffer(obj), start);
}

template <unsigned N, typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
auto ch_slice(T& obj, size_t start = 0) {
  return bit_slice<N>(bit_accessor::get_buffer(obj), start);
}

template <unsigned N, typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
const auto ch_aslice(const T& obj, size_t start = 0) {
  return const_bit_slice<N>(bit_accessor::get_buffer(obj), start * N);
}

template <unsigned N, typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
auto ch_aslice(T& obj, size_t start = 0) {
  return bit_slice<N>(bit_accessor::get_buffer(obj), start * N);
}

// zero-extend function

template <unsigned D>
class zext_impl {
public:
    template <typename T>
    const auto operator() (const T& obj) {
      return ch_cat(ch_bit<D>(0x0), obj);
    }
};

template <>
class zext_impl<0> {
public:
    template <typename T>
    const auto operator() (const T& obj) {
      return ch_bit<T::bitwidth>(obj);
    }
};

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_zext(const T& obj) {
  static_assert(N >= T::bitwidth, "invalid extend size");
  return zext_impl<(N-T::bitwidth)>()(obj);
}

// sign-extend function

template <unsigned D>
class sext_impl {
public:
  template <typename T>
  const auto operator() (const T& obj) {
    auto pad = ch_bit<D>(0x0) - ch_zext<D>(obj[T::bitwidth - 1]);
    return ch_cat(pad, obj);
  }
};

template <>
class sext_impl<0> {
public:
  template <typename T>
  const auto operator() (const T& obj) {
    return ch_bit<T::bitwidth>(obj);
  }
};

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_sext(const T& obj) {
  static_assert(N >= T::bitwidth, "invalid extend size");
  return sext_impl<(N-T::bitwidth)>()(obj);
}

// shuffle functions

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_shuffle(const T& obj,
                      const std::array<uint32_t, T::bitwidth>& indices) {
  static_assert((T::bitwidth % N) == 0, "invalid indices size");
  ch_bit<N> ret;
  for (unsigned i = 0; i < T::bitwidth; ++i) {
    ret.template aslice<<(N / T::bitwidth)>(i) = obj.template aslice<(N / T::bitwidth)>(indices[i]);
  }
  return ret;
}

// tap functions

template <typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
void ch_tap(const std::string& name, const T& value) {
  registerTap(name, get_lnode(value));
}

// print functions

const ch_bit<64> ch_getTick();

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRES(are_all_bit_convertible<Args...>::value)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

}
}

#define CH_TIE(...) std::forward_as_tuple(__VA_ARGS__)

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
