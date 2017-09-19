#pragma once

#include "bit.h"
#include "bus.h"

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_BUS_IMPL(name, size) \
  public: \
    using base   = cash::internal::ch_bus<size>; \
    using data_t = cash::internal::snode; \
    name() {} \
    name(const name& e) : base(e) {} \
    name(name&& e) : base(std::move(e)) {} \
    name(enum_type e) : base(static_cast<int>(e)) {} \
    name& operator=(const name& e) { \
      base::operator=(e); \
      return *this; \
    } \
    name& operator=(name&& e) { \
      base::operator=(std::move(e)); \
      return *this; \
    }

#define CH_ENUM_BODY_IMPL(name, const_name, bus_name, base_name, size, assignment_body) \
  public: \
    using base = cash::internal::base_name<size>; \
    using data_t  = cash::internal::lnode; \
    using value_t = name; \
    using const_t = __const_type__; \
    using bus_t   = __bus_type__; \
    name() {} \
    name(const name& e) : base(e) {} \
    name(name&& e) : base(std::move(e)) {} \
    name(enum_type e) : base(static_cast<int>(e)) {} \
    assignment_body(name) \
    name clone() const { \
      return base::clone(); \
    } \
  protected: \
    name(const base& b) : base(b) {} \
    friend name ch_reg(const name& next, const name& init) { \
      return cash::internal::ch_reg(next, init); \
    } \
    friend name ch_reg(const name& next) { \
      return cash::internal::ch_reg(next); \
    }

#define CH_ENUM_IMPL(name, size, ...) \
  class name : public cash::internal::ch_bit<size> { \
  public: \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __MAX_VALUE__ \
    }; \
    static_assert(ilog2(__MAX_VALUE__) <= size, "enum size mismatch"); \
  protected: \
    class __bus_type__ : public cash::internal::ch_bus<size> { \
      CH_ENUM_BUS_IMPL(__bus_type__, size) \
    }; \
    class __const_type__ : public cash::internal::const_bit<size> { \
      CH_ENUM_BODY_IMPL(__const_type__, __const_type__, __bus_type__, const_bit, size, CH_ENUM_NOASSIGN_IMPL) \
    }; \
    CH_ENUM_BODY_IMPL(name, __const_type__, __bus_type__, ch_bit, size,CH_ENUM_ASSIGN_IMPL) \
  }

#define CH_ENUM_NOASSIGN_IMPL(name)

#define CH_ENUM_ASSIGN_IMPL(name) \
  name& operator=(const name& e) { \
    base::operator=(e); \
    return *this; \
  } \
  name& operator=(name&& e) { \
    base::operator=(std::move(e)); \
    return *this; \
  }

#define CH_ENUM(name, size, body) \
  CH_ENUM_IMPL(name, size, CH_REM body)
