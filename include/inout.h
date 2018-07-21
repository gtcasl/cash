#pragma once

#include "ioport.h"

#define CH_INOUT_DIR_EACH(a, i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)>::traits::direction

#define CH_INOUT_DIR(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_DIR_EACH, , CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_FLIP_DIR_EACH(a, i, x) \
  ch_flip_io<ch::internal::identity_t<CH_PAIR_L(x)>>::traits::direction

#define CH_INOUT_FLIP_DIR(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_FLIP_DIR_EACH, , CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_LOGIC_FIELD(a, i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)> CH_PAIR_R(x)

#define CH_INOUT_LOGIC_FLIP_FIELD(a, i, x) \
  ch_flip_io<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_INOUT_SCALAR_COPY_CTOR(a, i, x) \
  CH_PAIR_R(x)(__other.CH_PAIR_R(x))

#define CH_INOUT_LOGIC_COPY_CTOR(a, i, x) \
  CH_PAIR_R(x)(__other.CH_PAIR_R(x), sloc)

#define CH_INOUT_CTOR_BODY(a, i, x) \
  CH_PAIR_R(x)(ch::internal::stringf("%s_%s", name.c_str(), CH_STRINGIZE(CH_PAIR_R(x))).c_str(), sloc)

#define CH_INOUT_BIND_BODY(a, i, x) \
  this->CH_PAIR_R(x)(__other.CH_PAIR_R(x))

#define CH_INOUT_SCALAR_FIELD(a, i, x) \
  ch::internal::ch_scalar_io<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_INOUT_SCALAR_FLIP_FIELD(a, i, x) \
  ch::internal::ch_scalar_io<ch_flip_io<ch::internal::identity_t<CH_PAIR_L(x)>>> CH_PAIR_R(x)

#define CH_INOUT_MOVE_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::move(__other.CH_PAIR_R(x)))

