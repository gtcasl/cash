#pragma once

#include "logic.h"

#define CH_STRUCT_SIZE_EACH(a, i, x) \
  ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_STRUCT_SIZE(...) \
  (CH_FOR_EACH(CH_STRUCT_SIZE_EACH, , CH_SEP_PLUS, __VA_ARGS__))

#define CH_STRUCT_FIELD_OFFSET(a, i, x) \
  CH_CONCAT(__field_offset, CH_INC(i)) = __field_offset##i + ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_STRUCT_SCALAR_FIELD(a, i, x) \
  ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_LOGIC_FIELD(a, i, x) \
  ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_SCALAR_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::make_shared<ch::internal::type_buffer_t<traits>>( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, __field_offset##i))

#define CH_STRUCT_LOGIC_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::make_shared<ch::internal::type_buffer_t<traits>>( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, __field_offset##i, \
    CH_STRINGIZE(CH_PAIR_R(x))))

#define CH_STRUCT_MOVE_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::move(rhs.CH_PAIR_R(x)))

#define CH_STRUCT_SCALAR_FIELD_CTOR_ARGS(a, i, x) \
  const ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>>& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_LOGIC_FIELD_CTOR_ARGS(a, i, x) \
  const ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>>& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_FIELD_CTOR_INIT(a, i, x) \
  CH_PAIR_R(x) = CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_GETBUFFER(i, x) \
  return ch::internal::type_accessor_t<traits>::buffer(CH_PAIR_R(x))

#define CH_STRUCT_CLONE(a, i, x) \
  CH_PAIR_R(x).clone()

#define CH_BASIC_STRUCT_SCALAR_IMPL(struct_name, field_body, ...) \
private: \
  enum { __field_offset0 = 0, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit struct_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth)) \
    : CH_FOR_EACH(CH_STRUCT_SCALAR_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const struct_name& rhs) \
    : struct_name(ch::internal::type_accessor_t<traits>::copy_buffer(rhs)) {} \
  struct_name(struct_name&& rhs) : \
    CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__)) \
    : struct_name() { \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  } \
public:

#define CH_BASIC_STRUCT_LOGIC_IMPL(struct_name, name, field_body, ...) \
private: \
  enum { __field_offset0 = 0, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit struct_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, CH_CUR_SLOC, CH_STRINGIZE(name))) \
    : CH_FOR_EACH(CH_STRUCT_LOGIC_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const struct_name& rhs, CH_SLOC) \
    : struct_name(ch::internal::type_accessor_t<traits>::copy_buffer(rhs, sloc, CH_STRINGIZE(name))) {} \
  struct_name(struct_name&& rhs) : \
    CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_LOGIC_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) \
    : struct_name(std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, sloc, CH_STRINGIZE(name))) { \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    CH_STRUCT_GETBUFFER(0, CH_FIRST_ARG(__VA_ARGS__))->source(); \
  } \
public:

#define CH_DERIVED_STRUCT_SCALAR_IMPL(struct_name, field_body, ...) \
private: \
  enum { __field_offset0 = ch_width_v<base>, \
         CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit struct_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth)) \
    : base(buffer) \
    , CH_FOR_EACH(CH_STRUCT_SCALAR_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const struct_name& rhs) \
    : struct_name(ch::internal::type_accessor_t<traits>::copy_buffer(rhs)) {} \
  struct_name(struct_name&& rhs) \
    : base(std::move(rhs))\
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__), const base& parent) \
    : struct_name() { \
    ch::internal::type_accessor_t<traits>::write(*this, 0, parent, 0, ch_width_v<base>); \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    return base::buffer(); \
  } \
public:

