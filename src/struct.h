#pragma once

#include "bit.h"
#include "bus.h"

#define CH_STRUCT_SIZE(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_STRUCT_FIELD(i, x) \
  CH_PAIR(x)

#define CH_STRUCT_BUS_FIELD(i, x) \
  typename CH_PAIR_L(x)::bus_type CH_PAIR_R(x)

#define CH_STRUCT_CTOR_INIT(i, x) \
  CH_PAIR_R(x)(rhs.CH_PAIR_R(x))

#define CH_STRUCT_CTOR_ARG(i, x) \
  const CH_PAIR_L(x)& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_CLONE_ARG(i, x) \
  CH_PAIR_R(x).clone()

#define CH_STRUCT_BUS_CTOR_ARG(i, x) \
  const typename CH_PAIR_L(x)::bus_type& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_CTOR_ARG_INIT(i, x) \
  CH_PAIR_R(x)(CH_CONCAT(_,CH_PAIR_R(x)))

#define CH_STRUCT_ASSIGN(i, x) \
  this->CH_PAIR_R(x) = rhs.CH_PAIR_R(x)

#define CH_STRUCT_READ(i, x) \
  if (offset < CH_PAIR_L(x)::bitcount) { \
    size_t len = std::min<size_t>(length, CH_PAIR_L(x)::bitcount - offset); \
    cash::internal::read_data(CH_PAIR_R(x), inout, offset, len); \
    length -= len; \
    if (0 == length) \
      return; \
    offset = CH_PAIR_L(x)::bitcount; \
  } \
  offset -= CH_PAIR_L(x)::bitcount
          
#define CH_STRUCT_WRITE(i, x) \
  if (dst_offset < CH_PAIR_L(x)::bitcount) { \
    size_t len = std::min<size_t>(src_length, CH_PAIR_L(x)::bitcount - dst_offset); \
    cash::internal::write_data(CH_PAIR_R(x), dst_offset, in, src_offset, len); \
    src_length -= len; \
    if (0 == src_length) \
      return; \
    src_offset += len; \
    dst_offset = CH_PAIR_L(x)::bitcount; \
  } \
  dst_offset -= CH_PAIR_L(x)::bitcount

#define CH_STRUCT_IMPL(name, ...) \
  class name : public cash::internal::ch_bitbase<CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)> { \
  public:\
    using base = cash::internal::ch_bitbase<CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    using data_type = typename base::data_type; \
    class bus_type : public cash::internal::ch_busbase<CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)> { \
    public: \
      using base = cash::internal::ch_busbase<CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)>; \
      using base::operator=; \
      using data_type = typename base::data_type; \
      bus_type() {} \
      bus_type(const bus_type& rhs) : CH_FOR_EACH(CH_STRUCT_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(CH_REVERSE_FOR_EACH(CH_STRUCT_BUS_CTOR_ARG, CH_SEP_COMMA, __VA_ARGS__)) \
        : CH_FOR_EACH(CH_STRUCT_CTOR_ARG_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const base& rhs) { base::operator=(rhs); } \
      bus_type& operator=(const bus_type& rhs) { \
        CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
        return *this; \
      } \
      CH_FOR_EACH(CH_STRUCT_BUS_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    protected: \
      void read_data(data_type& inout, size_t offset, size_t length) const override { \
        CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
        CH_ABORT("invalid subscript index"); \
      } \
      void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override { \
        CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
        CH_ABORT("invalid subscript index"); \
      } \
    };\
    name() {} \
    name(const name& rhs) : CH_FOR_EACH(CH_STRUCT_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(CH_REVERSE_FOR_EACH(CH_STRUCT_CTOR_ARG, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_CTOR_ARG_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& rhs) { base::operator=(rhs); } \
    name& operator=(const name& rhs) { \
      CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_FOR_EACH(CH_STRUCT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    name clone() const { \
      return name(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE_ARG, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
  protected: \
    void read_data(data_type& inout, size_t offset, size_t length) const override { \
      CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) override { \
      CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
  public:

#define CH_STRUCT(name, body, ...) CH_STRUCT_IMPL(name, CH_REM body) __VA_ARGS__ }
