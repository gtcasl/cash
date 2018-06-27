#pragma once

#include "logic.h"

#define CH_UNION_SIZE_EACH(a, i, x) \
  ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_UNION_SIZE(...) \
  std::max({CH_FOR_EACH(CH_UNION_SIZE_EACH, , CH_SEP_COMMA, __VA_ARGS__)})

#define CH_UNION_SCALAR_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::make_shared<ch::internal::type_buffer_t<traits>>( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0))

#define CH_UNION_LOGIC_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::make_shared<ch::internal::type_buffer_t<traits>>( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0, \
    CH_STRINGIZE(CH_PAIR_R(x))))

#define CH_UNION_MOVE_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::move(__other.CH_PAIR_R(x)))

#define CH_UNION_SCALAR_FIELD(a, i, x) \
  ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_LOGIC_FIELD(a, i, x) \
  ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_SCALAR_FIELD_CTOR(type, i, x) \
  type(const ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>>& CH_CONCAT(_,CH_PAIR_R(x))) \
    : type() { \
    this->operator =(CH_CONCAT(_,CH_PAIR_R(x)).as_scbit().pad<traits::bitwidth>().as<type>()); \
  }

#define CH_UNION_LOGIC_FIELD_CTOR(type, i, x) \
  type(const ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>>& CH_CONCAT(_,CH_PAIR_R(x)), CH_SLOC) \
    : type(std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, sloc, CH_STRINGIZE(name))) { \
    this->operator =(CH_CONCAT(_,CH_PAIR_R(x)).as_bit().pad<traits::bitwidth>(sloc).as<type>()); \
  }

#define CH_UNION_SCALAR_IMPL(union_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit union_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth)) \
    : CH_FOR_EACH(CH_UNION_SCALAR_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& __other) \
    : union_name(ch::internal::type_accessor_t<traits>::copy_buffer(__other)) {} \
  union_name(union_name&& __other) \
    : CH_FOR_EACH(CH_UNION_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  CH_FOR_EACH(CH_UNION_SCALAR_FIELD_CTOR, union_name, CH_SEP_SPACE, __VA_ARGS__) \
protected: \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  } \
public:

#define CH_UNION_LOGIC_IMPL(union_name, name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit union_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, CH_CUR_SLOC, CH_STRINGIZE(name))) \
    : CH_FOR_EACH(CH_UNION_LOGIC_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& __other, CH_SLOC) \
    : union_name(ch::internal::type_accessor_t<traits>::copy_buffer(__other, sloc, CH_STRINGIZE(name))) {} \
  union_name(union_name&& __other) \
    : CH_FOR_EACH(CH_UNION_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  CH_FOR_EACH(CH_UNION_LOGIC_FIELD_CTOR, union_name, CH_SEP_SPACE, __VA_ARGS__) \
protected: \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  }

#define CH_UNION_ASSIGN_IMPL(union_name) \
public: \
  union_name& operator=(const union_name& __other) { \
    ch::internal::type_accessor_t<traits>::copy(*this, __other); \
    return *this; \
  } \
  union_name& operator=(union_name&& __other) { \
    ch::internal::type_accessor_t<traits>::move(*this, std::move(__other)); \
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
