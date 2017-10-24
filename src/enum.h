#pragma once

#include "bit.h"

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_SCALAR_IMPL(enum_name, value_name, size) \
  class enum_name : public ch::internal::ch_scalar<size> { \
  public: \
    using traits = ch::internal::scalar_traits<size, enum_name, value_name>; \
    using base = ch::internal::ch_scalar<size>; \
    enum_name(const ch::internal::scalar_buffer& buffer = ch::internal::scalar_buffer(size)) : base(buffer) {} \
    enum_name(const enum_name& rhs) : base(rhs) {} \
    enum_name(enum_name&& rhs) : base(std::move(rhs)) {} \
    enum_name(enum_type rhs) : base(rhs) {} \
    enum_name& operator=(const enum_name& rhs) { \
      base::operator=(rhs); \
      return *this; \
    } \
    enum_name& operator=(enum_name&& rhs) { \
      base::operator=(std::move(rhs)); \
      return *this; \
    } \
    enum_name& operator=(enum_type rhs) { \
      base::operator=(rhs); \
      return *this; \
    } \
    inline friend const auto operator==(const enum_name& lhs, const enum_name& rhs) { \
      return (lhs.asScalar() == rhs.asScalar()); \
    } \
    inline friend const auto operator!=(const enum_name& lhs, const enum_name& rhs) { \
      return (lhs.asScalar() != rhs.asScalar()); \
    } \
    CH_SCALAR_TYPE_INTERFACE(enum_name) \
  }

#define CH_ENUM_BODY_IMPL(enum_name, reverse_name, assignment_body) \
  enum_name(const ch::internal::bit_buffer& buffer = ch::internal::bit_buffer(traits::bitwidth)) : base(buffer) {} \
  enum_name(const enum_name& rhs) : base(rhs) {} \
  enum_name(enum_name&& rhs) : base(std::move(rhs)) {} \
  enum_name(const reverse_name& rhs) : base(rhs) {} \
  enum_name(enum_type rhs) : base(rhs) {} \
  assignment_body(enum_name) \
protected: \
  enum_name(const base& rhs) : base(rhs) {}

#define CH_ENUM_READONLY_IMPL(enum_name) \
  CH_BIT_READONLY_INTERFACE(enum_name) \
  const auto operator==(const enum_name& rhs) const { \
    return (this->asBits() == rhs.asBits()); \
  } \
  const auto operator!=(const enum_name& rhs) const { \
    return (this->asBits() != rhs.asBits()); \
  }

#define CH_ENUM_WRITABLE_IMPL(enum_name) \
  CH_BIT_READONLY_INTERFACE(enum_name) \
  CH_BIT_WRITABLE_INTERFACE(enum_name) \
  enum_name& operator=(const enum_name& rhs) { \
    base::operator=(rhs); \
    return *this; \
  } \
  enum_name& operator=(enum_name&& rhs) { \
    base::operator=(std::move(rhs)); \
    return *this; \
  } \
  enum_name& operator=(const __const_type__& rhs) { \
    base::operator=(rhs); \
    return *this; \
  } \
  enum_name& operator=(enum_type rhs) { \
    base::operator=(rhs); \
    return *this; \
  } \
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
  protected: \
    CH_ENUM_SCALAR_IMPL(__scalar_type__, enum_name, size); \
    using __self_type = enum_name; \
    class __const_type__ : public ch::internal::const_bit<size> { \
    public: \
      using traits = ch::internal::logic_traits<size, __const_type__, __const_type__, enum_name, __scalar_type__>; \
      using base = ch::internal::const_bit<size>; \
      CH_ENUM_BODY_IMPL(__const_type__, enum_name, CH_ENUM_READONLY_IMPL) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<size, enum_name, __const_type__, enum_name, __scalar_type__>; \
    using base = ch::internal::ch_bit<size>; \
    CH_ENUM_BODY_IMPL(enum_name, __const_type__, CH_ENUM_WRITABLE_IMPL) \
  }

#define CH_ENUM(name, size, body) \
  CH_ENUM_IMPL(name, size, CH_REM body)
