#pragma once

#include "bitv.h"
#include "bus.h"

namespace chdl_internal {

#define CHDL_STRUCT_SIZE(i, x) \
  CHDL_PAIR_L(x)::bit_count

#define CHDL_STRUCT_FIELD(i, x) \
  CHDL_PAIR(x)

#define CHDL_STRUCT_BUS_FIELD(i, x) \
  typename CHDL_PAIR_L(x)::bus_type CHDL_PAIR_R(x)

#define CHDL_STRUCT_READ(i, x) \
  if (offset < CHDL_PAIR_L(x)::bit_count) { \
    size_t len = std::min<size_t>(length, CHDL_PAIR_L(x)::bit_count - offset); \
    read_data(CHDL_PAIR_R(x), out, offset, len); \
    length -= len; \
    if (length == 0) \
      return; \
    offset = CHDL_PAIR_L(x)::bit_count; \
  } \
  offset -= CHDL_PAIR_L(x)::bit_count
          
#define CHDL_STRUCT_WRITE(i, x) \
  if (dst_offset < CHDL_PAIR_L(x)::bit_count) { \
    size_t len = std::min<size_t>(src_length, CHDL_PAIR_L(x)::bit_count - dst_offset); \
    write_data(CHDL_PAIR_R(x), dst_offset, src, src_offset, len); \
    src_length -= len; \
    if (src_length == 0) \
      return; \
    src_offset += len; \
    dst_offset = CHDL_PAIR_L(x)::bit_count; \
  } \
  dst_offset -= CHDL_PAIR_L(x)::bit_count

#define CHDL_UNION_READ(i, x) \
  if (offset < CHDL_PAIR_L(x)::bit_count) { \
    size_t len = std::min<size_t>(length, CHDL_PAIR_L(x)::bit_count - offset); \
    read_data(CHDL_PAIR_R(x), out, offset, len); \
    length -= len; \
    if (length == 0) \
      return; \
    offset += len; \
  }
          
#define CHDL_UNION_WRITE(i, x) \
  if (dst_offset < CHDL_PAIR_L(x)::bit_count) { \
    size_t len = std::min<size_t>(src_length, CHDL_PAIR_L(x)::bit_count - dst_offset); \
    write_data(CHDL_PAIR_R(x), dst_offset, src, src_offset, len); \
  }

#define CHDL_STRUCT_IMPL(...) \
  public chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)> { \
    using base = chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    typedef typename base::data_type data_type; \
    typedef base self; \
    struct __bus_type : public chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)> { \
      using base = chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)>; \
      using base::operator=; \
      typedef typename base::data_type data_type; \
      typedef __bus_type bus_type; \
      typedef self logic_type; \
      CHDL_FOR_EACH(CHDL_STRUCT_BUS_FIELD, CHDL_SEMICOLON, __VA_ARGS__); \
      void read(std::vector< chdl_internal::partition<data_type> >& out, size_t offset, size_t length) const override { \
        CHDL_FOR_EACH(CHDL_STRUCT_READ, CHDL_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
      void write(size_t dst_offset, const std::vector< chdl_internal::partition<data_type> >& src, size_t src_offset, size_t src_length) override { \
        CHDL_FOR_EACH(CHDL_STRUCT_WRITE, CHDL_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
    }; \
    typedef self logic_type; \
    typedef __bus_type bus_type; \
    CHDL_FOR_EACH(CHDL_STRUCT_FIELD, CHDL_SEMICOLON, __VA_ARGS__); \
    void read(std::vector< chdl_internal::partition<data_type> >& out, size_t offset, size_t length) const override { \
      CHDL_FOR_EACH(CHDL_STRUCT_READ, CHDL_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
    void write(size_t dst_offset, const std::vector< chdl_internal::partition<data_type> >& src, size_t src_offset, size_t src_length) override { \
      CHDL_FOR_EACH(CHDL_STRUCT_WRITE, CHDL_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
  }

#define CHDL_UNION_IMPL(...) \
  public chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)> { \
    using base = chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    typedef typename base::data_type data_type; \
    typedef base self; \
    struct __bus_type : public chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)> { \
      using base = chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_PLUS, __VA_ARGS__)>; \
      using base::operator=; \
      typedef __bus_type bus_type; \
      typedef self logic_type; \
      typedef typename base::data_type data_type; \
      CHDL_FOR_EACH(CHDL_STRUCT_BUS_FIELD, CHDL_SEMICOLON, __VA_ARGS__); \
      void read(std::vector< chdl_internal::partition<data_type> >& out, size_t offset, size_t length) const override { \
        CHDL_FOR_EACH(CHDL_UNION_READ, CHDL_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
      void write(size_t dst_offset, const std::vector< chdl_internal::partition<data_type> >& src, size_t src_offset, size_t src_length) override { \
        CHDL_FOR_EACH(CHDL_UNION_WRITE, CHDL_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
    }; \
    typedef self logic_type; \
    typedef __bus_type bus_type; \
    CHDL_FOR_EACH(CHDL_STRUCT_FIELD, CHDL_SEMICOLON, __VA_ARGS__); \
    void read(std::vector< chdl_internal::partition<data_type> >& out, size_t offset, size_t length) const override { \
      CHDL_FOR_EACH(CHDL_UNION_READ, CHDL_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
    void write(size_t dst_offset, const std::vector< chdl_internal::partition<data_type> >& src, size_t src_offset, size_t src_length) override { \
      CHDL_FOR_EACH(CHDL_UNION_WRITE, CHDL_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
  }

#define CHDL_STRUCT(name) \
  struct name : CHDL_STRUCT_IMPL

#define CHDL_UNION(name) \
  struct name : CHDL_UNION_IMPL
  
}
