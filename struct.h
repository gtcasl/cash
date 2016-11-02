#pragma once

#include "bitv.h"
#include "bus.h"

namespace chdl_internal {

template <typename Base>
class struct_stub : public Base {
public:
  using Base::operator=; \
  using bitstream_type = typename Base::bitstream_type;
  
  struct_stub& operator=(const struct_stub& rhs) {
    // the main purpose of this stub is for disabling the base class assignment operator
    // such that the auto-generated derived assignment operators do not call it
  }   
};

}

#define CHDL_STRUCT_SIZE(i, x) \
  CHDL_PAIR_L(x)::bit_count

#define CHDL_STRUCT_FIELD(i, x) \
  CHDL_PAIR(x)

#define CHDL_STRUCT_BUS_FIELD(i, x) \
  typename CHDL_PAIR_L(x)::bus_type CHDL_PAIR_R(x)

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

#define CHDL_STRUCT_IMPL(...) \
  public chdl_internal::struct_stub< chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)> > { \
  public:\
    using base = chdl_internal::struct_stub< chdl_internal::ch_bitbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)> >; \
    using base::operator=; \
    using bitstream_type = typename base::bitstream_type; \
    class bus_type : public chdl_internal::struct_stub< chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)> > { \
    public: \
      using base = chdl_internal::struct_stub< chdl_internal::ch_busbase<CHDL_FOR_EACH(CHDL_STRUCT_SIZE, CHDL_SEP_PLUS, __VA_ARGS__)> >; \
      using base::operator=; \
      using bitstream_type = typename base::bitstream_type; \
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

#define CHDL_STRUCT(name) class name : CHDL_STRUCT_IMPL
