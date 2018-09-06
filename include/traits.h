#pragma once

namespace ch {
namespace internal {

enum traits_type {
  traits_none      = 0x00,
  traits_logic     = 0x01,
  traits_system    = 0x02,
  traits_logic_io  = 0x04,
  traits_system_io = 0x08,
  traits_udf       = 0x10,
};

inline constexpr auto operator|(traits_type lsh, traits_type rhs) {
  return traits_type((int)lsh | (int)rhs);
}

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

CH_DEF_SFINAE_CHECK(is_object_type, (T::traits::type & (traits_logic | traits_system)));

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
struct width_value_impl {
  static constexpr uint32_t value = 0;
};

template <typename T>
struct width_value_impl<T, std::enable_if_t<std::is_arithmetic_v<T>>> {
  static constexpr uint32_t value = bitwidth_v<T>;
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
inline constexpr uint32_t ch_width_v = width_impl<std::decay_t<Ts>...>::value;

///////////////////////////////////////////////////////////////////////////////

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
inline constexpr bool ch_signed_v = signed_impl<std::decay_t<T>>::value;

///////////////////////////////////////////////////////////////////////////////

template <unsigned Bitwidth, bool Signed, typename SystemType, typename LogicType>
struct system_traits {
  static constexpr traits_type type  = traits_system;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using system_type = SystemType;
  using logic_type  = LogicType;
};

template <typename T>
using ch_system_t = typename std::decay_t<T>::traits::system_type;

template <typename T>
inline constexpr bool is_system_traits_v = bool_constant_v<(T::type & traits_system)>;

CH_DEF_SFINAE_CHECK(is_system_only, bool_constant_v<(std::decay_t<T>::traits::type == traits_system)>);

CH_DEF_SFINAE_CHECK(is_system_type, is_system_traits_v<typename std::decay_t<T>::traits>);

///////////////////////////////////////////////////////////////////////////////

template <unsigned Bitwidth, bool Signed, typename LogicType, typename SystemType>
struct logic_traits {
  static constexpr traits_type type = traits_logic;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using logic_type  = LogicType;
  using system_type = SystemType;
};

template <typename T>
using ch_logic_t = typename std::decay_t<T>::traits::logic_type;

template <typename T>
inline constexpr bool is_logic_traits_v = bool_constant_v<(T::type & traits_logic)>;

CH_DEF_SFINAE_CHECK(is_logic_only, bool_constant_v<(std::decay_t<T>::traits::type == traits_logic)>);

CH_DEF_SFINAE_CHECK(is_logic_type, is_logic_traits_v<typename std::decay_t<T>::traits>);

///////////////////////////////////////////////////////////////////////////////

template <unsigned Bitwidth,
          ch_direction Direction,
          typename SystemIO,
          typename FlipIO,
          typename LogicIO>
struct system_io_traits {
  static constexpr traits_type type  = traits_system_io;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr ch_direction direction = Direction;
  using system_io = SystemIO;
  using flip_io   = FlipIO;
  using logic_io  = LogicIO;
};

template <unsigned Bitwidth,
          ch_direction Direction,
          typename LogicIO,
          typename FlipIO,
          typename SystemIO>
struct logic_io_traits {
  static constexpr traits_type type  = traits_logic_io;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr ch_direction direction = Direction;
  using logic_io  = LogicIO;
  using flip_io   = FlipIO;
  using system_io = SystemIO;
};

template <ch_direction Direction,
          typename SystemIO,
          typename FlipIO,
          typename LogicIO,
          typename SystemType>
struct mixed_system_io_traits {
  static constexpr traits_type type = traits_system_io | traits_system;
  static constexpr unsigned bitwidth = ch_width_v<SystemType>;
  static constexpr unsigned is_signed = ch_signed_v<SystemType>;
  static constexpr ch_direction direction = Direction;
  using system_io   = SystemIO;
  using flip_io     = FlipIO;
  using logic_io    = LogicIO;
  using system_type = SystemType;
  using logic_type  = ch_logic_t<SystemType>;
};

template <ch_direction Direction,
          typename LogicIO,
          typename FlipIO,
          typename SystemIO,
          typename LogicType>
struct mixed_logic_io_traits {
  static constexpr traits_type type = traits_logic_io | traits_logic;
  static constexpr unsigned bitwidth = ch_width_v<LogicType>;
  static constexpr unsigned is_signed = ch_signed_v<LogicType>;
  static constexpr ch_direction direction = Direction;
  using logic_io    = LogicIO;
  using flip_io     = FlipIO;
  using system_io   = SystemIO;
  using logic_type  = LogicType;
  using system_type = ch_system_t<LogicType>;
};

template <typename T>
using ch_logic_io = typename std::decay_t<T>::traits::logic_io;

template <typename T>
using ch_system_io = typename std::decay_t<T>::traits::system_io;

template <typename T>
using ch_flip_io = typename std::decay_t<T>::traits::flip_io;

template <typename T>
inline constexpr bool is_system_io_traits_v = bool_constant_v<(T::type & traits_system_io)>;

template <typename T>
inline constexpr bool is_logic_io_traits_v = bool_constant_v<(T::type & traits_logic_io)>;

template <typename T>
inline constexpr bool is_io_traits_v = bool_constant_v<(T::type & (traits_system_io | traits_logic_io))>;

CH_DEF_SFINAE_CHECK(is_system_io, is_system_io_traits_v<typename std::decay_t<T>::traits>);

CH_DEF_SFINAE_CHECK(is_logic_io, is_logic_io_traits_v<typename std::decay_t<T>::traits>);

CH_DEF_SFINAE_CHECK(is_io, is_io_traits_v<typename std::decay_t<T>::traits>);

///////////////////////////////////////////////////////////////////////////////

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
  using type = std::conditional_t<(ch_width_v<U0> != 0) && (ch_width_v<U1> != 0),
    std::conditional_t<(ch_width_v<U0> == ch_width_v<U1>) || ((ch_width_v<U0> > ch_width_v<U1>) && resize), U0,
        std::conditional_t<(ch_width_v<U0> < ch_width_v<U1>) && resize, U1, non_ch_type>>,
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
  using U0 = std::conditional_t<is_object_type_v<D0>, D0, non_ch_type>;
  using U1 = std::conditional_t<is_object_type_v<D1>, D1, non_ch_type>;
  using type = std::conditional_t<(ch_width_v<U0> != 0), U0, U1>;
};

template <typename T0, typename T1>
using deduce_first_type_t = typename deduce_first_type_impl<T0, T1>::type;

}
}
