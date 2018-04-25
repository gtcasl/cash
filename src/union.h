#pragma once

#include "logic.h"

namespace ch {
namespace internal {

template <typename T, typename... Fs>
struct union_init_fields_impl {};

template <typename T, typename F>
struct union_init_fields_impl<T, F> {
  static void apply(const T& value, F& field) {
    ch::internal::type_accessor_t<typename F::traits>::copy(field, value);
  }
};

template <typename T, typename F0, typename... Fs>
struct union_init_fields_impl0 {
  static void apply(const T& value, F0& field0, Fs&...) {
    ch::internal::type_accessor_t<typename F0::traits>::copy(field0, value);
  }
};

template <typename T, typename F0, typename... Fs>
struct union_init_fields_impl1 {
  static void apply(const T& value, F0&, Fs&... fields) {
    union_init_fields_impl<T, Fs...>::apply(value, fields...);
  }
};

template <typename T, typename F0, typename... Fs>
struct union_init_fields_impl<T, F0, Fs...> {
  static void apply(const T& value, F0& field0, Fs&... fields) {
    std::conditional_t<is_cast_convertible<F0, T>::value,
                       union_init_fields_impl0<T, F0, Fs...>,
                       union_init_fields_impl1<T, F0, Fs...>>::apply(value, field0, fields...);
  }
};

struct union_init_fields {
  template <typename T, typename... Fs>
  static void apply(const T& value, Fs&... fields) {
    union_init_fields_impl<T, Fs...>::apply(value, fields...);
  }
};

template <typename T>
struct union_zero_init_impl0 {
  static void apply(T&) {};
};

template <typename T, typename U>
struct union_zero_init_impl1 {
  static void apply(T& obj) {
    if constexpr(is_logic_traits<typename T::traits>::value && width_v<U> < T::traits::bitwidth) {
      obj.as_bit() = 0;
    }
  };
};

template <typename T, typename U>
using union_zero_init = std::conditional_t<has_bitwidth<U>::value,
                                           union_zero_init_impl1<T, U>,
                                           union_zero_init_impl0<T>>;
}
}

#define CH_UNION_SIZE_EACH(i, x) \
  ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_UNION_SIZE(...) \
  std::max({CH_FOR_EACH(CH_UNION_SIZE_EACH, CH_SEP_COMMA, __VA_ARGS__)})

#define CH_UNION_SCALAR_CTOR(i, x) \
  CH_PAIR_R(x)(std::make_shared<ch::internal::type_buffer_t<traits>>( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0))

#define CH_UNION_LOGIC_CTOR(i, x) \
  CH_PAIR_R(x)(std::make_shared<ch::internal::type_buffer_t<traits>>( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0, \
    CH_STRINGIZE(CH_PAIR_R(x))))

#define CH_UNION_MOVE_CTOR(i, x) \
  CH_PAIR_R(x)(std::move(rhs.CH_PAIR_R(x)))

#define CH_UNION_GETBUFFER(i, x) \
  return ch::internal::type_accessor_t<traits>::buffer(CH_PAIR_R(x))

#define CH_UNION_SCALAR_FIELD(i, x) \
  ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_LOGIC_FIELD(i, x) \
  ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_SCALAR_FIELD_CTOR_REQUIRES(i, x) \
  ch::internal::is_cast_convertible<decltype(CH_PAIR_R(x)), __T__>::value

#define CH_UNION_FIELD_CTOR_REQUIRES(i, x) \
  ch::internal::is_cast_convertible<decltype(CH_PAIR_R(x)), __T__>::value

#define CH_UNION_INIT_FIELD(i, x) \
  CH_PAIR_R(x)

#define CH_UNION_SCALAR_IMPL(union_name, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  union_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth)) \
    : CH_FOR_EACH(CH_UNION_SCALAR_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& rhs) \
    : union_name(ch::internal::type_accessor_t<traits>::copy_buffer(rhs)) {} \
  union_name(union_name&& rhs) \
    : CH_FOR_EACH(CH_UNION_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit union_name(const ch_scalar<traits::bitwidth>& rhs) \
    : union_name(std::make_shared<ch::internal::type_buffer_t<traits>>(ch::internal::scalar_accessor::data(rhs))) {} \
  template <typename __T__, \
             CH_REQUIRE_0(std::is_integral_v<__T__> || std::is_enum_v<__T__> || ch::internal::has_bitwidth<__T__>::value), \
             CH_REQUIRE_0(CH_FOR_EACH(CH_UNION_FIELD_CTOR_REQUIRES, CH_SEP_OR, __VA_ARGS__))> \
  explicit union_name(const __T__& rhs) : union_name() { \
    this->init_fields(rhs); \
  } \
protected: \
  template <typename __T__> \
  void init_fields(const __T__& rhs) { \
    ch::internal::union_zero_init<union_name, __T__>::apply(*this); \
    ch::internal::union_init_fields::apply( \
      static_cast<ch::internal::aggregate_init_cast_t<union_name, __T__>>(rhs), \
      CH_FOR_EACH(CH_UNION_INIT_FIELD, CH_SEP_COMMA, __VA_ARGS__)); \
  } \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  } \
  std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  } \