#define CH_BASIC_INOUT_SCALAR_IMPL(inout_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit inout_name(const typename traits::logic_io& __other) \
    : CH_FOR_EACH(CH_INOUT_SCALAR_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit inout_name(const inout_name& __other) \
    : CH_FOR_EACH(CH_INOUT_SCALAR_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __other) \
    : CH_FOR_EACH(CH_INOUT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  void operator()(typename traits::flip_io& __other) { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  inout_name& operator=(const inout_name&) = delete; \
  inout_name& operator=(inout_name&&) = delete;

#define CH_BASIC_INOUT_LOGIC_IMPL(inout_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit inout_name(const std::string& name = "io", CH_SLOC) \
    : CH_FOR_EACH(CH_INOUT_CTOR_BODY, , CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit inout_name(const typename traits::flip_io& __other, CH_SLOC) \
    : CH_FOR_EACH(CH_INOUT_LOGIC_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit inout_name(const inout_name& __other, CH_SLOC) \
    : CH_FOR_EACH(CH_INOUT_LOGIC_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __other) \
    : CH_FOR_EACH(CH_INOUT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  void operator()(typename traits::flip_io& __other) { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  inout_name& operator=(const inout_name&) = delete; \
  inout_name& operator=(inout_name&&) = delete;

#define CH_DERIVED_INOUT_SCALAR_IMPL(inout_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit inout_name(const typename traits::logic_io& __other) \
    : base(__other) \
    , CH_FOR_EACH(CH_INOUT_SCALAR_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit inout_name(const inout_name& __other) \
    : base(__other) \
    , CH_FOR_EACH(CH_INOUT_SCALAR_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __other) \
    : base(std::move(__other)) \
    , CH_FOR_EACH(CH_INOUT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  void operator()(typename traits::flip_io& __other) { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  inout_name& operator=(const inout_name&) = delete; \
  inout_name& operator=(inout_name&&) = delete;

#define CH_DERIVED_INOUT_LOGIC_IMPL(inout_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit inout_name(const std::string& name = "io", CH_SLOC) \
    : base(name, sloc) \
    , CH_FOR_EACH(CH_INOUT_CTOR_BODY, , CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit inout_name(const typename traits::flip_io& __other, CH_SLOC) \
    : base(__other, sloc) \
    , CH_FOR_EACH(CH_INOUT_LOGIC_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  explicit inout_name(const inout_name& __other, CH_SLOC) \
    : base(__other, sloc) \
    , CH_FOR_EACH(CH_INOUT_LOGIC_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __other) \
    : base(std::move(__other)) \
    , CH_FOR_EACH(CH_INOUT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  void operator()(typename traits::flip_io& __other) { \
    base::operator()(__other); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  inout_name& operator=(const inout_name&) = delete; \
  inout_name& operator=(inout_name&&) = delete;

#define CH_BASIC_INOUT_IMPL(inout_name, ...) \
  class inout_name { \
  private: \
    class __scalar_io__; \
    class __scalar_flip_io__; \
    class __logic_flip_io__ { \
    public: \
      using traits = ch::internal::logic_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
        CH_INOUT_FLIP_DIR(__VA_ARGS__), __logic_flip_io__, inout_name, __scalar_flip_io__>; \
      CH_BASIC_INOUT_LOGIC_IMPL(__logic_flip_io__, CH_INOUT_LOGIC_FLIP_FIELD, __VA_ARGS__) \
    }; \
    class __scalar_io__ { \
    public: \
      using traits = ch::internal::scalar_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
        CH_INOUT_DIR(__VA_ARGS__), __scalar_io__, __scalar_flip_io__, inout_name>; \
      CH_BASIC_INOUT_SCALAR_IMPL(__scalar_io__, CH_INOUT_SCALAR_FIELD, __VA_ARGS__) \
    }; \
    class __scalar_flip_io__ { \
    public: \
      using traits = ch::internal::scalar_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
        CH_INOUT_DIR(__VA_ARGS__), __scalar_flip_io__, __scalar_io__, __logic_flip_io__>; \
      CH_BASIC_INOUT_SCALAR_IMPL(__scalar_flip_io__, CH_INOUT_SCALAR_FLIP_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::logic_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
      CH_INOUT_DIR(__VA_ARGS__), inout_name, __logic_flip_io__, __scalar_io__>; \
    CH_BASIC_INOUT_LOGIC_IMPL(inout_name, CH_INOUT_LOGIC_FIELD, __VA_ARGS__) \
  }

#define CH_DERIVED_INOUT_IMPL(inout_name, parent, ...) \
  class inout_name : public parent { \
  private: \
    class __scalar_io__; \
    class __scalar_flip_io__; \
    class __logic_flip_io__ : public ch_flip_io<parent> { \
    public: \
      using base = ch_flip_io<parent>; \
      using traits = ch::internal::logic_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
        ch_direction_v<base> | CH_INOUT_FLIP_DIR(__VA_ARGS__), __logic_flip_io__, inout_name, __scalar_flip_io__>; \
      CH_DERIVED_INOUT_LOGIC_IMPL(__logic_flip_io__, CH_INOUT_LOGIC_FLIP_FIELD, __VA_ARGS__) \
    }; \
    class __scalar_io__ : public ch::internal::ch_scalar_io<parent> { \
    public: \
      using base = ch::internal::ch_scalar_io<parent>; \
      using traits = ch::internal::scalar_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
        ch_direction_v<base> | CH_INOUT_FLIP_DIR(__VA_ARGS__), __scalar_io__, __scalar_flip_io__, inout_name>; \
      CH_DERIVED_INOUT_SCALAR_IMPL(__scalar_io__, CH_INOUT_SCALAR_FIELD, __VA_ARGS__) \
    }; \
    class __scalar_flip_io__ : public ch::internal::ch_scalar_io<ch_flip_io<parent>> { \
    public: \
      using base = ch::internal::ch_scalar_io<ch_flip_io<parent>>; \
      using traits = ch::internal::scalar_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
        ch_direction_v<base> | CH_INOUT_DIR(__VA_ARGS__), __scalar_flip_io__, __scalar_io__, __logic_flip_io__>; \
      CH_DERIVED_INOUT_SCALAR_IMPL(__scalar_flip_io__, CH_INOUT_SCALAR_FLIP_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using base = parent; \
    using traits = ch::internal::logic_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
      ch_direction_v<base> | CH_INOUT_DIR(__VA_ARGS__), inout_name, __logic_flip_io__, __scalar_io__>; \
    CH_DERIVED_INOUT_LOGIC_IMPL(inout_name, CH_INOUT_LOGIC_FIELD, __VA_ARGS__) \
  }

#define CH_BASIC_INOUT(name, body) \
  CH_BASIC_INOUT_IMPL(name, CH_REM body)

#define CH_DERIVED_INOUT(name, parent, body) \
  CH_DERIVED_INOUT_IMPL(name, parent, CH_REM body)

#define GET_INOUT(_1, _2, _3, NAME, ...) NAME
#define CH_INOUT(...) GET_INOUT(__VA_ARGS__, CH_DERIVED_INOUT, CH_BASIC_INOUT, ignore)(__VA_ARGS__)

#define CH_IO(...) \
  CH_BASIC_INOUT_IMPL(__io_type__, __VA_ARGS__); \
  __io_type__ io

#define CH_FLIP(x) (ch_flip_io<x>)
