#pragma once

#include "bitv.h"
#include "bus.h"

#define CHDL_ENUM_FIELD(i, x) \
  x

#define CHDL_ENUM_IMPL(...) \
    enum enum_type { \
    CHDL_FOR_EACH(CHDL_ENUM_FIELD, CHDL_SEP_COMMA, __VA_ARGS__) \
    , __max_value__ \
    }; \
    class bus_type : public chdl_internal::ch_bus<base::bit_count> { \
      public: \
        using base = chdl_internal::ch_bus<base::bit_count>; \
        using bitstream_type = typename base::bitstream_type; \
        bus_type() {} \
        bus_type(const bus_type& e) : base(e) {} \
        bus_type(enum_type e) : base(e) {} \
    }; \
    static_assert(CLOG2(__max_value__) <= base::bit_count); \
    static constexpr unsigned type_check(unsigned e) { \
      assert(e < __max_value__); \
      return e; \
    } \
  }

#define CHDL_ENUM(name, size) \
  class name : public chdl_internal::ch_bitv<size> { \
  public: \
    using base = chdl_internal::ch_bitv<size>; \
    using bitstream_type = typename base::bitstream_type; \
    name() {} \
    name(const name& e) : base(e) {} \
    name(unsigned e) : base(type_check(e)) {} \
  CHDL_ENUM_IMPL
