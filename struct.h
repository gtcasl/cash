#pragma once

#include "bit.h"
#include "bus.h"

#define CHDL_STRUCT_SIZE(i, x) \
  CHDL_PAIR_L(x)::bit_count

#define CHDL_STRUCT_FIELD(i, x) \
  CHDL_PAIR(x)

#define CHDL_STRUCT_BUS_FIELD(i, x) \
  typename CHDL_PAIR_L(x)::bus_type CHDL_PAIR_R(x)

#define CHDL_STRUCT_CTOR_INIT(i, x) \
  CHDL_PAIR_R(x)(rhs.CHDL_PAIR_R(x))

#define CHDL_STRUCT_CTOR_ARG(i, x) \
  const CHDL_PAIR_L(x)& CHDL_CONCAT(CHDL_PAIR_R(x),_)

#define CHDL_STRUCT_BUS_CTOR_ARG(i, x) \
  const typename CHDL_PAIR_L(x)::bus_type& CHDL_CONCAT(CHDL_PAIR_R(x),_)

#define CHDL_STRUCT_CTOR_ARG_INIT(i, x) \
  CHDL_PAIR_R(x)(CHDL_CONCAT(CHDL_PAIR_R(x),_))

#define CHDL_STRUCT_ASSIGN(i, x) \
  this->CHDL_PAIR_R(x) = rhs.CHDL_PAIR_R(x)

#define CHDL_STRUCT_READ(i, x) \
  if (offset < CHDL_PAIR_L(x)::bit_count) { \
    size_t len = std::min<size_t>(length, CHDL_PAIR_L(x)::bit_count - offset); \
    read_data(CHDL_PAIR_R(x), inout, offset, len); \
    length -= len; \
    if (length == 0) \
      return; \
    offset = CHDL_PAIR_L(x)::bit_count; \
  } \
  offset -= CHDL_PAIR_L(x)::bit_count
          
#define CHDL_STRUCT_WRITE(i, x) \
  if (dst_offset < CHDL_PAIR_L(x)::bit_count) { \
    size_t len = std::min<size_t>(src_length, CHDL_PAIR_L(x)::bit_count - dst_offset); \
    write_data(CHDL_PAIR_R(x), dst_offset, in, src_offset, len); \
    src_length -= len; \
    if (src_length == 0) \
      return; \
    src_offset += len; \
    dst_offset = CHDL_PAIR_L(x)::bit_count; \
  } \
  dst_offset -= CHDL_PAIR_L(x)::bit_count


#define CHDL_STRUCT_IMPL(name, ...) \
  class name : public chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)> { \
  public:\
    using base = chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    using bitstream_type = typename base::bitstream_type; \
    class bus_type : public chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)> { \
    public: \
      using base = chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)>; \
      using base::operator=; \
      using bitstream_type = typename base::bitstream_type; \
      bus_type() {} \
      bus_type(const bus_type& rhs) : CHDL_FOR_EACH(CHDL_STRUCT_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(CHDL_REVERSE_FOR_EACH(CHDL_STRUCT_BUS_CTOR_ARG, CHDL_SEP_COMMA, __VA_ARGS__)) : CHDL_FOR_EACH(CHDL_STRUCT_CTOR_ARG_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const base& rhs) { base::operator=(rhs); } \
      bus_type& operator=(const bus_type& rhs) { \
        CHDL_FOR_EACH(CHDL_STRUCT_ASSIGN, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
        return *this; \
      } \
      CHDL_FOR_EACH(CHDL_STRUCT_BUS_FIELD, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
    protected: \
      void read(bitstream_type& inout, size_t offset, size_t length) const override { \
        CHDL_FOR_EACH(CHDL_STRUCT_READ, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
      void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override { \
        CHDL_FOR_EACH(CHDL_STRUCT_WRITE, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
    };\
    name() {} \
    name(const name& rhs) : CHDL_FOR_EACH(CHDL_STRUCT_CTOR_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
    name(CHDL_REVERSE_FOR_EACH(CHDL_STRUCT_CTOR_ARG, CHDL_SEP_COMMA, __VA_ARGS__)) : CHDL_FOR_EACH(CHDL_STRUCT_CTOR_ARG_INIT, CHDL_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& rhs) { base::operator=(rhs); } \
    name& operator=(const name& rhs) { \
      CHDL_FOR_EACH(CHDL_STRUCT_ASSIGN, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CHDL_FOR_EACH(CHDL_STRUCT_FIELD, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    void read(bitstream_type& inout, size_t offset, size_t length) const override { \
      CHDL_FOR_EACH(CHDL_STRUCT_READ, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
    void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) override { \
      CHDL_FOR_EACH(CHDL_STRUCT_WRITE, CHDL_SEP_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
  }

#define CHDL_STRUCT(name, body) CHDL_STRUCT_IMPL(name, CHDL_REM body)
