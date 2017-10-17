#pragma once

#include "bit.h"

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_SCALAR_IMPL(enum_name, value_name, size) \
  class enum_name : public ch::internal::ch_scalar<size> { \
  public: \
    using base = ch::internal::ch_scalar<size>; \
    using traits = ch::internal::scalar_traits<enum_name, value_name>; \
    enum_name(const ch::internal::bytes_store& store = ch::internal::bytes_store(size)) : base(store) {} \
    enum_name(const enum_name& __rhs__) : base(__rhs__) {} \
    enum_name(enum_name&& __rhs__) : base(std::move(__rhs__)) {} \
    enum_name(enum_type __rhs__) : base(__rhs__) {} \
    enum_name& operator=(const enum_name& __rhs__) { \
      base::operator=(__rhs__); \
      return *this; \
    } \
    enum_name& operator=(enum_name&& __rhs__) { \
      base::operator=(std::move(__rhs__)); \
      return *this; \
    } \
    enum_name& operator=(enum_type __rhs__) { \
      base::operator=(__rhs__); \
      return *this; \
    } \
  }

#define CH_ENUM_BODY_IMPL(enum_name, assignment_body) \
  enum_name() {} \
  enum_name(const enum_name& __rhs__) : base(__rhs__) {} \
  enum_name(enum_name&& __rhs__) : base(std::move(__rhs__)) {} \
  enum_name(enum_type __rhs__) : base(__rhs__) {} \
  assignment_body(enum_name) \
  const auto clone() const { \
    return traits::value_type(base::clone()); \
  } \
protected: \
  enum_name(const base& __rhs__) : base(__rhs__) {} \
  friend const auto ch_reg(const enum_name& next, const enum_name& init) { \
    return ch::internal::ch_reg(next, init); \
  } \
  friend const auto ch_reg(const enum_name& next) { \
    return ch::internal::ch_reg(next); \
  }

#define CH_ENUM_READONLY_IMPL(enum_name) \
  CH_BIT_READONLY_INTERFACE(enum_name)

#define CH_ENUM_WRITABLE_IMPL(enum_name) \
  enum_name(const __const_type__& __rhs__) \
    : enum_name(reinterpret_cast<const base&>(__rhs__)) {} \
  enum_name& operator=(const enum_name& __rhs__) { \
    base::operator=(__rhs__); \
    return *this; \
  } \
  enum_name& operator=(enum_name&& __rhs__) { \
    base::operator=(std::move(__rhs__)); \
    return *this; \
  } \
  enum_name& operator=(enum_type __rhs__) { \
    base::operator=(__rhs__); \
    return *this; \
  } \
  CH_BIT_WRITABLE_INTERFACE(enum_name)

#define CH_ENUM_IMPL(enum_name, size, ...) \
  class enum_name : public ch::internal::ch_bit<size> { \
  public: \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __MAX_VALUE__ \
    }; \
    static_assert(ilog2(__MAX_VALUE__) <= size, "enum size mismatch"); \
  protected: \
    CH_ENUM_SCALAR_IMPL(__scalar_type__, enum_name, size); \
    class __const_type__ : public ch::internal::const_bit<size> { \
    public: \
      using base = ch::internal::const_bit<size>; \
      using traits = ch::internal::logic_traits<__const_type__, __const_type__, enum_name, __scalar_type__>; \
      CH_ENUM_BODY_IMPL(__const_type__, CH_ENUM_READONLY_IMPL) \
    }; \
  public: \
    using base = ch::internal::ch_bit<size>; \
    using traits = ch::internal::logic_traits<enum_name, __const_type__, enum_name, __scalar_type__>; \
    CH_ENUM_BODY_IMPL(enum_name, CH_ENUM_WRITABLE_IMPL) \
  }

#define CH_ENUM(name, size, body) \
  CH_ENUM_IMPL(name, size, CH_REM body)
