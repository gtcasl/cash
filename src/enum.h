#pragma once

#include "bit.h"
#include "bus.h"

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_BUS_IMPL(name, size) \
  class name : public cash::internal::ch_bus<size> { \
    public: \
      using base   = cash::internal::ch_bus<size>; \
      using data_t = typename base::data_t; \
      name() {} \
      name(const name& __rhs__) : base(__rhs__) {} \
      name(name&& __rhs__) : base(std::move(__rhs__)) {} \
      name(enum_type __rhs__) : base(__rhs__) {} \
      name& operator=(const name& __rhs__) { \
        base::operator=(__rhs__); \
        return *this; \
      } \
      name& operator=(name&& __rhs__) { \
        base::operator=(std::move(__rhs__)); \
        return *this; \
      } \
      name& operator=(enum_type __rhs__) { \
        base::operator=(__rhs__); \
        return *this; \
      } \
    }

#define CH_ENUM_BODY_IMPL(name, value_name, const_name, bus_name, base_name, size, assignment_body) \
  public: \
    using base = cash::internal::base_name<size>; \
    using data_t  = typename base::data_t; \
    using value_t = value_name; \
    using const_t = const_name; \
    using bus_t   = bus_name; \
    name() {} \
    name(const name& __rhs__) : base(__rhs__) {} \
    name(name&& __rhs__) : base(std::move(__rhs__)) {} \
    name(enum_type __rhs__) : base(__rhs__) {} \
    assignment_body(name) \
    const auto clone() const { \
      return value_t(base::clone()); \
    } \
  protected: \
    name(const base& __rhs__) : base(__rhs__) {} \
    template <typename __T__> friend const auto cash::internal::make_type(const cash::internal::lnode&); \
    friend name ch_reg(const name& next, const name& init) { \
      return cash::internal::ch_reg(next, init); \
    } \
    friend name ch_reg(const name& next) { \
      return cash::internal::ch_reg(next); \
    }

#define CH_ENUM_READONLY_IMPL(name) \
  CH_BIT_READONLY_INTERFACE(name)

#define CH_ENUM_WRITABLE_IMPL(name) \
  name& operator=(const name& __rhs__) { \
    base::operator=(__rhs__); \
    return *this; \
  } \
  name& operator=(name&& __rhs__) { \
    base::operator=(std::move(__rhs__)); \
    return *this; \
  } \
  name& operator=(enum_type __rhs__) { \
    base::operator=(__rhs__); \
    return *this; \
  } \
  CH_BIT_WRITABLE_INTERFACE(name)

#define CH_ENUM_IMPL(name, size, ...) \
  class name : public cash::internal::ch_bit<size> { \
  public: \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __MAX_VALUE__ \
    }; \
    static_assert(ilog2(__MAX_VALUE__) <= size, "enum size mismatch"); \
  protected: \
    CH_ENUM_BUS_IMPL(__bus_type__, size); \
    class __const_type__ : public cash::internal::const_bit<size> { \
      CH_ENUM_BODY_IMPL(__const_type__, name, __const_type__, __bus_type__, const_bit, size, CH_ENUM_READONLY_IMPL) \
    }; \
    CH_ENUM_BODY_IMPL(name, name, __const_type__, __bus_type__, ch_bit, size,CH_ENUM_WRITABLE_IMPL) \
  }

#define CH_ENUM(name, size, body) \
  CH_ENUM_IMPL(name, size, CH_REM body)
