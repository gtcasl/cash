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

CH_DEF_SFINAE_CHECK(is_bit_compatible, (std::is_base_of<const_bit<T::bitsize>, T>::value
                                        || std::is_same<typename T::traits::value_type, ch_bit<T::bitsize>>::value));

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

template <typename T, unsigned N = std::decay_t<T>::bitsize>
struct is_bit_convertible {
  static constexpr bool value = is_cast_convertible<ch_bit<N>, T>::value;
};

template <typename... Ts>
using are_all_bit_convertible = conjunction<is_bit_convertible<Ts>::value...>;

template <typename... Ts>
using are_all_logic_type = conjunction<is_logic_type<Ts>::value...>;

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

  void set_data(const lnode& data);

  const lnode& get_data() const;

  void write(uint32_t dst_offset, const lnode& data, uint32_t src_offset, uint32_t length);

  bit_buffer clone() const;

  void copy(const bit_buffer& rhs);

  auto get_size() const {
    return size_;
  }

private:
  lnode    src_;
  mutable lnode node_;
  unsigned offset_;
  unsigned size_;
};

struct bit_accessor {
  template <typename T>
  static const bit_buffer& get_buffer(const T& obj) {
    return obj.get_buffer();
  }
  template <typename T>
  static bit_buffer& get_buffer(T& obj) {
    return obj.get_buffer();
  }
  template <typename T>
  static const lnode& get_data(const T& obj) {
    return obj.get_buffer().get_data();
  }
};

#define CH_BIT_READONLY_INTERFACE(type)

#define CH_BIT_WRITABLE_INTERFACE(type)

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class const_bit {
public:
  static constexpr unsigned bitsize = N;
  using traits = logic_traits<const_bit, const_bit, ch_bit<N>, ch_scalar<N>>;

  const_bit() : buffer_(N) {}

  const_bit(const const_bit& rhs) : buffer_(rhs.buffer_.clone()) {}

  const_bit(const_bit&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  template <typename T, CH_REQUIRES(is_logic_type<T>::value)>
  explicit const_bit(const T& rhs) : buffer_(bit_accessor::get_buffer(rhs).clone()) {}

  explicit const_bit(const bit_buffer& buffer) : buffer_(buffer) {
    assert(N == buffer.get_size());
  }

  explicit const_bit(const ch_scalar<N>& rhs) : buffer_(scalar_accessor::get_data(rhs)) {}

  template <typename U,
            CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value), CH_VOID_T>
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

  const auto clone() const {
    return ch_bit<N>(buffer_.clone());
  }

  CH_BIT_READONLY_INTERFACE(const_bit)

protected:

  const_bit& operator=(const const_bit& rhs) {
    buffer_.copy(rhs.buffer_);
    return *this;
  }

  const_bit& operator=(const_bit&& rhs) {
    buffer_ = std::move(rhs.buffer_);
    return *this;
  }

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

  template <typename T, CH_REQUIRES(is_logic_type<T>::value)>
  explicit ch_bit(const T& rhs) : base(rhs) {}

  explicit ch_bit(const bit_buffer& buffer) : base(buffer) {}

  explicit ch_bit(const ch_scalar<N>& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value), CH_VOID_T>
  explicit ch_bit(const U& rhs) : base(rhs) {}

  ch_bit& operator=(const ch_bit& rhs) {
    base::operator =(rhs);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    base::operator =(std::move(rhs));
    return *this;
  }

  ch_bit& operator=(const const_bit<N>& rhs) {
    base::operator =(rhs);
    return *this;
  }

  template <typename T, CH_REQUIRES(is_logic_type<T>::value)>
  ch_bit& operator=(const T& rhs) {
    buffer_.copy(bit_accessor::get_buffer(rhs));
    return *this;
  }

  ch_bit& operator=(const ch_scalar<N>& rhs) {
    buffer_.set_data(scalar_accessor::get_data(rhs));
    return *this;
  }

  template <typename T, CH_REQUIRES(is_integral_or_enum<T>::value), CH_VOID_T>
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

template <typename T, unsigned N = T::bitsize>
using bit_cast_t = std::conditional_t<is_logic_type<T>::value, const T&, ch_bit<N>>;

template <typename T, unsigned N = T::bitsize,
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
  bit_accessor::get_buffer(inout).write(offset, bit_accessor::get_data(arg), 0, T::bitsize);
  return offset + T::bitsize;
}

template <unsigned N, typename T0, typename... Ts>
unsigned cat_impl(ch_bit<N>& inout, unsigned offset, const T0& arg0, const Ts&... args) {
  offset = cat_impl(inout, offset, args...);
  bit_accessor::get_buffer(inout).write(offset, bit_accessor::get_data(arg0), 0, T0::bitsize);
  return offset + T0::bitsize;
}

template <typename... Ts,
         CH_REQUIRES(are_all_bit_convertible<Ts...>::value)>
const auto ch_cat(const Ts&... args) {
  ch_bit<concat_traits<Ts...>::bitsize> ret;
  cat_impl(ret, 0, static_cast<bit_cast_t<Ts>>(args)...);
  return ret;
}

template <typename B, typename A,
          CH_REQUIRES(is_logic_type<B>::value),
          CH_REQUIRES(is_logic_type<A>::value)>
const auto operator,(const B& b, const A& a) {
  return ch_cat(b, a);
}

template <typename... Ts,
         CH_REQUIRES(are_all_logic_type<Ts...>::value)>
auto ch_tie(Ts&... args) {
  return bit_concat<concat_traits<Ts...>::bitsize>({
        bit_accessor::get_buffer(static_cast<bit_cast_t<Ts>>(args))...});
}

// slice functions

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_slice(const T& in, size_t start = 0) {
  return const_bit_slice<N>(bit_accessor::get_buffer(in), start);
}

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_aslice(const T& in, size_t start = 0) {
  return const_bit_slice<N>(bit_accessor::get_buffer(in), start * N);
}

// extend functions

template <unsigned D>
class zext_impl {
public:
    template <typename T>
    const auto operator() (const T& in) {
      return ch_cat(ch_bit<D>(0x0), in);
    }
};

template <>
class zext_impl<0> {
public:
    template <typename T>
    const auto operator() (const T& in) {
      return value_type_t<T>(in);
    }
};

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_zext(const T& in) {
  static_assert(N >= T::bitsize, "invalid extend size");
  return zext_impl<(N-T::bitsize)>()(in);
}

template <unsigned D>
class sext_impl {
public:
  template <typename T>
  const auto operator() (const T& in) {
    auto pad = ch_bit<D>(0x0) - ch_zext<D>(in[T::bitsize - 1]);
    return ch_cat(pad, in);
  }
};

template <>
class sext_impl<0> {
public:
  template <typename T>
  const auto operator() (const T& in) {
    return value_type_t<T>(in);
  }
};

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_sext(const T& in) {
  static_assert(N >= T::bitsize, "invalid extend size");
  return sext_impl<(N-T::bitsize)>()(in);
}

// shuffle functions

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_shuffle(const T& in,
                     const std::array<uint32_t, T::bitsize>& indices) {
  static_assert((T::bitsize % N) == 0, "invalid indices size");
  ch_bit<N> ret;
  for (unsigned i = 0; i < T::bitsize; ++i) {
    ret.template aslice<<(N / T::bitsize)>(i) = in.template aslice<(N / T::bitsize)>(indices[i]);
  }
  return ret;
}

// utils functions

template <typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
void ch_tap(const std::string& name, const T& value) {
  registerTap(name, get_lnode(value));
}

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
