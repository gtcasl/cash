#pragma once

#include "bit.h"
#include "bus.h"

#define CH_ENUM_FIELD(i, x) \
  x

#define CH_ENUM_IMPL(name, size, ...) \
  class name : public cash_internal::ch_bit<size> { \
  public: \
    using base = cash_internal::ch_bit<size>; \
    using bitstream_type = typename base::bitstream_type; \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __max_value__ \
    }; \
    static_assert(CLOG2(__max_value__) <= base::bit_count, "enum size mismatch"); \
    name() {} \
    name(const name& e) : base(e) {} \
    name(enum_type e) : base(e) {} \
    class bus_type : public cash_internal::ch_bus<base::bit_count> { \
      public: \
        using base = cash_internal::ch_bus<base::bit_count>; \
        using bitstream_type = typename base::bitstream_type; \
        bus_type() {} \
        bus_type(const bus_type& e) : base(e) {} \
        bus_type(enum_type e) : base(e) {} \
    }; \
  private: \
    name(const base& b) : base(b) {} \
    friend name ch_reg(const name& next, const name& init) { \
      return cash_internal::ch_reg<size>(reinterpret_cast<const cash_internal::ch_bitbase<size>&>(next), \
                    reinterpret_cast<const cash_internal::ch_bitbase<size>&>(init)); \
    } \
    friend name ch_reg(const name& next) { \
      return cash_internal::ch_reg<size>(reinterpret_cast<const cash_internal::ch_bitbase<size>&>(next)); \
    } \
  public:
  
#define CH_ENUM(name, size, body, ...) CH_ENUM_IMPL(name, size, CH_REM body) __VA_ARGS__ }
