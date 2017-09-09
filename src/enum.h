#pragma once

#include "bit.h"
#include "bus.h"

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_IMPL(name, size, ...) \
  class name : public cash::internal::ch_bit<size> { \
  public: \
    using base = cash::internal::ch_bit<size>; \
    using data_type = typename base::data_type; \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __max_value__ \
    }; \
    static_assert(ilog2(__max_value__) <= base::bitcount, "enum size mismatch"); \
    class bus_type : public cash::internal::ch_bus<base::bitcount> { \
      public: \
        using base = cash::internal::ch_bus<name::base::bitcount>; \
        using data_type = typename base::data_type; \
        bus_type() {} \
        bus_type(const bus_type& e) : base(e) {} \
        bus_type(bus_type&& e) : base(std::move(e)) {} \
        bus_type(enum_type e) : base(e) {} \
        bus_type& operator=(const bus_type& e) { \
          base::operator=(e); \
          return *this; \
        } \
        bus_type& operator=(bus_type&& e) { \
          base::operator=(std::move(e)); \
          return *this; \
        } \
    }; \
    name() {} \
    name(const name& e) : base(e) {} \
    name(name&& e) : base(std::move(e)) {} \
    name(enum_type e) : base(e) {} \
    name& operator=(const name& e) { \
      base::operator=(e); \
      return *this; \
    } \
    name& operator=(name&& e) { \
      base::operator=(std::move(e)); \
      return *this; \
    } \
    name clone() const { \
      return this->clone(); \
    } \
  public:
  
#define CH_ENUM(name, size, body, ...) \
  CH_ENUM_IMPL(name, size, CH_REM body) __VA_ARGS__ }