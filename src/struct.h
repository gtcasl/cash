#pragma once

#include "bit.h"
#include "bus.h"

#define CH_STRUCT_SIZE(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_STRUCT_FIELD(i, x) \
  typename CH_PAIR_L(x)::value_type CH_PAIR_R(x)

#define CH_STRUCT_BUS_FIELD(i, x) \
  typename CH_PAIR_L(x)::value_type::bus_type CH_PAIR_R(x)

#define CH_STRUCT_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_STRUCT_FIELD_CTOR_TMPL(i, x) \
  typename __T##i

#define CH_STRUCT_FIELD_CTOR_REQUIRES(i, x) \
  CH_REQUIRES(cash::internal::is_cast_convertible<__T##i, typename CH_PAIR_L(x)::value_type>::value)

#define CH_STRUCT_FIELD_CTOR_ARGS(i, x) \
  const __T##i& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_FIELD_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(CH_CONCAT(_,CH_PAIR_R(x)))

#define CH_STRUCT_ASSIGN(i, x) \
  this->CH_PAIR_R(x) = __rhs__.CH_PAIR_R(x)

#define CH_STRUCT_CLONE(i, x) \
  CH_PAIR_R(x).clone()

#define CH_STRUCT_READ(i, x) \
  if (__offset__ < CH_PAIR_L(x)::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, CH_PAIR_L(x)::bitcount - __offset__); \
    cash::internal::read_data(CH_PAIR_R(x), __inout__, __offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __offset__ -= CH_PAIR_L(x)::bitcount
          
#define CH_STRUCT_WRITE(i, x) \
  if (__dst_offset__ < CH_PAIR_L(x)::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, CH_PAIR_L(x)::bitcount - __dst_offset__); \
    cash::internal::write_data(CH_PAIR_R(x), __dst_offset__, __in__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __src_offset__ += __len__; \
    __dst_offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __dst_offset__ -= CH_PAIR_L(x)::bitcount

#define CH_STRUCT_IMPL(name, ...) \
  class name : public cash::internal::ch_bitbase<CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)> { \
  public:\
    using base = cash::internal::ch_bitbase<CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    using data_type = typename base::data_type; \
    using value_type = name; \
    using const_type = const name; \
    class bus_type : public cash::internal::ch_busbase<base::bitcount> { \
    public: \
      using base = cash::internal::ch_busbase<name::base::bitcount>; \
      using base::operator=; \
      using data_type = typename base::data_type; \
      using value_type = bus_type; \
      using const_type = const bus_type; \
      bus_type() {} \
      bus_type(const bus_type& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const base& __rhs__) { base::operator=(__rhs__); } \
      template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
                CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
      explicit bus_type(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
        : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      explicit bus_type(bool __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(char __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(int8_t __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(uint8_t __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(int16_t __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(uint16_t __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(int32_t __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(uint32_t __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(int64_t __rhs__) { base::operator=(__rhs__); } \
      explicit bus_type(uint64_t __rhs__) { base::operator=(__rhs__); } \
      bus_type& operator=(const bus_type& __rhs__) { \
        CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
        return *this; \
      } \
      CH_FOR_EACH(CH_STRUCT_BUS_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    protected: \
      void read_data(data_type& __inout__, size_t __offset__, size_t __length__) const override { \
        CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
        CH_ABORT("invalid subscript index"); \
      } \
      void write_data(size_t __dst_offset__, const data_type& __in__, size_t __src_offset__, size_t __length__) override { \
        CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
        CH_ABORT("invalid subscript index"); \
      } \
    };\
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& __rhs__) { base::operator=(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    explicit name(bool __rhs__) { base::operator=(__rhs__); } \
    explicit name(char __rhs__) { base::operator=(__rhs__); } \
    explicit name(int8_t __rhs__) { base::operator=(__rhs__); } \
    explicit name(uint8_t __rhs__) { base::operator=(__rhs__); } \
    explicit name(int16_t __rhs__) { base::operator=(__rhs__); } \
    explicit name(uint16_t __rhs__) { base::operator=(__rhs__); } \
    explicit name(int32_t __rhs__) { base::operator=(__rhs__); } \
    explicit name(uint32_t __rhs__) { base::operator=(__rhs__); } \
    explicit name(int64_t __rhs__) { base::operator=(__rhs__); } \
    explicit name(uint64_t __rhs__) { base::operator=(__rhs__); } \
    name& operator=(const name& __rhs__) { \
      CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_FOR_EACH(CH_STRUCT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    name clone() const { \
      return name(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
  protected: \
    void read_data(data_type& __inout__, size_t __offset__, size_t __length__) const override { \
      CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    void write_data(size_t __dst_offset__, const data_type& __in__, size_t __src_offset__, size_t __length__) override { \
      CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
  public:

#define CH_STRUCT(name, body, ...) CH_STRUCT_IMPL(name, CH_REM body) __VA_ARGS__ }
