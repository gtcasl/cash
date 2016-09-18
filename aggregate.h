#pragma once

#include "bitv.h"

namespace chdl_internal {

#define CHDL_STRUCT_SIZE(i, x) CHDL_PAIR_L(x)::bit_count

#define CHDL_STRUCT_FIELD(i, x) CHDL_PAIR(x)

#define CHDL_STRUCT_GET(i, x) \
  if (index < CHDL_PAIR_L(x)::bit_count) \
    return chdl_internal::ch_bitbase_indexer<CHDL_PAIR_L(x)>::get(CHDL_PAIR_R(x), index); \
  index -= CHDL_PAIR_L(x)::bit_count

#define CHDL_STRUCT_BUS_FIELD(i, x) typename CHDL_PAIR_L(x)::bus_type CHDL_PAIR_R(x)

#define CHDL_STRUCT_BUS_GET(i, x) \
  if (index < CHDL_PAIR_L(x)::bit_count) \
    return chdl_internal::ch_sigbase_indexer<typename CHDL_PAIR_L(x)::bus_type>::get(CHDL_PAIR_R(x), index); \
  index -= CHDL_PAIR_L(x)::bit_count

#define CHDL_STRUCT_SEMICOLON() ;
#define CHDL_STRUCT_PLUS() +

#define CHDL_STRUCT_IMPL(...) \
  public chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)> { \
    using base = chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    typedef typename base::value_type value_type; \
    struct bus_type : public chdl_internal::ch_sigbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)> { \
      using base = chdl_internal::ch_sigbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)>; \
      using base::operator=; \
      typedef typename base::value_type value_type; \
      CHDL_FOR_EACH(CHDL_STRUCT_BUS_FIELD, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
      virtual const chdl_internal::ch_signal& get(size_t index) const { \
        CHDL_FOR_EACH(CHDL_STRUCT_BUS_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
      virtual chdl_internal::ch_signal& get(size_t index) { \
        CHDL_FOR_EACH(CHDL_STRUCT_BUS_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
    }; \
    CHDL_FOR_EACH(CHDL_STRUCT_FIELD, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
    virtual const chdl_internal::ch_logic& get(size_t index) const { \
      CHDL_FOR_EACH(CHDL_STRUCT_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
    virtual chdl_internal::ch_logic& get(size_t index) { \
      CHDL_FOR_EACH(CHDL_STRUCT_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
  }

#define CHDL_UNION_IMPL(...) \
  public chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)> { \
    using base = chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    typedef typename base::value_type value_type; \
    struct bus_type : public chdl_internal::ch_sigbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)> { \
      using base = chdl_internal::ch_sigbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_STRUCT_PLUS, __VA_ARGS__)>; \
      using base::operator=; \
      typedef typename base::value_type value_type; \
      CHDL_FOR_EACH(CHDL_STRUCT_BUS_FIELD, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
      virtual const chdl_internal::ch_signal& get(size_t index) const { \
        CHDL_FOR_EACH(CHDL_STRUCT_BUS_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
      virtual chdl_internal::ch_signal& get(size_t index) { \
        CHDL_FOR_EACH(CHDL_STRUCT_BUS_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
        CHDL_ABORT("invalid subscript index"); \
      } \
    }; \
    CHDL_FOR_EACH(CHDL_STRUCT_FIELD, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
    virtual const chdl_internal::ch_logic& get(size_t index) const { \
      CHDL_FOR_EACH(CHDL_STRUCT_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
    virtual chdl_internal::ch_logic& get(size_t index) { \
      CHDL_FOR_EACH(CHDL_STRUCT_GET, CHDL_STRUCT_SEMICOLON, __VA_ARGS__); \
      CHDL_ABORT("invalid subscript index"); \
    } \
  }

#define CHDL_STRUCT(name) struct name : CHDL_STRUCT_IMPL

#define CHDL_UNION(name) struct name : CHDL_UNION_IMPL
  
}
