#pragma once

#include "struct.h"

namespace cash {
namespace internal {

template <typename T>
class ch_port {
public:
  static const unsigned bitcount = T::bitcount;
  using value_type = T;

private:
  //--
};

template <typename T>
class ch_out;

template <typename T>
class ch_in : public ch_port<T> {
public:
  static_assert(std::is_base_of<ch_bitbase<T::bitcount>, T>::value, "invalid object type");
  using base = ch_port<T>;
  using value_type = T;
  using flip_type = ch_out<T>;

  ch_in() {}
  ch_in(const ch_in& in) : value_(in.value_) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  explicit ch_in(const U& value) : value_(value) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_in<U>& in) {
    value_ = in.value_;
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_out<U>& out) {
    value_ = out.value_;
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const U& value) {
    value_ = value;
  }

  const T& operator*() const {
    return value_;
  }

  const T* operator->() const {
    return &value_;
  }

private:
  ch_in& operator=(const ch_in&) = delete;
  T value_;
};

template <typename T>
class ch_out : public ch_port<T> {
public:
  static_assert(std::is_base_of<ch_bitbase<T::bitcount>, T>::value, "invalid object type");
  using base = ch_port<T>;
  using value_type = T;
  using flip_type = ch_in<T>;

  ch_out() {}
  ch_out(const ch_out& out) : value_(out.value_) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_out<U>& out) {
    value_ = out.value_;
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(ch_in<U>& in) {
    in(value_);
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(U& value) {
    value = value_;
  }

  void operator()(T& value) {
    value = value_;
  }

  T& operator*() {
    return value_;
  }

  T* operator->() {
    return &value_;
  }

private:
  ch_out& operator=(const ch_out&) = delete;
  T value_;

  template <typename U> friend class ch_in;
};

#define CH_INOUT_FIELD(i, x) \
  CH_PAIR_L(x) CH_PAIR_R(x)

#define CH_INOUT_FLIP_FIELD(i, x) \
  CH_PAIR_L(x)::flip_type CH_PAIR_R(x)

#define CH_INOUT_BIND_APPLY(i, x) \
  this->CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_ARGS(i, x) \
  __T##i&& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_APPLY(i, x) \
  this->CH_PAIR_R(x)(std::forward<__T##i>(CH_CONCAT(_,CH_PAIR_R(x))))

#define CH_INOUT_IMPL(name, ...) \
  class name : public cash::internal::ch_port<name> { \
  private: \
    CH_STRUCT_IMPL(__value_type__, __VA_ARGS__) }; \
    class __flip_type__ : public cash::internal::ch_port<__flip_type__> { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      using base = cash::internal::ch_port<__flip_type__>; \
      static const unsigned bitcount = __value_type__::bitcount; \
      using value_type = __value_type__; \
      using flip_type = name; \
      __flip_type__() {} \
      __flip_type__(const __flip_type__& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      void operator()(__flip_type__& __rhs__) { \
        CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      void operator()(value_type& __rhs__) { \
        CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__)> \
      void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) { \
        CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      CH_FOR_EACH(CH_INOUT_FLIP_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    }; \
    name& operator=(const name&) = delete; \
  public: \
    using base = cash::internal::ch_port<name>; \
    static const unsigned bitcount = __value_type__::bitcount; \
    using value_type = __value_type__; \
    using flip_type  = __flip_type__; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    void operator()(name& __rhs__) { \
      CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void operator()(value_type& __rhs__) { \
      CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__)> \
    void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) { \
      CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    CH_FOR_EACH(CH_INOUT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  public:

#define CH_INOUT(name, body, ...) CH_INOUT_IMPL(name, CH_REM body) __VA_ARGS__ }

#define CH_IO(...) \
  CH_INOUT_IMPL(io_type, __VA_ARGS__) }; \
  io_type io

}
}
