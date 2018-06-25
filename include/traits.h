#pragma once

#include "lnode.h"

#define CH_OP_ARY(x)   (x & (0x3 << 5))
#define CH_OP_CLASS(x) (x & (0x7 << 7))

#define CH_OP_TYPE(n, v) op_##n = v,
#define CH_OP_NAME(n, v) #n,
#define CH_OP_INDEX(op)  (op & 0x1f)
#define CH_OP_ENUM(m) \
  m(eq,     0 | op_binary | op_compare | op_symmetric) \
  m(ne,     1 | op_binary | op_compare | op_symmetric) \
  m(lt,     2 | op_binary | op_compare) \
  m(gt,     3 | op_binary | op_compare) \
  m(le,     4 | op_binary | op_compare) \
  m(ge,     5 | op_binary | op_compare) \
  m(inv,    6 | op_unary  | op_bitwise) \
  m(and,    7 | op_binary | op_bitwise | op_symmetric) \
  m(or,     8 | op_binary | op_bitwise | op_symmetric) \
  m(xor,    9 | op_binary | op_bitwise | op_symmetric) \
  m(andr,  10 | op_unary  | op_reduce) \
  m(orr,   11 | op_unary  | op_reduce) \
  m(xorr,  12 | op_unary  | op_reduce) \
  m(sll,   13 | op_binary | op_shift) \
  m(srl,   14 | op_binary | op_shift) \
  m(sra,   15 | op_binary | op_shift) \
  m(add,   16 | op_binary | op_arithm | op_symmetric) \
  m(sub,   17 | op_binary | op_arithm) \
  m(neg,   18 | op_unary  | op_arithm) \
  m(mult,  19 | op_binary | op_arithm | op_symmetric) \
  m(div,   20 | op_binary | op_arithm) \
  m(mod,   21 | op_binary | op_arithm) \
  m(zext,  22 | op_unary  | op_misc) \
  m(sext,  23 | op_unary  | op_misc)

namespace ch {
namespace internal {

enum op_flags {
  op_unary   = 0 << 5,
  op_binary  = 1 << 5,
  op_tenary  = 2 << 5,
  op_nary    = 3 << 5,

  op_bitwise = 0 << 7,
  op_compare = 1 << 7,
  op_arithm  = 2 << 7,
  op_shift   = 3 << 7,
  op_reduce  = 4 << 7,
  op_misc    = 5 << 7,

  op_symmetric = 1 << 10,
};

enum ch_op {
  CH_OP_ENUM(CH_OP_TYPE)
};

const char* to_string(ch_op op);

///////////////////////////////////////////////////////////////////////////////

enum traits_type {
  traits_none      = 0x0,
  traits_logic     = 0x1,
  traits_scalar    = 0x2,
  traits_io        = 0x4,
  traits_udf       = 0x8,
  traits_logic_io  = traits_logic | traits_io,
  traits_scalar_io = traits_scalar | traits_io,
};

CH_DEF_SFINAE_CHECK(is_object_type, (T::traits::type & (traits_logic | traits_scalar)));

template <typename T, typename Enable = void>
struct width_value_impl {
  static constexpr uint32_t value = 0;
};

template <typename T>
struct width_value_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  static constexpr uint32_t value = std::numeric_limits<T>::digits +
                                    std::numeric_limits<T>::is_signed;
};

template <typename T>
struct width_value_impl<T, std::enable_if_t<is_object_type_v<T>>> {
  static constexpr uint32_t value = T::traits::bitwidth;
};

template <typename... Ts>
struct width_impl;

template <typename T>
struct width_impl<T> {
  static constexpr uint32_t value = width_value_impl<T>::value;
};

template <typename T0, typename... Ts>
struct width_impl<T0, Ts...> {
  static constexpr uint32_t value = T0::traits::bitwidth + width_impl<Ts...>::value;
};

template <typename... Ts>
inline constexpr uint32_t width_v = width_impl<std::decay_t<Ts>...>::value;

template <typename T, typename Enable = void>
struct signed_impl {
  static constexpr bool value = false;
};

template <typename T>
struct signed_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  static constexpr bool value = std::numeric_limits<T>::is_signed;
};

template <typename T>
struct signed_impl<T, std::enable_if_t<is_object_type_v<T>>> {
  static constexpr bool value = T::traits::is_signed;
};

template <typename T>
inline constexpr bool signed_v = signed_impl<std::decay_t<T>>::value;

struct non_ch_type {
  struct traits {
    static constexpr traits_type type = traits_none;
    static constexpr unsigned bitwidth = 0;
    static constexpr bool is_signed = false;
  };
};

template <typename T>
using ch_type_t = std::conditional_t<is_object_type_v<T>, T, non_ch_type>;

template <bool resize, typename T0, typename T1>
struct deduce_type_impl {
  using D0 = std::decay_t<T0>;
  using D1 = std::decay_t<T1>;
  using U0 = std::conditional_t<is_object_type_v<D0>, D0, non_ch_type>;
  using U1 = std::conditional_t<is_object_type_v<D1>, D1, non_ch_type>;
  using type = std::conditional_t<(width_v<U0> != 0) && (width_v<U1> != 0),
    std::conditional_t<(width_v<U0> == width_v<U1>) || ((width_v<U0> > width_v<U1>) && resize), U0,
        std::conditional_t<(width_v<U0> < width_v<U1>) && resize, U1, non_ch_type>>,
          std::conditional_t<(width_v<U0> != 0), U0, U1>>;
};

template <bool resize, typename... Ts>
struct deduce_type;

template <bool resize, typename T0, typename T1>
struct deduce_type<resize, T0, T1> {
  using type = typename deduce_type_impl<resize, T0, T1>::type;
};

template <bool resize, typename T0, typename T1, typename... Ts>
struct deduce_type<resize, T0, T1, Ts...> {
  using type = typename deduce_type<resize, typename deduce_type_impl<resize, T0, T1>::type, Ts...>::type;
};

template <bool resize, typename... Ts>
using deduce_type_t = typename deduce_type<resize, Ts...>::type;

template <typename T0, typename T1>
struct deduce_first_type_impl {
  using D0 = std::decay_t<T0>;
  using D1 = std::decay_t<T1>;
  using U0 = std::conditional_t<is_object_type_v<D0>, D0, non_ch_type>;
  using U1 = std::conditional_t<is_object_type_v<D1>, D1, non_ch_type>;
  using type = std::conditional_t<(width_v<U0> != 0), U0, U1>;
};

template <typename T0, typename T1>
using deduce_first_type_t = typename deduce_first_type_impl<T0, T1>::type;

}
}