public:

#define CH_UNION_LOGIC_IMPL(union_name, name, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  union_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, CH_SRC_LOCATION, CH_STRINGIZE(name))) \
    : CH_FOR_EACH(CH_UNION_LOGIC_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& rhs, const source_location& sloc = CH_SRC_LOCATION) \
    : union_name(ch::internal::type_accessor_t<traits>::copy_buffer(rhs, sloc, CH_STRINGIZE(name))) {} \
  union_name(union_name&& rhs) \
    : CH_FOR_EACH(CH_UNION_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit union_name(const ch_bit<traits::bitwidth>& rhs, \
                      const source_location& sloc = CH_SRC_LOCATION) \
    : union_name(ch::internal::type_accessor_t<traits>::copy_buffer(rhs, sloc, CH_STRINGIZE(name))) {} \
  explicit union_name(const ch_scalar<traits::bitwidth>& rhs, \
                      const source_location& sloc = CH_SRC_LOCATION) \
    : union_name(std::make_shared<ch::internal::type_buffer_t<traits>>( \
        ch::internal::scalar_accessor::data(rhs), sloc, CH_STRINGIZE(name))) {} \
  template <typename __T__, \
             CH_REQUIRE_0(std::is_integral_v<__T__> || std::is_enum_v<__T__> || ch::internal::has_bitwidth<__T__>::value), \
             CH_REQUIRE_0(CH_FOR_EACH(CH_UNION_FIELD_CTOR_REQUIRES, CH_SEP_OR, __VA_ARGS__))> \
  explicit union_name(const __T__& rhs, \
                      const source_location& sloc = CH_SRC_LOCATION) \
    : union_name(std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, sloc, CH_STRINGIZE(name))) { \
    this->init_fields(rhs); \
  } \
protected: \
  template <typename __T__> \
  void init_fields(const __T__& rhs) { \
    ch::internal::union_zero_init<union_name, __T__>::apply(*this); \
    ch::internal::union_init_fields::apply( \
      static_cast<ch::internal::aggregate_init_cast_t<union_name, __T__>>(rhs), \
      CH_FOR_EACH(CH_UNION_INIT_FIELD, CH_SEP_COMMA, __VA_ARGS__)); \
  } \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  } \
  std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  }

#define CH_UNION_ASSIGN_IMPL(union_name) \
public: \
  union_name& operator=(const union_name& rhs) { \
    ch::internal::type_accessor_t<traits>::copy(*this, rhs); \
    return *this; \
  } \
  union_name& operator=(union_name&& rhs) { \
    ch::internal::type_accessor_t<traits>::move(*this, std::move(rhs)); \
    return *this; \
  }

#define CH_UNION_SCALAR_FRIENDS_IMPL(enum_name) \
protected: \
  friend class ch::internal::scalar_accessor;

#define CH_UNION_LOGIC_FRIENDS_IMPL(enum_name) \
protected: \
  friend class ch::internal::logic_accessor;

#define CH_UNION_IMPL(union_name, ...) \
  class union_name { \
  private: \
    class __scalar_type__ { \
    public: \
      using traits = ch::internal::scalar_traits<CH_UNION_SIZE(__VA_ARGS__), false, __scalar_type__, union_name>; \
      CH_UNION_SCALAR_IMPL(__scalar_type__, CH_UNION_SCALAR_FIELD, __VA_ARGS__) \
      CH_UNION_ASSIGN_IMPL(__scalar_type__) \
      CH_SCALAR_INTERFACE(__scalar_type__) \
      CH_UNION_SCALAR_FRIENDS_IMPL(__scalar_type__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<CH_UNION_SIZE(__VA_ARGS__), false, union_name, __scalar_type__>; \
    CH_UNION_LOGIC_IMPL(union_name, union_name, CH_UNION_LOGIC_FIELD, __VA_ARGS__) \
    CH_UNION_ASSIGN_IMPL(union_name) \
    CH_LOGIC_INTERFACE(union_name) \
    CH_UNION_LOGIC_FRIENDS_IMPL(union_name) \
  }

#define CH_UNION(name, body) \
  CH_UNION_IMPL(name, CH_REM body)
