#pragma once

#include "bit.h"

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_BODY_IMPL(enum_name, reverse_name) \
  enum_name(const ch::internal::type_buffer_t<traits>& buffer = \
    ch::internal::type_buffer_t<traits>(traits::bitwidth)) : base(buffer) {} \
  enum_name(const enum_name& rhs) : base(rhs) {} \
  enum_name(enum_name&& rhs) : base(std::move(rhs)) {} \
  enum_name(const reverse_name& rhs) : base(rhs) {} \
  enum_name(enum_type rhs) : base(rhs) {}

#define CH_ENUM_WRITABLE_IMPL(enum_name, reverse_name) \
  enum_name& operator=(const enum_name& rhs) { \
    base::operator=(rhs); \
    return *this; \
  } \
  enum_name& operator=(enum_name&& rhs) { \
    base::operator=(std::move(rhs)); \
    return *this; \
  } \
  enum_name& operator=(const reverse_name& rhs) { \
    base::operator=(rhs); \
    return *this; \
  } \
  enum_name& operator=(enum_type rhs) { \
    base::operator=(rhs); \
    return *this; \
  }

#define CH_ENUM_LOGIC_FRIENDS_IMPL(enum_name) \
protected: \
  friend const auto ch_reg(const enum_name& next, const enum_name& init) { \
    return ch::internal::ch_reg(next, init); \
  } \
  friend const auto ch_reg(const enum_name& next) { \
    return ch::internal::ch_reg(next); \
  }

#define CH_ENUM_IMPL(enum_name, size, ...) \
  class enum_name : public ch::internal::ch_bit<size> { \
  public: \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __MAX_VALUE__ \
    }; \
    static_assert(ilog2(__MAX_VALUE__) <= size, "enum size mismatch"); \
  private: \
    class __logic_const_type__; \
    class __scalar_type__; \
    class __scalar_const_type__ : public ch::internal::const_scalar<size> { \
    public: \
      using base = ch::internal::const_scalar<size>; \
      using traits = ch::internal::scalar_traits<size, __scalar_const_type__, __scalar_const_type__, __scalar_type__, __logic_const_type__>; \
      CH_ENUM_BODY_IMPL(__scalar_const_type__, __scalar_type__) \
      CH_SCALAR_READONLY_INTERFACE(__scalar_const_type__) \
    }; \
    class __scalar_type__ : public ch::internal::ch_scalar<size> { \
    public: \
      using base = ch::internal::ch_scalar<size>; \
      using traits = ch::internal::scalar_traits<size, __scalar_type__, __scalar_const_type__, __scalar_type__, enum_name>; \
      CH_ENUM_BODY_IMPL(__scalar_type__, __scalar_const_type__) \
      CH_ENUM_WRITABLE_IMPL(__scalar_type__, __scalar_const_type__) \
      CH_SCALAR_READONLY_INTERFACE(__scalar_type__) \
      CH_SCALAR_WRITABLE_INTERFACE(__scalar_type__) \
    }; \
    class __logic_const_type__ : public ch::internal::const_bit<size> { \
    public: \
      using base = ch::internal::const_bit<size>; \
      using traits = ch::internal::logic_traits<size, __logic_const_type__, __logic_const_type__, enum_name, __scalar_const_type__>; \
      CH_ENUM_BODY_IMPL(__logic_const_type__, enum_name) \
      CH_LOGIC_READONLY_INTERFACE(__logic_const_type__) \
      CH_ENUM_LOGIC_FRIENDS_IMPL(__logic_const_type__) \
    }; \
  public: \
    using base = ch::internal::ch_bit<size>; \
    using traits = ch::internal::logic_traits<size, enum_name, __logic_const_type__, enum_name, __scalar_type__>; \
    CH_ENUM_BODY_IMPL(enum_name, __logic_const_type__) \
    CH_ENUM_WRITABLE_IMPL(enum_name, __logic_const_type__) \
    CH_LOGIC_READONLY_INTERFACE(enum_name) \
    CH_LOGIC_WRITABLE_INTERFACE(enum_name) \
    CH_ENUM_LOGIC_FRIENDS_IMPL(enum_name) \
  }

#define CH_ENUM(name, size, body) \
  CH_ENUM_IMPL(name, size, CH_REM body)
