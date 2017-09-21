#pragma once

#include "struct.h"

namespace cash {
namespace internal {

lnodeimpl* createInputNode(const snode& in);

snodeimpl* createOutputNode(const lnode& out);

template <typename T, unsigned N = T::bitcount,
          CH_REQUIRES(is_bus_convertible<T>::value)>
auto ch_input(const T& in) {
  return make_bit<N>(createInputNode(get_snode<T, N>(in)));
}

template <typename T, unsigned N = T::bitcount,
          CH_REQUIRES(is_bit_convertible<T>::value)>
auto ch_output(const T& out) {
  return make_bus<N>(createOutputNode(get_lnode<T, N>(out)));
}

template <bool input, bool output>
class ch_port {
public:
  //--

protected:
  //--
};

template <typename T>
class ch_in;

template <typename T>
class ch_out;

template <typename T>
class ch_in : public T::const_type, public ch_port<true, false> {
public:
  using base = typename T::const_type;
  using value_type = T;
  using const_type = typename T::const_type;
  using flip_type = ch_out<T>;

  ch_in() {}
  ch_in(const ch_in& in) : base(in) {}
  ch_in(ch_in&& in) : base(std::move(in)) {}

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

  void operator()(const ch_busbase<T::bitcount>& value) {
    this->assign(ch_input(value));
  }

protected:

  ch_in& operator=(const ch_in&) = delete;
  ch_in& operator=(ch_in&&) = delete;
};

template <typename T>
class ch_out : public T, public ch_port<false, true> {
public:
  using base = T;
  using base::operator=;
  using value_type = T;
  using const_type = typename T::const_type;
  using flip_type = ch_in<T>;

  ch_out() {}
  ch_out(const ch_out& out) : base(out) {}
  ch_out(ch_out&& out) : base(std::move(out)) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const ch_out<U>& out) {
    base::operator=(out);
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(ch_in<U>& in) {
    in(*this);
  }

  template <typename U,
            CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(U& value) {
    value = *this;
  }

  void operator()(ch_bus<T::bitcount>& value) {
    value = ch_output(*this);
  }

protected:

  ch_out& operator=(const ch_out&) = delete;
  ch_out& operator=(ch_out&&) = delete;

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
  class name : public cash::internal::ch_port<true, true> { \
  private: \
    CH_STRUCT_IMPL(__value_type__, __VA_ARGS__); \
    class __flip_type__ : public cash::internal::ch_port<true, true> { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      static constexpr unsigned bitcount = __value_type__::bitcount; \
      using base = cash::internal::ch_port<true, true>; \
      using value_type = __value_type__; \
      using const_type = __value_type__::const_type; \
      using flip_type = name; \
      __flip_type__() {} \
      __flip_type__(const __flip_type__& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      __flip_type__(__flip_type__&& __rhs__) : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      void operator()(__flip_type__& __rhs__) { \
        CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      void operator()(value_type& __rhs__) { \
        CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__)> \
      void operator()(CH_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) { \
        CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
      } \
      CH_FOR_EACH(CH_INOUT_FLIP_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    }; \
    name& operator=(const name&) = delete; \
  public: \
    static constexpr unsigned bitcount = __value_type__::bitcount; \
    using base = cash::internal::ch_port<true, true>; \
    using value_type = __value_type__; \
    using const_type = __value_type__::const_type; \
    using bus_type = value_type::bus_type; \
    using flip_type  = __flip_type__; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(name&& __rhs__) : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    void operator()(name& __rhs__) { \
      CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void operator()(value_type& __rhs__) { \
      CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__)> \
    void operator()(CH_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) { \
      CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    CH_FOR_EACH(CH_INOUT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  }

#define CH_INOUT(name, body) \
  CH_INOUT_IMPL(name, CH_REM body)

#define CH_IO(...) \
  CH_INOUT_IMPL(io_t, __VA_ARGS__); \
  io_t io

}
}
