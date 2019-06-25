#pragma once

#include "bitvector.h"

namespace ch {
namespace internal {

#ifndef CASH_BLOCK_SIZE
  #define CASH_BLOCK_SIZE 8
#endif

template <unsigned N> class ch_sbit;
template <unsigned N> class ch_sint;
template <unsigned N> class ch_suint;

template <unsigned N> class ch_bit;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

using block_type = std::conditional_t<CASH_BLOCK_SIZE == 1, uint8_t,
                     std::conditional_t<CASH_BLOCK_SIZE == 2, uint16_t,
                       std::conditional_t<CASH_BLOCK_SIZE == 4, uint32_t,
                         std::conditional_t<CASH_BLOCK_SIZE == 8, uint64_t,
                           std::nullptr_t>>>>;

using sdata_type = bitvector<block_type>;

enum traits_type {
  traits_none      = 0x00,
  traits_logic     = 0x01,
  traits_system    = 0x02,
  traits_logic_io  = 0x04,
  traits_system_io = 0x08,
};

enum class ch_direction {
  in    = 0x1,
  out   = 0x2,
  inout = in | out,
};

inline constexpr auto operator|(ch_direction lsh, ch_direction rhs) {
  return ch_direction((int)lsh | (int)rhs);
}

template <typename T>
inline constexpr ch_direction ch_direction_v = std::decay_t<T>::traits::direction;

CH_DEF_SFINAE_CHECK(is_object_type, (T::traits::type != traits_none));

CH_DEF_SFINAE_CHECK(is_data_type, 0 != (T::traits::type & (traits_logic | traits_system)));

CH_DEF_SFINAE_CHECK(is_io_type, 0 != (T::traits::type & (traits_logic_io | traits_system_io)));

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
struct width_impl {
  static constexpr uint32_t value = 0;
};

template <typename T>
struct width_impl<T, std::enable_if_t<is_object_type_v<T>>> {
  static constexpr uint32_t value = T::traits::bitwidth;
};

template <typename T>
struct width_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  static constexpr uint32_t value = bitwidth_v<T>;
};

template <typename... Ts>
struct width_list_impl;

template <typename T>
struct width_list_impl<T> {
  static constexpr uint32_t value = width_impl<T>::value;
};

template <typename T0, typename... Ts>
struct width_list_impl<T0, Ts...> {
  static constexpr uint32_t value = width_list_impl<T0>::value + width_list_impl<Ts...>::value;
};

template <typename... Ts>
inline constexpr uint32_t ch_width_v = width_list_impl<std::decay_t<Ts>...>::value;

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
struct is_signed_impl {
  static constexpr bool value = false;
};

template <typename T>
struct is_signed_impl<T, std::enable_if_t<is_data_type_v<T>>> {
  static constexpr bool value = T::traits::is_signed;
};

template <typename T>
struct is_signed_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  static constexpr bool value = std::is_signed_v<T>;
};

template <typename T>
inline constexpr bool is_signed_v = is_signed_impl<std::decay_t<T>>::value;

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
struct signed_type_impl {
  using type = void;
};

template <typename T>
struct signed_type_impl<T, std::enable_if_t<std::is_signed_v<T>>> {
  using type = T;
};

template <typename T>
struct signed_type_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  using type = std::make_signed_t<T>;
};


template <typename T>
struct signed_type_impl<T, std::enable_if_t<std::is_same_v<T, ch_bit<ch_width_v<T>>>>> {
  using type = ch_int<ch_width_v<T>>;
};

template <typename T>
struct signed_type_impl<T, std::enable_if_t<std::is_same_v<T, ch_uint<ch_width_v<T>>>>> {
  using type = ch_int<ch_width_v<T>>;
};

template <typename T>
struct signed_type_impl<T, std::enable_if_t<std::is_same_v<T, ch_sbit<ch_width_v<T>>>>> {
  using type = ch_sint<ch_width_v<T>>;
};

