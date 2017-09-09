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

#define CH_STRUCT_FIELD_TMPL(i, x) \
  typename _T##i

#define CH_STRUCT_FIELD_REQUIRES(i, x) \
  CH_REQUIRES(cash::internal::is_weak_convertible<_T##i, CH_PAIR_L(x)>::value)

#define CH_STRUCT_CTOR_FIELD(i, x) \
  const _T##i& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_CTOR_FIELD_INIT(i, x) \
  CH_PAIR_R(x)(CH_CONCAT(_,CH_PAIR_R(x)))

#define CH_STRUCT_ASSIGN(i, x) \
  this->CH_PAIR_R(x) = rhs.CH_PAIR_R(x)

#define CH_STRUCT_CLONE(i, x) \
  CH_PAIR_R(x).clone()

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
    size_t len = std::min<size_t>(length, CH_PAIR_L(x)::bitcount - dst_offset); \
    cash::internal::write_data(CH_PAIR_R(x), dst_offset, in, src_offset, len); \
    length -= len; \
    if (0 == length) \
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
    class bus_type : public cash::internal::ch_busbase<base::bitcount> { \
    public: \
      using base = cash::internal::ch_busbase<name::base::bitcount>; \
      using base::operator=; \
      using data_type = typename base::data_type; \
      bus_type() {} \
      bus_type(const bus_type& rhs) : CH_FOR_EACH(CH_STRUCT_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const base& rhs) { base::operator=(rhs); } \
      template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
                CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
      explicit bus_type(CH_REVERSE_FOR_EACH(CH_STRUCT_CTOR_FIELD, CH_SEP_COMMA, __VA_ARGS__)) \
        : CH_FOR_EACH(CH_STRUCT_CTOR_FIELD_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
      explicit bus_type(bool rhs) { base::operator=(rhs); } \
      explicit bus_type(char rhs) { base::operator=(rhs); } \
      explicit bus_type(int8_t rhs) { base::operator=(rhs); } \
      explicit bus_type(uint8_t rhs) { base::operator=(rhs); } \
      explicit bus_type(int16_t rhs) { base::operator=(rhs); } \
      explicit bus_type(uint16_t rhs) { base::operator=(rhs); } \
      explicit bus_type(int32_t rhs) { base::operator=(rhs); } \
      explicit bus_type(uint32_t rhs) { base::operator=(rhs); } \
      explicit bus_type(int64_t rhs) { base::operator=(rhs); } \
      explicit bus_type(uint64_t rhs) { base::operator=(rhs); } \
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
      void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override { \
        CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
        CH_ABORT("invalid subscript index"); \
      } \
    };\
    name() {} \
    name(const name& rhs) : CH_FOR_EACH(CH_STRUCT_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& rhs) { base::operator=(rhs); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_CTOR_FIELD, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_CTOR_FIELD_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
    explicit name(bool rhs) { base::operator=(rhs); } \
    explicit name(char rhs) { base::operator=(rhs); } \
    explicit name(int8_t rhs) { base::operator=(rhs); } \
    explicit name(uint8_t rhs) { base::operator=(rhs); } \
    explicit name(int16_t rhs) { base::operator=(rhs); } \
    explicit name(uint16_t rhs) { base::operator=(rhs); } \
    explicit name(int32_t rhs) { base::operator=(rhs); } \
    explicit name(uint32_t rhs) { base::operator=(rhs); } \
    explicit name(int64_t rhs) { base::operator=(rhs); } \
    explicit name(uint64_t rhs) { base::operator=(rhs); } \
    name& operator=(const name& rhs) { \
      CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_FOR_EACH(CH_STRUCT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    name clone() const { \
      return name(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
  protected: \
    void read_data(data_type& inout, size_t offset, size_t length) const override { \
      CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override { \
      CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
  public:

#define CH_STRUCT(name, body, ...) CH_STRUCT_IMPL(name, CH_REM body) __VA_ARGS__ }
