#pragma once

#include "port.h"

#define CH_INOUT_DIRECTION_EACH(i, x) \
  (int)ch::internal::identity_t<CH_PAIR_L(x)>::traits::direction

#define CH_INOUT_DIRECTION(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_DIRECTION_EACH, CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_FLIP_DIRECTION_EACH(i, x) \
  (int)ch_flip_t<ch::internal::identity_t<CH_PAIR_L(x)>>::traits::direction

#define CH_INOUT_FLIP_DIRECTION(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_FLIP_DIRECTION_EACH, CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_FIELD(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)> CH_PAIR_R(x)

#define CH_INOUT_FLIP_FIELD(i, x) \
  ch_flip_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_INOUT_BIND_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::traits::port_type CH_PAIR_R(x)

#define CH_INOUT_FLIP_BIND_FIELD(i, x) \
  typename ch_flip_t<ch::internal::identity_t<CH_PAIR_L(x)>>::traits::port_type CH_PAIR_R(x)

#define CH_INOUT_COPY_CTOR(i, x) \
  CH_PAIR_R(x)(rhs.CH_PAIR_R(x))

#define CH_INOUT_CTOR_BODY(i, x) \
  CH_PAIR_R(x)(ch::internal::fstring("%s_%s", name.c_str(), CH_STRINGIZE(CH_PAIR_R(x))).c_str())

