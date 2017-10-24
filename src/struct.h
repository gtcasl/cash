#pragma once

#include "bit.h"

#define CH_STRUCT_SIZE_EACH(i, x) \
  ch_bitwidth_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_STRUCT_SIZE(...) \
  (CH_FOR_EACH(CH_STRUCT_SIZE_EACH, CH_SEP_PLUS, __VA_ARGS__))

#define CH_STRUCT_FIELD_OFFSET(i, x) \
  CH_CONCAT(__field_offset, CH_INC(i)) = __field_offset##i + ch_bitwidth_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_STRUCT_SCALAR_FIELD(i, x) \
  ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_FIELD(i, x) \
  ch_value_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_CONST_FIELD(i, x) \
  ch_const_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_SCALAR_DEFAULT_CTOR(i, x) \
  CH_PAIR_R(x)(ch::internal::scalar_buffer(ch_bitwidth_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, __field_offset##i))

#define CH_STRUCT_DEFAULT_CTOR(i, x) \
  CH_PAIR_R(x)(ch::internal::bit_buffer(ch_bitwidth_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, __field_offset##i))

#define CH_STRUCT_MOVE_CTOR(i, x) \
  CH_PAIR_R(x)(std::move(rhs.CH_PAIR_R(x)))

#define CH_STRUCT_FIELD_CTOR_TMPL(i, x) \
  typename __T##i

#define CH_STRUCT_SCALAR_FIELD_CTOR_REQUIRES(i, x) \
  CH_REQUIRES(ch::internal::is_cast_convertible< \
    ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>>, __T##i>::value)

#define CH_STRUCT_FIELD_CTOR_REQUIRES(i, x) \
  CH_REQUIRES(ch::internal::is_cast_convertible< \
    ch_value_t<ch::internal::identity_t<CH_PAIR_L(x)>>, __T##i>::value)

#define CH_STRUCT_FIELD_CTOR_ARGS(i, x) \
  const __T##i& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_SCALAR_FIELD_CTOR_BODY(i, x) \
  ch::internal::scalar_accessor::copy(CH_PAIR_R(x), ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>>(CH_CONCAT(_,CH_PAIR_R(x))))

#define CH_STRUCT_FIELD_CTOR_BODY(i, x) \
  ch::internal::bit_accessor::copy(CH_PAIR_R(x), ch_value_t<ch::internal::identity_t<CH_PAIR_L(x)>>(CH_CONCAT(_,CH_PAIR_R(x))))

#define CH_STRUCT_SCALAR_GETBUFFER(i, x) \
  return ch::internal::scalar_accessor::get_buffer(CH_PAIR_R(x))

#define CH_STRUCT_GETBUFFER(i, x) \
  return ch::internal::bit_accessor::get_buffer(CH_PAIR_R(x))

#define CH_STRUCT_CLONE(i, x) \
  CH_PAIR_R(x).clone()

#define CH_STRUCT_SCALAR_IMPL2(struct_name, value_name, ...) \
  class struct_name { \
  public: \
    using traits = ch::internal::scalar_traits<CH_STRUCT_SIZE(__VA_ARGS__), struct_name, value_name>; \
  protected: \
    enum { __field_offset0 = 0, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, CH_SEP_COMMA, __VA_ARGS__) }; \
  public: \
    CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    struct_name(const ch::internal::scalar_buffer& buffer = ch::internal::scalar_buffer(traits::bitwidth)) \
      : CH_FOR_EACH(CH_STRUCT_SCALAR_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    struct_name(const struct_name& rhs) \
      : struct_name(ch::internal::scalar_accessor::cloneBuffer(rhs)) {} \
    struct_name(struct_name&& rhs) \
      : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    explicit struct_name(const ch_scalar<traits::bitwidth>& rhs) \
      : struct_name(ch::internal::scalar_buffer(ch::internal::scalar_accessor::get_data(rhs))) {} \
    template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
    explicit struct_name(__T__ rhs) \
      : struct_name(ch::internal::scalar_buffer(bitvector(traits::bitwidth, rhs))) {} \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : struct_name() { \
      CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    struct_name& operator=(const struct_name& rhs) { \
      ch::internal::scalar_accessor::copy(*this, rhs); \
      return *this; \
    } \
    struct_name& operator=(struct_name&& rhs) { \
      ch::internal::scalar_accessor::move(*this, std::move(rhs)); \
      return *this; \
    } \
    CH_SCALAR_TYPE_INTERFACE(struct_name) \
  private: \
    const ch::internal::scalar_buffer_ptr& get_buffer() const { \
      CH_FOR_EACH_1(0, CH_STRUCT_SCALAR_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__)->get_source(); \
    } \
    ch::internal::scalar_buffer_ptr& get_buffer() { \
      CH_FOR_EACH_1(0, CH_STRUCT_SCALAR_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__)->get_source(); \
    } \
    friend class ch::internal::scalar_accessor; \
  }

#define CH_STRUCT_SCALAR_IMPL3(struct_name, value_name, parent, ...) \
  class struct_name : public parent { \
  public: \
    using traits = ch::internal::scalar_traits<ch_bitwidth_v<parent> + CH_STRUCT_SIZE(__VA_ARGS__), struct_name, value_name>; \
  private: \
    enum { __field_offset0 = ch_bitwidth_v<parent>, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, CH_SEP_COMMA, __VA_ARGS__) }; \
  public: \
    CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    struct_name(const ch::internal::scalar_buffer& buffer = ch::internal::scalar_buffer(traits::bitwidth)) \
      : parent(buffer) \
      , CH_FOR_EACH(CH_STRUCT_SCALAR_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    struct_name(const struct_name& rhs) \
      : struct_name(ch::internal::scalar_accessor::cloneBuffer(rhs)) {} \
    struct_name(struct_name&& rhs) \
      : parent(std::move(rhs)) \
      , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    explicit struct_name(const ch_scalar<traits::bitwidth>& rhs) \
        : struct_name(ch::internal::scalar_buffer(ch::internal::scalar_accessor::get_data(rhs))) {} \
    template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
    explicit struct_name(__T__ rhs) \
      : struct_name(ch::internal::scalar_buffer(bitvector(traits::bitwidth, rhs))) {} \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), typename... __Ts__, \
              CH_REVERSE_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__), __Ts__&&... args) \
      : struct_name() { \
      ch::internal::scalar_accessor::copy<parent>(*this, parent(args...)); \
      CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    struct_name& operator=(const struct_name& rhs) { \
      ch::internal::scalar_accessor::copy(*this, rhs); \
      return *this; \
    } \
    struct_name& operator=(struct_name&& rhs) { \
      ch::internal::scalar_accessor::move(*this, std::move(rhs)); \
      return *this; \
    } \
    CH_SCALAR_TYPE_INTERFACE(struct_name) \
  private: \
    const ch::internal::scalar_buffer_ptr& get_buffer() const { \
      return ch::internal::scalar_accessor::get_buffer<parent>(*this); \
    } \
    ch::internal::scalar_buffer_ptr& get_buffer() { \
      return ch::internal::scalar_accessor::get_buffer<parent>(*this); \
    } \
    friend class ch::internal::scalar_accessor; \
  }

#define CH_STRUCT_BODY_IMPL2(struct_name, reverse_name, assignment_body, field_body, ...) \
private: \
  enum { __field_offset0 = 0, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  struct_name(const ch::internal::bit_buffer& buffer = ch::internal::bit_buffer(traits::bitwidth)) \
    : CH_FOR_EACH(CH_STRUCT_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const struct_name& rhs) \
    : struct_name(ch::internal::bit_accessor::cloneBuffer(rhs)) {} \
  struct_name(struct_name&& rhs) : \
    CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const reverse_name& rhs) \
    : struct_name(ch::internal::bit_accessor::cloneBuffer(rhs)) {} \
  template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
  explicit struct_name(__T__ rhs) \
    : struct_name(ch::internal::bit_buffer(bitvector(traits::bitwidth, rhs))) {} \
  explicit struct_name(const ch_scalar<traits::bitwidth>& rhs) \
    : struct_name(ch::internal::bit_buffer(ch::internal::scalar_accessor::get_data(rhs))) {} \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
    : struct_name() { \
    CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  assignment_body(struct_name, __VA_ARGS__) \
private: \
  const ch::internal::bit_buffer& get_buffer() const { \
    CH_FOR_EACH_1(0, CH_STRUCT_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  ch::internal::bit_buffer& get_buffer() { \
    CH_FOR_EACH_1(0, CH_STRUCT_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  friend class ch::internal::bit_accessor; \

#define CH_STRUCT_BODY_IMPL3(struct_name, reverse_name, assignment_body, field_body, ...) \
private: \
  enum { __field_offset0 = ch_bitwidth_v<__parent_type__>, \
         CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  struct_name(const ch::internal::bit_buffer& buffer = ch::internal::bit_buffer(traits::bitwidth)) \
    : __parent_type__(buffer) \
    , CH_FOR_EACH(CH_STRUCT_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const struct_name& rhs) \
    : struct_name(ch::internal::bit_accessor::cloneBuffer(rhs)) {} \
  struct_name(struct_name&& rhs) \
    : __parent_type__(std::move(rhs))\
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const reverse_name& rhs) \
    : struct_name(ch::internal::bit_accessor::cloneBuffer(rhs)) {} \
  template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
  explicit struct_name(__T__ rhs) \
    : struct_name(ch::internal::bit_buffer(bitvector(traits::bitwidth, rhs))) {} \
  explicit struct_name(const ch_scalar<traits::bitwidth>& rhs) \
    : struct_name(ch::internal::bit_buffer(ch::internal::scalar_accessor::get_data(rhs))) {} \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), typename... __Ts__, \
            CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__), __Ts__&&... args) \
    : struct_name() { \
    ch::internal::bit_accessor::copy<__parent_type__>(*this, __parent_type__(args...)); \
    CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  assignment_body(struct_name, __VA_ARGS__) \
private: \
  const ch::internal::bit_buffer& get_buffer() const { \
    return ch::internal::bit_accessor::get_buffer<__parent_type__>(*this); \
  } \
  ch::internal::bit_buffer& get_buffer() { \
    return ch::internal::bit_accessor::get_buffer<__parent_type__>(*this); \
  } \
  friend class ch::internal::bit_accessor; \

#define CH_STRUCT_READONLY_IMPL2(struct_name, ...) \
  CH_BIT_READONLY_INTERFACE(struct_name)

#define CH_STRUCT_WRITABLE_IMPL2(struct_name, ...) \
  CH_BIT_READONLY_INTERFACE(struct_name) \
  CH_BIT_WRITABLE_INTERFACE(struct_name) \
  struct_name& operator=(const struct_name& rhs) { \
    ch::internal::bit_accessor::copy(*this, rhs); \
    return *this; \
  } \
  struct_name& operator=(struct_name&& rhs) { \
    ch::internal::bit_accessor::move(*this, std::move(rhs)); \
    return *this; \
  } \
  struct_name& operator=(const __const_type__& rhs) { \
    ch::internal::bit_accessor::copy(*this, rhs); \
    return *this; \
  }

#define CH_STRUCT_READONLY_IMP32(struct_name, ...) \
  CH_BIT_READONLY_INTERFACE(struct_name)

#define CH_STRUCT_WRITABLE_IMPL3(struct_name, ...) \
  CH_BIT_READONLY_INTERFACE(struct_name) \
  CH_BIT_WRITABLE_INTERFACE(struct_name) \
  struct_name& operator=(const struct_name& rhs) { \
    ch::internal::bit_accessor::copy(*this, rhs); \
    return *this; \
  } \
  struct_name& operator=(struct_name&& rhs) { \
    ch::internal::bit_accessor::move(*this, std::move(rhs)); \
    return *this; \
  } \
  struct_name& operator=(const __const_type__& rhs) { \
    ch::internal::bit_accessor::copy(*this, rhs); \
    return *this; \
  }

#define CH_STRUCT_IMPL2(struct_name, ...) \
  class struct_name { \
  private: \
    CH_STRUCT_SCALAR_IMPL2(__scalar_type__, struct_name, __VA_ARGS__); \
    class __const_type__ { \
    public: \
      using traits = ch::internal::logic_traits<CH_STRUCT_SIZE(__VA_ARGS__), __const_type__, __const_type__, struct_name, __scalar_type__>; \
      CH_STRUCT_BODY_IMPL2(__const_type__, struct_name, CH_STRUCT_READONLY_IMPL2, CH_STRUCT_CONST_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<CH_STRUCT_SIZE(__VA_ARGS__), struct_name, __const_type__, struct_name, __scalar_type__>; \
    CH_STRUCT_BODY_IMPL2(struct_name, __const_type__, CH_STRUCT_WRITABLE_IMPL2, CH_STRUCT_FIELD, __VA_ARGS__) \
  }

#define CH_STRUCT_IMPL3(struct_name, parent, ...) \
  class struct_name : public parent { \
  private: \
    CH_STRUCT_SCALAR_IMPL3(__scalar_type__, struct_name, ch_scalar_t<parent>, __VA_ARGS__); \
    class __const_type__ : public ch_const_t<parent> { \
    private: \
      using __parent_type__ = ch_const_t<parent>; \
    public: \
      using traits = ch::internal::logic_traits<ch_bitwidth_v<parent> + CH_STRUCT_SIZE(__VA_ARGS__), __const_type__, __const_type__, struct_name, __scalar_type__>; \
      CH_STRUCT_BODY_IMPL3(__const_type__, struct_name, CH_STRUCT_READONLY_IMPL2, CH_STRUCT_CONST_FIELD, __VA_ARGS__) \
    }; \
    using __parent_type__ = parent; \
  public: \
    using traits = ch::internal::logic_traits<ch_bitwidth_v<parent> + CH_STRUCT_SIZE(__VA_ARGS__), struct_name, __const_type__, struct_name, __scalar_type__>; \
    CH_STRUCT_BODY_IMPL3(struct_name, __const_type__, CH_STRUCT_WRITABLE_IMPL3, CH_STRUCT_FIELD, __VA_ARGS__) \
  }

#define CH_STRUCT2(name, body) \
  CH_STRUCT_IMPL2(name, CH_REM body)

#define CH_STRUCT3(name, parent, body) \
  CH_STRUCT_IMPL3(name, parent, CH_REM body)

#define GET_STRUCT(_1, _2, _3, NAME, ...) NAME
#define CH_STRUCT(...) GET_STRUCT(__VA_ARGS__, CH_STRUCT3, CH_STRUCT2)(__VA_ARGS__)
