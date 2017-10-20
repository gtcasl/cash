#pragma once

#include "bit.h"

#define CH_STRUCT_SIZE_EACH(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)>::bitsize

#define CH_STRUCT_SIZE(...) \
  (CH_FOR_EACH(CH_STRUCT_SIZE_EACH, CH_SEP_PLUS, __VA_ARGS__))

#define CH_STRUCT_FIELD_OFFSET(i, x) \
  CH_CONCAT(__field_offset, CH_INC(i)) = __field_offset##i + ch::internal::identity_t<CH_PAIR_L(x)>::bitsize

#define CH_STRUCT_SCALAR_FIELD(i, x) \
  ch_scalar_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_FIELD(i, x) \
  ch_value_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_CONST_FIELD(i, x) \
  ch_const_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_SCALAR_DEFAULT_CTOR(i, x) \
  CH_PAIR_R(x)(ch::internal::scalar_buffer(ch::internal::identity_t<CH_PAIR_L(x)>::bitsize, buffer, __field_offset##i))

#define CH_STRUCT_DEFAULT_CTOR(i, x) \
  CH_PAIR_R(x)(ch::internal::bit_buffer(ch::internal::identity_t<CH_PAIR_L(x)>::bitsize, buffer, __field_offset##i))

#define CH_STRUCT_MOVE_CTOR(i, x) \
  CH_PAIR_R(x)(std::move(__rhs__.CH_PAIR_R(x)))

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

#define CH_STRUCT_MOVE_ASSIGN(i, x) \
  this->CH_PAIR_R(x) = std::move(__rhs__.CH_PAIR_R(x))

#define CH_STRUCT_SCALAR_GETBUFFER(i, x) \
  return ch::internal::scalar_accessor::get_buffer(CH_PAIR_R(x))

#define CH_STRUCT_GETBUFFER(i, x) \
  return ch::internal::bit_accessor::get_buffer(CH_PAIR_R(x))

#define CH_STRUCT_CLONE(i, x) \
  CH_PAIR_R(x).clone()

#define CH_STRUCT_SCALAR_IMPL2(struct_name, value_name, ...) \
  class struct_name { \
  public: \
    static constexpr unsigned bitsize = CH_STRUCT_SIZE(__VA_ARGS__); \
    using traits = ch::internal::scalar_traits<struct_name, value_name>; \
  protected: \
    enum { __field_offset0 = 0, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, CH_SEP_COMMA, __VA_ARGS__) }; \
  public: \
    CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    struct_name(const ch::internal::scalar_buffer& buffer = ch::internal::scalar_buffer(bitsize)) \
      : CH_FOR_EACH(CH_STRUCT_SCALAR_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) { assert(bitsize == buffer.get_size()); } \
    struct_name(const struct_name& __rhs__) \
      : struct_name(ch::internal::scalar_accessor::clone(__rhs__)) {} \
    struct_name(struct_name&& __rhs__) \
      : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    explicit struct_name(const ch_scalar<bitsize>& __rhs__) \
      : struct_name(ch::internal::scalar_buffer(ch::internal::scalar_accessor::get_data(__rhs__))) {} \
    template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
    explicit struct_name(__T__ __rhs__) \
      : struct_name(ch::internal::scalar_buffer(bitvector(bitsize, __rhs__))) {} \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : struct_name() { \
      CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    struct_name& operator=(const struct_name& __rhs__) { \
      ch::internal::scalar_accessor::copy(*this, __rhs__); \
      return *this; \
    } \
    struct_name& operator=(struct_name&& __rhs__) { \
      CH_FOR_EACH(CH_STRUCT_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_SCALAR_TYPE_INTERFACE() \
  private: \
    const ch::internal::scalar_buffer& get_buffer() const { \
      CH_FOR_EACH_1(0, CH_STRUCT_SCALAR_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    ch::internal::scalar_buffer& get_buffer() { \
      CH_FOR_EACH_1(0, CH_STRUCT_SCALAR_GETBUFFER, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    friend class ch::internal::scalar_accessor; \
  }

#define CH_STRUCT_SCALAR_IMPL3(struct_name, value_name, parent, ...) \
  class struct_name : public parent { \
  public: \
    static constexpr unsigned bitsize = parent::bitsize + CH_STRUCT_SIZE(__VA_ARGS__); \
    using traits = ch::internal::scalar_traits<struct_name, value_name>; \
  private: \
    enum { __field_offset0 = parent::bitsize, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, CH_SEP_COMMA, __VA_ARGS__) }; \
  public: \
    CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    struct_name(const ch::internal::scalar_buffer& buffer = ch::internal::scalar_buffer(bitsize)) \
      : parent(ch::internal::scalar_buffer(parent::bitsize, buffer, 0)) \
      , CH_FOR_EACH(CH_STRUCT_SCALAR_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) { assert(bitsize == buffer.get_size()); } \
    struct_name(const struct_name& __rhs__) \
      : struct_name(ch::internal::scalar_accessor::clone(__rhs__)) {} \
    struct_name(struct_name&& __rhs__) \
      : parent(std::move(__rhs__)) \
      , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    explicit struct_name(const ch_scalar<bitsize>& __rhs__) \
        : struct_name(ch::internal::scalar_buffer(ch::internal::scalar_accessor::get_data(__rhs__))) {} \
    template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
    explicit struct_name(__T__ __rhs__) \
      : struct_name(ch::internal::scalar_buffer(bitvector(bitsize, __rhs__))) {} \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), typename... __Ts__, \
              CH_REVERSE_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__), __Ts__&&... __args__) \
      : struct_name() { \
      ch::internal::scalar_accessor::copy<parent>(*this, parent(__args__...)); \
      CH_FOR_EACH(CH_STRUCT_SCALAR_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    struct_name& operator=(const struct_name& __rhs__) { \
      ch::internal::scalar_accessor::copy(*this, __rhs__); \
      return *this; \
    } \
    struct_name& operator=(struct_name&& __rhs__) { \
      parent::operator=(std::move(__rhs__)); \
      CH_FOR_EACH(CH_STRUCT_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_SCALAR_TYPE_INTERFACE() \
  private: \
    const ch::internal::scalar_buffer& get_buffer() const { \
      return ch::internal::scalar_accessor::get_buffer<parent>(*this); \
    } \
    ch::internal::scalar_buffer& get_buffer() { \
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
  struct_name(const ch::internal::bit_buffer& buffer = ch::internal::bit_buffer(bitsize)) \
    : CH_FOR_EACH(CH_STRUCT_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) { assert(bitsize == buffer.get_size()); } \
  struct_name(const struct_name& __rhs__) \
    : struct_name(ch::internal::bit_accessor::clone(__rhs__)) {} \
  struct_name(struct_name&& __rhs__) : \
    CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const reverse_name& __rhs__) \
    : struct_name(ch::internal::bit_accessor::clone(__rhs__)) {} \
  template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
  explicit struct_name(__T__ __rhs__) \
    : struct_name(ch::internal::bit_buffer(bitvector(bitsize, __rhs__))) {} \
  explicit struct_name(const ch_scalar<bitsize>& __rhs__) \
    : struct_name(ch::internal::bit_buffer(ch::internal::scalar_accessor::get_data(__rhs__))) {} \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
    : struct_name() { \
    CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  const auto clone() const { \
    return typename traits::value_type(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__)); \
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
  enum { __field_offset0 = __parent_type__::bitsize, \
         CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  struct_name(const ch::internal::bit_buffer& buffer = ch::internal::bit_buffer(bitsize)) \
    : __parent_type__(ch::internal::bit_buffer(__parent_type__::bitsize, buffer, 0)) \
    , CH_FOR_EACH(CH_STRUCT_DEFAULT_CTOR, CH_SEP_COMMA, __VA_ARGS__) { assert(bitsize == buffer.get_size()); } \
  struct_name(const struct_name& __rhs__) \
    : struct_name(ch::internal::bit_accessor::clone(__rhs__)) {} \
  struct_name(struct_name&& __rhs__) \
    : __parent_type__(std::move(__rhs__))\
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  struct_name(const reverse_name& __rhs__) \
    : struct_name(ch::internal::bit_accessor::clone(__rhs__)) {} \
  template <typename __T__, CH_REQUIRES(ch::internal::is_integral_or_enum<__T__>::value)> \
  explicit struct_name(__T__ __rhs__) \
    : struct_name(ch::internal::bit_buffer(bitvector(bitsize, __rhs__))) {} \
  explicit struct_name(const ch_scalar<bitsize>& __rhs__) \
    : struct_name(ch::internal::bit_buffer(ch::internal::scalar_accessor::get_data(__rhs__))) {} \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), typename... __Ts__, \
            CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__), __Ts__&&... __args__) \
    : struct_name() { \
    ch::internal::bit_accessor::copy<__parent_type__>(*this, __parent_type__(__args__...)); \
    CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  const auto clone() const { \
    return typename traits::value_type(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__), __parent_type__::clone()); \
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
  CH_BIT_WRITABLE_INTERFACE(struct_name) \
  struct_name& operator=(const struct_name& __rhs__) { \
    ch::internal::bit_accessor::copy(*this, __rhs__); \
    return *this; \
  } \
  struct_name& operator=(struct_name&& __rhs__) { \
    CH_FOR_EACH(CH_STRUCT_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
    return *this; \
  } \
  struct_name& operator=(const __const_type__& __rhs__) { \
    ch::internal::bit_accessor::copy(*this, __rhs__); \
    return *this; \
  }

#define CH_STRUCT_READONLY_IMP32(struct_name, ...) \
  CH_BIT_READONLY_INTERFACE(struct_name)

#define CH_STRUCT_WRITABLE_IMPL3(struct_name, ...) \
  CH_BIT_WRITABLE_INTERFACE(struct_name) \
  struct_name& operator=(const struct_name& __rhs__) { \
    ch::internal::bit_accessor::copy(*this, __rhs__); \
    return *this; \
  } \
  struct_name& operator=(struct_name&& __rhs__) { \
    __parent_type__::operator=(std::move(__rhs__)); \
    CH_FOR_EACH(CH_STRUCT_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
    return *this; \
  } \
  struct_name& operator=(const __const_type__& __rhs__) { \
    ch::internal::bit_accessor::copy(*this, __rhs__); \
    return *this; \
  }

#define CH_STRUCT_IMPL2(struct_name, ...) \
  class struct_name { \
  private: \
    CH_STRUCT_SCALAR_IMPL2(__scalar_type__, struct_name, __VA_ARGS__); \
    class __const_type__ { \
    public: \
      static constexpr unsigned bitsize = CH_STRUCT_SIZE(__VA_ARGS__); \
      using traits = ch::internal::logic_traits<__const_type__, __const_type__, struct_name, __scalar_type__>; \
      CH_STRUCT_BODY_IMPL2(__const_type__, struct_name, CH_STRUCT_READONLY_IMPL2, CH_STRUCT_CONST_FIELD, __VA_ARGS__) \
    }; \
  public: \
    static constexpr unsigned bitsize = CH_STRUCT_SIZE(__VA_ARGS__); \
    using traits = ch::internal::logic_traits<struct_name, __const_type__, struct_name, __scalar_type__>; \
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
      static constexpr unsigned bitsize = parent::bitsize + CH_STRUCT_SIZE(__VA_ARGS__); \
      using traits = ch::internal::logic_traits<__const_type__, __const_type__, struct_name, __scalar_type__>; \
      CH_STRUCT_BODY_IMPL3(__const_type__, struct_name, CH_STRUCT_READONLY_IMPL2, CH_STRUCT_CONST_FIELD, __VA_ARGS__) \
    }; \
    using __parent_type__ = parent; \
  public: \
    static constexpr unsigned bitsize = parent::bitsize + CH_STRUCT_SIZE(__VA_ARGS__); \
    using traits = ch::internal::logic_traits<struct_name, __const_type__, struct_name, __scalar_type__>; \
    CH_STRUCT_BODY_IMPL3(struct_name, __const_type__, CH_STRUCT_WRITABLE_IMPL3, CH_STRUCT_FIELD, __VA_ARGS__) \
  }

#define CH_STRUCT2(name, body) \
  CH_STRUCT_IMPL2(name, CH_REM body)

#define CH_STRUCT3(name, parent, body) \
  CH_STRUCT_IMPL3(name, parent, CH_REM body)

#define GET_STRUCT(_1, _2, _3, NAME, ...) NAME
#define CH_STRUCT(...) GET_STRUCT(__VA_ARGS__, CH_STRUCT3, CH_STRUCT2)(__VA_ARGS__)