#define CH_DERIVED_STRUCT_LOGIC_IMPL(struct_name, name, field_body, ...) \
private: \
  enum { __field_offset0 = ch_width_v<base>, \
         CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit struct_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, CH_CUR_SLOC, CH_STRINGIZE(name))) \
    : base(buffer) \
    , CH_FOR_EACH(CH_STRUCT_LOGIC_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const struct_name& rhs, CH_SLOC) \
    : struct_name(ch::internal::type_accessor_t<traits>::copy_buffer(rhs, sloc, CH_STRINGIZE(name))) {} \
  struct_name(struct_name&& rhs) \
    : base(std::move(rhs))\
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_LOGIC_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__), const base& parent, CH_SLOC) \
    : struct_name(std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, sloc, CH_STRINGIZE(name))) { \
    ch::internal::type_accessor_t<traits>::write(*this, 0, parent, 0, ch_width_v<base>); \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer() const { \
    return base::buffer(); \
  }

#define CH_STRUCT_ASSIGN_IMPL(struct_name) \
public: \
  struct_name& operator=(const struct_name& rhs) { \
    ch::internal::type_accessor_t<traits>::copy(*this, rhs); \
    return *this; \
  } \
  struct_name& operator=(struct_name&& rhs) { \
    ch::internal::type_accessor_t<traits>::move(*this, std::move(rhs)); \
    return *this; \
  }

#define CH_STRUCT_SCALAR_FRIENDS_IMPL(enum_name) \
protected: \
  friend class ch::internal::scalar_accessor;

#define CH_STRUCT_LOGIC_FRIENDS_IMPL(enum_name) \
protected: \
  friend class ch::internal::logic_accessor;

#define CH_BASIC_STRUCT_IMPL(struct_name, ...) \
  class struct_name { \
  private: \
    class __scalar_type__ { \
    public: \
      using traits = ch::internal::scalar_traits<CH_STRUCT_SIZE(__VA_ARGS__), false, __scalar_type__, struct_name>; \
      CH_BASIC_STRUCT_SCALAR_IMPL(__scalar_type__, CH_STRUCT_SCALAR_FIELD, __VA_ARGS__) \
      CH_SCALAR_INTERFACE(__scalar_type__) \
      CH_STRUCT_ASSIGN_IMPL(__scalar_type__) \
      CH_STRUCT_SCALAR_FRIENDS_IMPL(__scalar_type__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<CH_STRUCT_SIZE(__VA_ARGS__), false, struct_name, __scalar_type__>; \
    CH_BASIC_STRUCT_LOGIC_IMPL(struct_name, struct_name, CH_STRUCT_LOGIC_FIELD, __VA_ARGS__) \
    CH_LOGIC_INTERFACE(struct_name) \
    CH_STRUCT_ASSIGN_IMPL(struct_name) \
    CH_STRUCT_LOGIC_FRIENDS_IMPL(struct_name) \
  }

#define CH_DERIVED_STRUCT_IMPL(struct_name, parent, ...) \
  class struct_name : public parent { \
  private: \
    class __scalar_type__ : public ch_scalar_t<parent> { \
    public: \
      using base = ch_scalar_t<parent>; \
      using traits = ch::internal::scalar_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), false, __scalar_type__, struct_name>; \
      CH_DERIVED_STRUCT_SCALAR_IMPL(__scalar_type__, CH_STRUCT_SCALAR_FIELD, __VA_ARGS__) \
      CH_STRUCT_ASSIGN_IMPL(__scalar_type__) \
      CH_SCALAR_INTERFACE(__scalar_type__) \
      CH_STRUCT_SCALAR_FRIENDS_IMPL(__scalar_type__) \
    }; \
  public: \
    using base = parent; \
    using traits = ch::internal::logic_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), false, struct_name, __scalar_type__>; \
    CH_DERIVED_STRUCT_LOGIC_IMPL(struct_name, struct_name, CH_STRUCT_LOGIC_FIELD, __VA_ARGS__) \
    CH_STRUCT_ASSIGN_IMPL(struct_name) \
    CH_LOGIC_INTERFACE(struct_name) \
    CH_STRUCT_LOGIC_FRIENDS_IMPL(struct_name) \
  }

#define CH_BASIC_STRUCT(name, body) \
  CH_BASIC_STRUCT_IMPL(name, CH_REM body)

#define CH_DERIVED_STRUCT(name, parent, body) \
  CH_DERIVED_STRUCT_IMPL(name, parent, CH_REM body)

#define GET_STRUCT(_1, _2, _3, NAME, ...) NAME
#define CH_STRUCT(...) GET_STRUCT(__VA_ARGS__, CH_DERIVED_STRUCT, CH_BASIC_STRUCT, ignore)(__VA_ARGS__)
