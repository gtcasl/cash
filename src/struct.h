#pragma once

#include "bit.h"
#include "bus.h"

#define CH_STRUCT_SIZE_EACH(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_STRUCT_SIZE(...) \
  CH_FOR_EACH(CH_STRUCT_SIZE_EACH, CH_SEP_PLUS, __VA_ARGS__)

#define CH_STRUCT_FIELD(i, x) \
  typename CH_PAIR_L(x)::value_t CH_PAIR_R(x)

#define CH_STRUCT_CONST_FIELD(i, x) \
  typename CH_PAIR_L(x)::const_t CH_PAIR_R(x)

#define CH_STRUCT_BUS_FIELD(i, x) \
  typename CH_PAIR_L(x)::bus_t CH_PAIR_R(x)

#define CH_STRUCT_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_STRUCT_MOVE_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(std::move(__rhs__.CH_PAIR_R(x)))

#define CH_STRUCT_FIELD_CTOR_TMPL(i, x) \
  typename __T##i

#define CH_STRUCT_FIELD_CTOR_REQUIRES(i, x) \
  CH_REQUIRES(cash::internal::is_cast_convertible<__T##i, typename CH_PAIR_L(x)::value_t>::value)

#define CH_STRUCT_FIELD_CTOR_ARGS(i, x) \
  const __T##i& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_FIELD_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(CH_CONCAT(_,CH_PAIR_R(x)))

#define CH_STRUCT_MOVE_ASSIGN(i, x) \
  this->CH_PAIR_R(x) = std::move(__rhs__.CH_PAIR_R(x))

#define CH_STRUCT_CLONE(i, x) \
  CH_PAIR_R(x).clone()

#define CH_STRUCT_READ_DATA(i, x) \
  if (__offset__ < CH_PAIR_L(x)::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, CH_PAIR_L(x)::bitcount - __offset__); \
    cash::internal::read_data(CH_PAIR_R(x), __inout__, __offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __offset__ -= CH_PAIR_L(x)::bitcount
          
#define CH_STRUCT_WRITE_DATA(i, x) \
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

#define CH_STRUCT_BUS_WRITE(i, x) \
  if (__dst_offset__ < CH_PAIR_L(x)::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, CH_PAIR_L(x)::bitcount - __dst_offset__); \
    CH_PAIR_R(x).write(__dst_offset__, __in__, __sizeInBytes__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __src_offset__ += __len__; \
    __dst_offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __dst_offset__ -= CH_PAIR_L(x)::bitcount

#define CH_STRUCT_BUS_IMPL(name, ...) \
  class name : public cash::internal::ch_busbase<CH_STRUCT_SIZE(__VA_ARGS__)> { \
  public: \
    using base = cash::internal::ch_busbase<CH_STRUCT_SIZE(__VA_ARGS__)>; \
    using data_t = typename base::data_t; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(name&& __rhs__) : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& __rhs__) { this->assign(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    template <typename __T__, CH_REQUIRES(cash::internal::is_bit_scalar<__T__>::value)> \
    explicit name(__T__ __rhs__) { this->assign(__rhs__); } \
    name& operator=(const name& __rhs__) { \
      this->assign(__rhs__); \
      return *this; \
    } \
    name& operator=(name&& __rhs__) { \
      CH_FOR_EACH(CH_STRUCT_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_BUS_INTERFACE(name) \
    void write(uint32_t __dst_offset__, const void* __in__, uint32_t __sizeInBytes__, uint32_t __src_offset__ = 0, uint32_t __length__ = CH_STRUCT_SIZE(__VA_ARGS__)) { \
      assert(__dst_offset__ + __length__ <= base::bitcount); \
      assert(__src_offset__ + __length__ <= __sizeInBytes__ * 8); \
      CH_FOR_EACH(CH_STRUCT_BUS_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    CH_FOR_EACH(CH_STRUCT_BUS_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    void read_data(cash::internal::nodelist<data_t>& __inout__, size_t __offset__, size_t __length__) const override { \
      CH_FOR_EACH(CH_STRUCT_READ_DATA, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_t>& __in__, size_t __src_offset__, size_t __length__) override { \
      CH_FOR_EACH(CH_STRUCT_WRITE_DATA, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
  }

#define CH_STRUCT_BODY_IMPL(name, value_name, const_name, bus_name, assignment_body, field_body, ...) \
  public:\
    using base = typename cash::internal::ch_bitbase<CH_STRUCT_SIZE(__VA_ARGS__)>; \
    using data_t  = typename base::data_t; \
    using value_t = value_name; \
    using const_t = const_name; \
    using bus_t   = bus_name; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(name&& __rhs__) : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& __rhs__) { this->assign(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    template <typename __T__, CH_REQUIRES(cash::internal::is_bit_scalar<__T__>::value)> \
    explicit name(__T__ __rhs__) { this->assign(__rhs__); } \
    assignment_body(name, __VA_ARGS__) \
    const auto clone() const { \
      return value_t(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
    CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    void read_data(cash::internal::nodelist<data_t>& __inout__, size_t __offset__, size_t __length__) const { \
      CH_FOR_EACH(CH_STRUCT_READ_DATA, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_t>& __in__, size_t __src_offset__, size_t __length__) { \
      CH_FOR_EACH(CH_STRUCT_WRITE_DATA, CH_SEP_SEMICOLON, __VA_ARGS__); \
    }

#define CH_STRUCT_READ_DATAONLY_IMPL(name, ...) \
  CH_BIT_READONLY_INTERFACE(name) \

#define CH_STRUCT_WRITABLE_IMPL(name, ...) \
  name& operator=(const name& __rhs__) { \
    this->assign(__rhs__); \
    return *this; \
  } \
  name& operator=(name&& __rhs__) { \
    CH_FOR_EACH(CH_STRUCT_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
    return *this; \
  } \
  CH_BIT_WRITABLE_INTERFACE(name)

#define CH_STRUCT_IMPL(name, ...) \
  class name : public cash::internal::ch_bitbase<CH_STRUCT_SIZE(__VA_ARGS__)> { \
  protected: \
    CH_STRUCT_BUS_IMPL(__bus_type__, __VA_ARGS__); \
    class __const_type__ : public cash::internal::ch_bitbase<CH_STRUCT_SIZE(__VA_ARGS__)> { \
      CH_STRUCT_BODY_IMPL(__const_type__, name, __const_type__, __bus_type__, CH_STRUCT_READ_DATAONLY_IMPL, CH_STRUCT_CONST_FIELD, __VA_ARGS__) \
    }; \
    CH_STRUCT_BODY_IMPL(name, name, __const_type__, __bus_type__, CH_STRUCT_WRITABLE_IMPL, CH_STRUCT_FIELD, __VA_ARGS__) \
  }

#define CH_STRUCT(name, body) \
  CH_STRUCT_IMPL(name, CH_REM body)