template <typename T>
struct signed_type_impl<T, std::enable_if_t<std::is_same_v<T, ch_suint<ch_width_v<T>>>>> {
  using type = ch_sint<ch_width_v<T>>;
};

template <typename T>
using ch_signed_t = typename signed_type_impl<T>::type;

///////////////////////////////////////////////////////////////////////////////

CH_DEF_SFINAE_CHECK(is_resizable, sizeof(typename T:: template size_cast<1>) != 0);

template <typename T, unsigned N, typename Enable = void>
struct size_cast_impl {
  using type = void;
};

template <typename T, unsigned N>
struct size_cast_impl<T, N, std::enable_if_t<is_resizable_v<T>>> {
  using type = typename T::template size_cast<N>;
};

template <typename T, unsigned N>
using ch_size_cast_t = typename size_cast_impl<T, N>::type;

template <typename T, typename U>
inline constexpr bool is_resize_constructible_v =
       is_strictly_constructible_v<T, U>
    || (!is_strictly_constructible_v<U, T>
     && is_resizable_v<T>
     && is_strictly_constructible_v<ch_size_cast_t<T, ch_width_v<U>>, U>);

///////////////////////////////////////////////////////////////////////////////

template <unsigned Bitwidth,
          bool Signed,
          typename SystemType,
          typename LogicType>
struct system_traits {
  static_assert(Bitwidth != 0, "invalid size");
  static constexpr int type = traits_system;
  static constexpr unsigned bitwidth  = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using system_type = SystemType;
  using logic_type  = LogicType;
};

template <typename T, typename Enable = void>
struct system_t_impl {
  using type = void;
};

template <typename T>
struct system_t_impl<T, std::enable_if_t<(is_object_type_v<T>)>> {
  using type = typename std::decay_t<T>::traits::system_type;
};

template <typename T>
struct system_t_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  using type = std::conditional_t<std::is_signed_v<T>, ch_sint<ch_width_v<T>>, ch_suint<ch_width_v<T>>>;
};

template <typename T>
using ch_system_t = typename system_t_impl<std::decay_t<T>>::type;

CH_DEF_SFINAE_CHECK(is_system_only, (T::traits::type == traits_system));

CH_DEF_SFINAE_CHECK(is_system_type, 0 != (T::traits::type & traits_system));

///////////////////////////////////////////////////////////////////////////////

template <unsigned Bitwidth,
          bool Signed,
          typename LogicType,
          typename SystemType>
struct logic_traits {
  static_assert(Bitwidth != 0, "invalid size");
  static constexpr int type = traits_logic;
  static constexpr unsigned bitwidth  = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using logic_type  = LogicType;
  using system_type = SystemType;
};

template <typename T, typename Enable = void>
struct logic_t_impl {
  using type = void;
};

template <typename T>
struct logic_t_impl<T, std::enable_if_t<is_object_type_v<T>>> {
  using type = typename std::decay_t<T>::traits::logic_type;
};

template <typename T>
struct logic_t_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  using type = std::conditional_t<std::is_signed_v<T>, ch_int<ch_width_v<T>>, ch_uint<ch_width_v<T>>>;
};

template <typename T>
using ch_logic_t = typename logic_t_impl<std::decay_t<T>>::type;

CH_DEF_SFINAE_CHECK(is_logic_only, (T::traits::type == traits_logic));

CH_DEF_SFINAE_CHECK(is_logic_type, 0 != (T::traits::type & traits_logic));

///////////////////////////////////////////////////////////////////////////////

template <unsigned Bitwidth,
          ch_direction Direction,
          typename SystemIO,
          typename FlipIO,
          typename LogicIO,
          typename LogicFlipIO,
          typename SystemType,
          typename LogicType>
struct system_io_traits {
  static_assert(Bitwidth != 0, "invalid size");
  static constexpr int type = traits_system_io;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr ch_direction direction = Direction;
  using system_io     = SystemIO;
  using flip_io       = FlipIO;
  using logic_io      = LogicIO;
  using logic_flip_io = LogicFlipIO;
  using system_type   = SystemType;
  using logic_type    = LogicType;
};

