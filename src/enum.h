#pragma once

#include "bit.h"
#include "bus.h"

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_BUS_IMPL(name, size, ...) \
  namespace cash { namespace internal { \
    template <> \
    struct traits<name> { \
      static constexpr unsigned bitcount = size; \
      static constexpr bool readonly = false; \
      using data_type  = snode; \
      using value_type = name; \
      using const_type = name; \
      using bus_type   = name; \
    }; \
  } } \
  class name : public cash::internal::ch_bus<size> { \
  public: \
    using base = cash::internal::ch_bus<size>; \
    enum enum_type { \
      CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
      , __MAX_VALUE__ \
    }; \
    static_assert(ilog2(__MAX_VALUE__) <= size, "enum size mismatch"); \
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
    } \
  } \

#define CH_ENUM_IMPL(name, const_name, bus_name, base_name, size, is_readonly, ...) \
  namespace cash { namespace internal { \
    template <> \
    struct traits<name> { \
      static constexpr unsigned bitcount = size; \
      static constexpr bool readonly = is_readonly; \
      using data_type  = lnode; \
      using value_type = name; \
      using const_type = const_name; \
      using bus_type   = bus_name; \
    }; \
  } } \
  class name : public cash::internal::base_name<size> { \
  public: \
    using base = cash::internal::base_name<size>; \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __MAX_VALUE__ \
    }; \
    static_assert(ilog2(__MAX_VALUE__) <= size, "enum size mismatch"); \
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
    } \
    name clone() const { \
      return this->clone(); \
    } \
  protected: \
    name(const base& b) : base(b) {} \
    friend name ch_reg(const name& next, const name& init) { \
      return cash::internal::ch_reg(next, init); \
    } \
    friend name ch_reg(const name& next) { \
      return cash::internal::ch_reg(next); \
    } \
  }
  
#define CH_ENUM(name, size, body) \
  class name; \
  class CH_UNAME(const, name); \
  class CH_UNAME(bus, name); \
  CH_ENUM_BUS_IMPL(CH_UNAME(bus, name), size, CH_REM body); \
  CH_ENUM_IMPL(name, CH_UNAME(const, name), CH_UNAME(bus, name), ch_bit, size, false, CH_REM body); \
  CH_ENUM_IMPL(CH_UNAME(const, name), CH_UNAME(const, name), CH_UNAME(bus, name), const_bit, size, true, CH_REM body)
