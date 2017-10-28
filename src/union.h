#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <typename T, typename... Fs>
struct union_init_fields_impl {};

template <typename T, typename F>
struct union_init_fields_impl<T, F> {
  static void apply(const T& value, F& field) {
    field = value;
  }
};

template <typename T, typename F0, typename... Fs>
struct union_init_fields_impl0 {
  static void apply(const T& value, F0& field0, Fs&... fields) {
    field0 = value;
  }
};

template <typename T, typename F0, typename... Fs>
struct union_init_fields_impl1 {
  static void apply(const T& value, F0& field0, Fs&... fields) {
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

template <typename U, typename T>
using union_init_cast_t = std::conditional_t<has_bitwidth<T>::value, const T&, U>;

template <typename T>
struct union_zero_init_impl0 {
  static void apply(T& obj) {};
};

template <typename T, typename U>
struct union_zero_init_impl1 {
  static void apply(T& obj) {
    if constexpr(bitwidth_v<U> < T::traits::bitwidth) {
      obj.asBits() = 0;
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
  ch_bitwidth_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_UNION_SIZE(...) \
  std::max({CH_FOR_EACH(CH_UNION_SIZE_EACH, CH_SEP_COMMA, __VA_ARGS__)})

#define CH_UNION_SCALAR_DEFAULT_CTOR(i, x) \
  CH_PAIR_R(x)(ch::internal::scalar_buffer(ch_bitwidth_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0))

#define CH_UNION_DEFAULT_CTOR(i, x) \
  CH_PAIR_R(x)(ch::internal::bit_buffer(ch_bitwidth_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0))

#define CH_UNION_MOVE_CTOR(i, x) \
  CH_PAIR_R(x)(std::move(rhs.CH_PAIR_R(x)))

#define CH_UNION_SCALAR_GETBUFFER(i, x) \
  return ch::internal::scalar_accessor::get_buffer(CH_PAIR_R(x))

#define CH_UNION_GETBUFFER(i, x) \
  return ch::internal::bit_accessor::get_buffer(CH_PAIR_R(x))

#define CH_UNION_SCALAR_FIELD(i, x) \
  ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_FIELD(i, x) \
  ch_value_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_CONST_FIELD(i, x) \
  ch_const_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_SCALAR_FIELD_CTOR_REQUIRES(i, x) \
  ch::internal::is_cast_convertible<ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>>, __T__>::value

#define CH_UNION_FIELD_CTOR_REQUIRES(i, x) \
  ch::internal::is_cast_convertible<ch_value_t<ch::internal::identity_t<CH_PAIR_L(x)>>, __T__>::value

#define CH_UNION_INIT_FIELD(i, x) \
  CH_PAIR_R(x)

#define CH_UNION_SCALAR_IMPL(union_name, value_name, ...) \
  class union_name { \
  public: \
    using traits = ch::internal::scalar_traits<CH_UNION_SIZE(__VA_ARGS__), union_name, value_name>; \
  public: \
    CH_FOR_EACH(CH_UNION_SCALAR_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    union_name(const ch::internal::scalar_buffer& buffer = ch::internal::scalar_buffer(traits::bitwidth)) \
      : CH_FOR_EACH(CH_UNION_SCALAR_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    union_name(const union_name& rhs) \
      : union_name(ch::internal::scalar_accessor::cloneBuffer(rhs)) {} \
    union_name(union_name&& rhs) \
      : CH_FOR_EACH(CH_UNION_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    explicit union_name(const ch_scalar<traits::bitwidth>& rhs) \
      : union_name(ch::internal::scalar_accessor::cloneBuffer(rhs)) {} \
    template <typename __T__, \
              CH_REQUIRES(CH_FOR_EACH(CH_UNION_FIELD_CTOR_REQUIRES, CH_SEP_OR, __VA_ARGS__))> \
    explicit union_name(const __T__& rhs) : union_name() { \
      this->init_fields(rhs); \
    } \
    union_name& operator=(const union_name& rhs) { \
      ch::internal::scalar_accessor::copy(*this, rhs); \
      return *this; \
    } \
    union_name& operator=(union_name&& rhs) { \
      ch::internal::scalar_accessor::move(*this, std::move(rhs)); \
      return *this; \
    } \
    CH_SCALAR_READONLY_INTERFACE(union_name) \
    CH_SCALAR_WRITABLE_INTERFACE(union_name) \
  protected: \
    template <typename __T__, \
              CH_REQUIRES(CH_FOR_EACH(CH_UNION_SCALAR_FIELD_CTOR_REQUIRES, CH_SEP_OR, __VA_ARGS__))> \
    void init_fields(const __T__& rhs) { \
      ch::internal::union_init_fields::apply( \
        static_cast<ch::internal::union_init_cast_t<ch_scalar<traits::bitwidth>, __T__>>(rhs), \
        CH_FOR_EACH(CH_UNION_INIT_FIELD, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
    const ch::internal::scalar_buffer_ptr& get_buffer() const { \
      CH_FOR_EACH_1(0, CH_UNION_SCALAR_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__)->get_source(); \
    } \
    ch::internal::scalar_buffer_ptr& get_buffer() { \
      CH_FOR_EACH_1(0, CH_UNION_SCALAR_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__)->get_source(); \
    } \
    friend class ch::internal::scalar_accessor; \
  }

#define CH_UNION_BODY_IMPL(union_name, reverse_name, assignment_body, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  union_name(const ch::internal::bit_buffer& buffer = ch::internal::bit_buffer(traits::bitwidth)) \
    : CH_FOR_EACH(CH_UNION_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& rhs) \
    : union_name(ch::internal::bit_accessor::cloneBuffer(rhs)) {} \
  union_name(union_name&& rhs) \
    : CH_FOR_EACH(CH_UNION_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const reverse_name& rhs) \
    : union_name(ch::internal::bit_accessor::cloneBuffer(rhs)) {} \
  explicit union_name(const ch_scalar<traits::bitwidth>& rhs) \
    : union_name(ch::internal::bit_buffer(ch::internal::scalar_accessor::get_data(rhs))) {} \
  template <typename __T__, \
            CH_REQUIRES(CH_FOR_EACH(CH_UNION_FIELD_CTOR_REQUIRES, CH_SEP_OR, __VA_ARGS__))> \
  explicit union_name(const __T__& rhs) : union_name() { \
    this->init_fields(rhs); \
  } \
  assignment_body(union_name, __VA_ARGS__) \
protected: \
  template <typename __T__, \
            CH_REQUIRES(CH_FOR_EACH(CH_UNION_FIELD_CTOR_REQUIRES, CH_SEP_OR, __VA_ARGS__))> \
  void init_fields(const __T__& rhs) { \
    ch::internal::union_zero_init<union_name, __T__>::apply(*this); \
    ch::internal::union_init_fields::apply( \
      static_cast<ch::internal::union_init_cast_t<ch_bit<traits::bitwidth>, __T__>>(rhs), \
      CH_FOR_EACH(CH_UNION_INIT_FIELD, CH_SEP_COMMA, __VA_ARGS__)); \
  } \
  const ch::internal::bit_buffer_ptr& get_buffer() const { \
    CH_FOR_EACH_1(0, CH_UNION_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__)->get_source(); \
  } \
  ch::internal::bit_buffer_ptr& get_buffer() { \
    CH_FOR_EACH_1(0, CH_UNION_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__)->get_source(); \
  } \
  friend class ch::internal::bit_accessor; \

#define CH_UNION_READONLY_IMPL(union_name, ...) \
  CH_BIT_READONLY_INTERFACE(union_name)

#define CH_UNION_WRITABLE_IMPL(union_name, ...) \
  CH_BIT_READONLY_INTERFACE(union_name) \
  CH_BIT_WRITABLE_INTERFACE(union_name) \
  union_name& operator=(const union_name& rhs) { \
    ch::internal::bit_accessor::copy(*this, rhs); \
    return *this; \
  } \
  union_name& operator=(union_name&& rhs) { \
    ch::internal::bit_accessor::move(*this, std::move(rhs)); \
    return *this; \
  } \
  union_name& operator=(const __const_type__& rhs) { \
    ch::internal::bit_accessor::copy(*this, rhs); \
    return *this; \
  }

#define CH_UNION_IMPL(union_name, ...) \
  class union_name { \
  protected: \
    CH_UNION_SCALAR_IMPL(__scalar_type__, union_name, __VA_ARGS__); \
    class __const_type__ { \
    public: \
      using traits = ch::internal::logic_traits<CH_UNION_SIZE(__VA_ARGS__), __const_type__, __const_type__, union_name, __scalar_type__>; \
      CH_UNION_BODY_IMPL(__const_type__, union_name, CH_UNION_READONLY_IMPL, CH_UNION_CONST_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<CH_UNION_SIZE(__VA_ARGS__), union_name, __const_type__, union_name, __scalar_type__>; \
    CH_UNION_BODY_IMPL(union_name, __const_type__, CH_UNION_WRITABLE_IMPL, CH_UNION_FIELD, __VA_ARGS__) \
  }

#define CH_UNION(name, body) \
  CH_UNION_IMPL(name, CH_REM body)