template <unsigned Bitwidth,
          ch_direction Direction,
          typename LogicIO,
          typename FlipIO,
          typename SystemIO,
          typename SystemFlipIO,
          typename SystemType,
          typename LogicType>
struct logic_io_traits {
  static_assert(Bitwidth != 0, "invalid size");
  static constexpr int type = traits_logic_io;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr ch_direction direction = Direction;
  using logic_io      = LogicIO;
  using flip_io       = FlipIO;
  using system_io     = SystemIO;
  using system_flip_io= SystemFlipIO;
  using system_type   = SystemType;
  using logic_type    = LogicType;
};

template <ch_direction Direction,
          typename SystemIO,
          typename FlipIO,
          typename LogicIO,
          typename SystemType>
struct base_system_io_traits {
  static constexpr int type = traits_system | traits_system_io;
  static constexpr unsigned bitwidth = ch_width_v<SystemType>;
  static constexpr unsigned is_signed = is_signed_v<SystemType>;
  static constexpr ch_direction direction = Direction;
  using system_io     = SystemIO;
  using flip_io       = FlipIO;
  using logic_io      = LogicIO;
  using system_type   = SystemType;
  using logic_type    = ch_logic_t<SystemType>;
};

template <ch_direction Direction,
          typename LogicIO,
          typename FlipIO,
          typename SystemIO,
          typename LogicType>
struct base_logic_io_traits {
  static constexpr int type = traits_logic | traits_logic_io;
  static constexpr unsigned bitwidth = ch_width_v<LogicType>;
  static constexpr unsigned is_signed = is_signed_v<LogicType>;
  static constexpr ch_direction direction = Direction;
  using logic_io      = LogicIO;
  using flip_io       = FlipIO;
  using system_io     = SystemIO;
  using logic_type    = LogicType;
  using system_type   = ch_system_t<LogicType>;
};

template <typename T>
using ch_logic_io = typename std::decay_t<T>::traits::logic_io;

template <typename T>
using ch_system_io = typename std::decay_t<T>::traits::system_io;

template <typename T>
using ch_flip_io = typename std::decay_t<T>::traits::flip_io;

CH_DEF_SFINAE_CHECK(is_system_io, 0 != (T::traits::type & traits_system_io));

CH_DEF_SFINAE_CHECK(is_logic_io, 0 != (T::traits::type & traits_logic_io));

//////////////////////////////////////////////////////////////////////////////

struct non_object_type {
  struct traits {
    static constexpr int type = traits_none;
    static constexpr unsigned bitwidth = 0;
    static constexpr bool is_signed = false;
  };
};

template <bool resize, typename T0, typename T1>
struct deduce_type_impl {
  using D0 = std::decay_t<T0>;
  using D1 = std::decay_t<T1>;
  using U0 = std::conditional_t<is_data_type_v<D0>, D0, non_object_type>;
  using U1 = std::conditional_t<is_data_type_v<D1>, D1, non_object_type>;
  using type = std::conditional_t<(ch_width_v<U0> != 0) && (ch_width_v<U1> != 0),
    std::conditional_t<(ch_width_v<U0> == ch_width_v<U1>) || ((ch_width_v<U0> > ch_width_v<U1>) && resize), U0,
        std::conditional_t<(ch_width_v<U0> < ch_width_v<U1>) && resize, U1, non_object_type>>,
          std::conditional_t<(ch_width_v<U0> != 0), U0, U1>>;
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
  using U0 = std::conditional_t<is_data_type_v<D0>, D0, non_object_type>;
  using U1 = std::conditional_t<is_data_type_v<D1>, D1, non_object_type>;
  using type = std::conditional_t<(ch_width_v<U0> != 0), U0, U1>;
};

template <typename T0, typename T1>
using deduce_first_type_t = typename deduce_first_type_impl<T0, T1>::type;

}
}