#define CH_INOUT_BIND_BODY(i, x) \
  this->CH_PAIR_R(x)(rhs.CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_ARGS(i, x) \
  __T##i&& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_BODY(i, x) \
  this->CH_PAIR_R(x)(std::forward<__T##i>(CH_CONCAT(_,CH_PAIR_R(x))))

#define CH_INOUT_FIELD_BIND_REQUIRES(i, x) \
  CH_REQUIRES(!std::is_same<std::decay_t<__T##i>, __self_type__>::value \
           && !std::is_same<std::decay_t<__T##i>, __port_type__>::value \
           && !std::is_same<std::decay_t<__T##i>, __flip_port_type__>::value)

#define CH_INOUT_BODY_IMPL2(inout_name, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  inout_name(const std::string& name = "io") \
    : CH_FOR_EACH(CH_INOUT_CTOR_BODY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& rhs) \
    : CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& rhs) \
    : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {}

#define CH_INOUT_BIND_IMPL2(field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  void operator()(const __self_type__& rhs) const { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __port_type__& rhs) const { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __flip_port_type__& rhs) const { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_REVERSE_FOR_EACH(CH_INOUT_FIELD_BIND_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) const { \
    CH_FOR_EACH(CH_INOUT_BIND_FIELD_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  }

#define CH_INOUT_BODY_IMPL3(inout_name, parent, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  inout_name(const std::string& name = "io") \
    : parent(name) \
    , CH_FOR_EACH(CH_INOUT_CTOR_BODY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& rhs) \
    : parent(rhs) \
    , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& rhs) \
    : parent(std::move(rhs)) \
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {}

#define CH_INOUT_BIND_IMPL3(parent, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  void operator()(const __self_type__& rhs) const { \
    parent::operator()(rhs); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __port_type__& rhs) const { \
    parent::operator()(rhs); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __flip_port_type__& rhs) const { \
    parent::operator()(rhs); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), typename... __Ts__, \
            CH_REVERSE_FOR_EACH(CH_INOUT_FIELD_BIND_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__), __Ts__&&... args) const { \
    parent::operator()(args...); \
    CH_FOR_EACH(CH_INOUT_BIND_FIELD_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  }

#define CH_INOUT_IMPL2(inout_name, ...) \
  class inout_name { \
  private: \
    CH_STRUCT_IMPL2(__value_type__, __VA_ARGS__); \
    class __flop_port_type__; \
    class __flip_type__ { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      CH_INOUT_BODY_IMPL2(__flip_type__, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    private: \
      class __port_type__ { \
      public: \
        using __self_type__ = __flip_type__; \
        using __flip_port_type__ = __flop_port_type__; \
        __port_type__(__flip_type__& rhs) \
          : CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
        CH_INOUT_BIND_IMPL2(CH_INOUT_FLIP_BIND_FIELD, __VA_ARGS__) \
      }; \
    public: \
      using traits = ch::internal::io_traits<__flip_type__, CH_INOUT_FLIP_DIRECTION(__VA_ARGS__), inout_name, __port_type__, __value_type__>; \
    }; \
    inout_name& operator=(const inout_name&) = delete; \
  public: \
    CH_INOUT_BODY_IMPL2(inout_name, CH_INOUT_FIELD, __VA_ARGS__) \
  private: \
    class __flop_port_type__ { \
    public: \
      using __port_type__ = __flop_port_type__; \
      using __self_type__ = inout_name; \
      using __flip_port_type__ = typename __flip_type__::traits::port_type; \
      __flop_port_type__(inout_name& rhs) \
        : CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BIND_IMPL2(CH_INOUT_BIND_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::io_traits<inout_name, CH_INOUT_DIRECTION(__VA_ARGS__), __flip_type__, __flop_port_type__, __value_type__>; \
  }

#define CH_INOUT_IMPL3(inout_name, parent, ...) \
  class inout_name : public parent { \
  private: \
    CH_STRUCT_IMPL3(__value_type__, parent, __VA_ARGS__); \
    class __flop_port_type__; \
    class __flip_type__ : public ch_flip_t<parent> { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      CH_INOUT_BODY_IMPL3(__flip_type__, ch_flip_t<parent>, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    private: \
      class __port_type__ : public ch_flip_t<parent>::traits::port_type { \
      public: \
        using __self_type__ = __flip_type__; \
        using __flip_port_type__ = __flop_port_type__; \
        __port_type__(__flip_type__& rhs) \
          : ch_flip_t<parent>::traits::port_type(rhs) \
          , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
        CH_INOUT_BIND_IMPL3(ch_flip_t<parent>::traits::port_type, CH_INOUT_FLIP_BIND_FIELD, __VA_ARGS__) \
      }; \
    public: \
      using traits = ch::internal::io_traits<__flip_type__, ch_direction((int)ch_flip_t<parent>::traits::direction | (int)CH_INOUT_FLIP_DIRECTION(__VA_ARGS__)), inout_name, __port_type__, __value_type__>; \
    }; \
    inout_name& operator=(const inout_name&) = delete; \
  public: \
    CH_INOUT_BODY_IMPL3(inout_name, parent, CH_INOUT_FIELD, __VA_ARGS__) \
  private: \
    class __flop_port_type__ : public parent::traits::port_type { \
    public: \
      using __port_type__ = __flop_port_type__; \
      using __self_type__ = inout_name; \
      using __flip_port_type__ = typename __flip_type__::traits::port_type; \
      __flop_port_type__(inout_name& rhs) \
        : parent::traits::port_type(rhs) \
        , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BIND_IMPL3(parent::traits::port_type, CH_INOUT_BIND_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::io_traits<inout_name, ch_direction((int)parent::traits::direction | (int)CH_INOUT_DIRECTION(__VA_ARGS__)), __flip_type__, __flop_port_type__, __value_type__>; \
  }

#define CH_INOUT2(name, body) \
  CH_INOUT_IMPL2(name, CH_REM body)

#define CH_INOUT3(name, parent, body) \
  CH_INOUT_IMPL3(name, parent, CH_REM body)

#define GET_INOUT(_1, _2, _3, NAME, ...) NAME
#define CH_INOUT(...) GET_INOUT(__VA_ARGS__, CH_INOUT3, CH_INOUT2)(__VA_ARGS__)

#define CH_IO(...) \
  CH_INOUT_IMPL2(__io_type__, __VA_ARGS__); \
  __io_type__ io

#define CH_FLIP(x) (ch_flip_t<x>)
