#pragma once

#include "struct.h"

namespace cash {
namespace internal {

lnodeimpl* createInputNode(const snode& in);

snodeimpl* createOutputNode(const lnode& out);

template <typename T, unsigned N = T::bitcount>
auto ch_input(const T& in) {
  return make_bit<N>(createInputNode(get_snode<T, N>(in)));
}

template <typename T, unsigned N = T::bitcount>
auto ch_output(const T& out) {
  return make_bus<N>(createOutputNode(get_lnode<T, N>(out)));
}

template <typename T>
class ch_port : public T {
public:
  ~ch_port() {}

protected:
  ch_port() {}
  ch_port(const ch_port& p) : T(p) {}
};

template <typename T>
class ch_in;

template <typename T>
class ch_out;

template <typename T>
class ch_in : public ch_port<typename T::const_t> {
public:
  using base = ch_port<T>;
  using value_t = T;
  using flip_type = ch_out<T>;

  ch_in() {}
  ch_in(const ch_in& in) : base(in) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_in<U>& in) {
    this->assign(in);
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_out<U>& out) {
    this->assign(out);
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const U& value) {
    this->assign(value);
  }

  template <typename U,
            CH_REQUIRES(U::bitcount == T::bitcount)>
  void operator()(const ch_busbase<U>& value) {
    this->assign(ch_input(value));
  }
};

template <typename T>
class ch_out : public ch_port<T> {
public:
  using base = ch_port<T>;
  using value_t = T;
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

  void operator()(ch_bus<T::bitcount>& value) {
    value = ch_output(value_);
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
      using value_t = __value_type__; \
      using flip_type = name; \
      __flip_type__() {} \
      __flip_type__(const __flip_type__& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      void operator()(__flip_type__& __rhs__) { \
        CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      void operator()(value_t& __rhs__) { \
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
    using value_t = __value_type__; \
    using flip_type  = __flip_type__; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    void operator()(name& __rhs__) { \
      CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void operator()(value_t& __rhs__) { \
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
