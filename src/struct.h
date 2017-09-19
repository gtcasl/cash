#pragma once

#include "bit.h"
#include "bus.h"

#define CH_STRUCT_SIZE(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_STRUCT_FIELD(i, x) \
  typename CH_PAIR_L(x)::value_t CH_PAIR_R(x)

#define CH_STRUCT_BUS_FIELD(i, x) \
  typename CH_PAIR_L(x)::bus_t CH_PAIR_R(x)

#define CH_STRUCT_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_STRUCT_FIELD_CTOR_TMPL(i, x) \
  typename __T##i

#define CH_STRUCT_FIELD_CTOR_REQUIRES(i, x) \
  CH_REQUIRES(cash::internal::is_cast_convertible<__T##i, typename CH_PAIR_L(x)::value_t>::value)

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

#define CH_STRUCT_BUS_IMPL(name, ...) \
  public: \
    using base = cash::internal::ch_busbase<name, CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)>; \
    using base::operator=; \
    using data_t = cash::internal::snode; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& __rhs__) { base::operator=(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    template <typename __T__, CH_REQUIRES(cash::internal::is_scalar<__T__>::value)> \
    explicit name(__T__ __rhs__) { base::operator=(__rhs__); } \
    name& operator=(const name& __rhs__) { \
      CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_FOR_EACH(CH_STRUCT_BUS_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    void read_data(cash::internal::nodelist<data_t>& __inout__, size_t __offset__, size_t __length__) const { \
      CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_t>& __in__, size_t __src_offset__, size_t __length__) { \
      CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    template <typename __T__, typename __D__, unsigned __N__, bool __R__> friend class cash::internal::typebase;

#define CH_STRUCT_BODY_IMPL(name, const_name, bus_name, is_readonly, assignment_body, ...) \
  public:\
    using base = typename cash::internal::ch_bitbase<name, CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__), is_readonly>; \
    using base::operator=; \
    using data_t  = cash::internal::lnode; \
    using value_t = name; \
    using const_t = const_name; \
    using bus_t   = bus_name; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& __rhs__) { base::operator=(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    assignment_body(name, __VA_ARGS__) \
    name clone() const { \
      return name(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
    CH_FOR_EACH(CH_STRUCT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    void read_data(cash::internal::nodelist<data_t>& __inout__, size_t __offset__, size_t __length__) const { \
      CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_t>& __in__, size_t __src_offset__, size_t __length__) { \
      CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    template <typename __T__, typename __D__, unsigned __N__, bool __R__> friend class cash::internal::typebase;

#define CH_STRUCT_NOASSIGN_IMPL(name, ...)

#define CH_STRUCT_ASSIGN_IMPL(name, ...) \
  explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
    : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  template <typename __T__, CH_REQUIRES(cash::internal::is_scalar<__T__>::value)> \
  explicit name(__T__ __rhs__) { base::operator=(__rhs__); } \
  name& operator=(const name& __rhs__) { \
    CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
    return *this; \
  }

#define CH_STRUCT_IMPL(name, ...) \
  class name : public cash::internal::ch_bitbase<name, CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__), false> { \
  protected: \
    class __bus_type__ : public cash::internal::ch_busbase<__bus_type__, CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__)> { \
      CH_STRUCT_BUS_IMPL(__bus_type__, __VA_ARGS__) \
    }; \
    class __const_type__ : public cash::internal::ch_bitbase<__const_type__, CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__), true> { \
      CH_STRUCT_BODY_IMPL(__const_type__, __const_type__, __bus_type__, true, CH_STRUCT_NOASSIGN_IMPL, __VA_ARGS__) \
    }; \
    CH_STRUCT_BODY_IMPL(name, __const_type__, __bus_type__, false, CH_STRUCT_ASSIGN_IMPL, __VA_ARGS__) \
  }

#define CH_STRUCT(name, body) \
  CH_STRUCT_IMPL(name, CH_REM body)
