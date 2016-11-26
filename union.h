#pragma once

#include "bit.h"
#include "bus.h"

#define CHDL_UNION_SIZE(i, x) \
  CHDL_PAIR_L(x)::bit_count

#define CHDL_UNION_FIELD(i, x) \
  chdl_internal::slice_ref<base, CHDL_PAIR_L(x)::bit_count> CHDL_PAIR_R(x)

#define CHDL_UNION_CTOR_INIT(i, x) \
  CHDL_PAIR_R(x)(__m)

#define CHDL_UNION_IMPL(name, ...) \
  class name : public chdl_internal::ch_bitbase<std::max({CHDL_FOR_EACH(CHDL_UNION_SIZE, CHDL_SEP_COMMA, __VA_ARGS__)})> { \
  public:\
    using base = chdl_internal::ch_bitbase<std::max({CHDL_FOR_EACH(CHDL_UNION_SIZE, CHDL_SEP_COMMA, __VA_ARGS__)})>; \
    using base::operator=; \
    using bitstream_type = typename base::bitstream_type; \
    class bus_type : public chdl_internal::ch_busbase<std::max({CHDL_FOR_EACH(CHDL_UNION_SIZE, CHDL_SEP_COMMA, __VA_ARGS__)})> { \
    public: \
      using base = chdl_internal::ch_busbase<std::max({CHDL_FOR_EACH(CHDL_UNION_SIZE, CHDL_SEP_COMMA, __VA_ARGS__)})>; \
      using base::operator=; \
      using bitstream_type = typename base::bitstream_type; \
      bus_type() : CHDL_FOR_EACH(CHDL_UNION_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const bus_type& rhs) : CHDL_FOR_EACH(CHDL_UNION_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const base& rhs) : CHDL_FOR_EACH(CHDL_UNION_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
      bus_type& operator=(const bus_type& rhs) { \
        __m = rhs.__m; \
        return *this; \
      } \
      CHDL_FOR_EACH(CHDL_UNION_FIELD, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
    protected: \
      ch_bus<base::bit_count> __m; \
      void read(bitstream_type& inout, size_t offset, size_t length) const override { \
        read_data(__m, inout, offset, length); \
      } \
      void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override { \
        write_data(__m, dst_offset, in, src_offset, src_length); \
      } \
    };\
    name() : CHDL_FOR_EACH(CHDL_UNION_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
    name(const name& rhs) : CHDL_FOR_EACH(CHDL_UNION_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& rhs) : CHDL_FOR_EACH(CHDL_UNION_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
    name& operator=(const name& rhs) { \
      __m = rhs.__m; \
      return *this; \
    } \
    CHDL_FOR_EACH(CHDL_UNION_FIELD, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    ch_bit<base::bit_count> __m; \
    void read(bitstream_type& inout, size_t offset, size_t length) const override { \
      read_data(__m, inout, offset, length); \
    } \
    void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override { \
      write_data(__m, dst_offset, in, src_offset, src_length); \
    }

#define CHDL_UNION(name, body, ...) CHDL_UNION_IMPL(name, CHDL_REM body) __VA_ARGS__ }
