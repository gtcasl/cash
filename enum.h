#pragma once

#include "bitv.h"
#include "bus.h"

#define CHDL_ENUM_FIELD(i, x) \
  x

#define CHDL_ENUM_IMPL(name, size, ...) \
  class name : public chdl_internal::ch_bitv<size> { \
  public: \
    using base = chdl_internal::ch_bitv<size>; \
    using base::operator=; \
    using bitstream_type = typename base::bitstream_type; \
    enum enum_type { \
    CHDL_FOR_EACH(CHDL_ENUM_FIELD, CHDL_SEP_COMMA, __VA_ARGS__) \
    , __max_value__ \
    }; \
    static_assert(CLOG2(__max_value__) <= base::bit_count); \
    name() {} \
    name(const name& e) : base(e) {} \
    name(enum_type e) : base(e) {} \
    class bus_type : public chdl_internal::ch_bus<base::bit_count> { \
      public: \
        using base = chdl_internal::ch_bus<base::bit_count>; \
        using bitstream_type = typename base::bitstream_type; \
        bus_type() {} \
        bus_type(const bus_type& e) : base(e) {} \
        bus_type(enum_type e) : base(e) {} \
    }; \
  }

#define CHDL_ENUM(name, size, body) CHDL_ENUM_IMPL(name, size, CHDL_REM body)
