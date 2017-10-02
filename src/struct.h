#pragma once

#include "bit.h"

#define CH_STRUCT_SIZE_EACH(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_STRUCT_SIZE(...) \
  CH_FOR_EACH(CH_STRUCT_SIZE_EACH, CH_SEP_PLUS, __VA_ARGS__)

#define CH_STRUCT_FIELD(i, x) \
  typename CH_PAIR_L(x)::value_type CH_PAIR_R(x)

#define CH_STRUCT_CONST_FIELD(i, x) \
  typename CH_PAIR_L(x)::const_type CH_PAIR_R(x)

#define CH_STRUCT_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_STRUCT_MOVE_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(std::move(__rhs__.CH_PAIR_R(x)))

#define CH_STRUCT_FIELD_CTOR_TMPL(i, x) \
  typename __T##i

#define CH_STRUCT_FIELD_CTOR_REQUIRES(i, x) \
  CH_REQUIRES(ch::internal::is_cast_convertible<__T##i, typename CH_PAIR_L(x)::value_type>::value)

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
    ch::internal::read_data(CH_PAIR_R(x), __inout__, __offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __offset__ -= CH_PAIR_L(x)::bitcount
          
#define CH_STRUCT_WRITE_DATA(i, x) \
  if (__dst_offset__ < CH_PAIR_L(x)::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, CH_PAIR_L(x)::bitcount - __dst_offset__); \
    ch::internal::write_data(CH_PAIR_R(x), __dst_offset__, __in__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __src_offset__ += __len__; \
    __dst_offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __dst_offset__ -= CH_PAIR_L(x)::bitcount

#define CH_STRUCT_READ_BYTES(i, x) \
  if (__dst_offset__ < CH_PAIR_L(x)::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, CH_PAIR_L(x)::bitcount - __dst_offset__); \
    CH_PAIR_R(x).read_bytes(__dst_offset__, __out__, __out_cbsize__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __src_offset__ += __len__; \
    __dst_offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __dst_offset__ -= CH_PAIR_L(x)::bitcount

#define CH_STRUCT_WRITE_BYTES(i, x) \
  if (__dst_offset__ < CH_PAIR_L(x)::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, CH_PAIR_L(x)::bitcount - __dst_offset__); \
    CH_PAIR_R(x).write_bytes(__dst_offset__, __in__, __in_cbsize__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __src_offset__ += __len__; \
    __dst_offset__ = CH_PAIR_L(x)::bitcount; \
  } \
  __dst_offset__ -= CH_PAIR_L(x)::bitcount

#define CH_STRUCT_BODY_IMPL(struct_name, value_name, const_name, assignment_body, field_body, ...) \
  public:\
    using base = typename ch::internal::ch_bitbase<CH_STRUCT_SIZE(__VA_ARGS__)>; \
    using value_type = value_name; \
    using const_type = const_name; \
    struct_name() {} \
    struct_name(const struct_name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    struct_name(struct_name&& __rhs__) : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    struct_name(const ch::internal::ch_bitbase<struct_name::bitcount>& __rhs__) { this->assign(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit struct_name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    template <typename __T__, CH_REQUIRES(ch::internal::is_ch_scalar<__T__>::value)> \
    explicit struct_name(__T__ __rhs__) { this->assign(__rhs__); } \
    assignment_body(struct_name, __VA_ARGS__) \
    const auto clone() const { \
      return value_type(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
    CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    void read_data(ch::internal::nodelist& __inout__, size_t __offset__, size_t __length__) const { \
      CH_FOR_EACH(CH_STRUCT_READ_DATA, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void write_data(size_t __dst_offset__, const ch::internal::nodelist& __in__, size_t __src_offset__, size_t __length__) { \
      CH_FOR_EACH(CH_STRUCT_WRITE_DATA, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void read_bytes(uint32_t __dst_offset__, void* __out__, uint32_t __out_cbsize__, uint32_t __src_offset__, uint32_t __length__) const override { \
      CH_FOR_EACH(CH_STRUCT_READ_BYTES, CH_SEP_SEMICOLON, __VA_ARGS__); \
    } \
    void write_bytes(uint32_t __dst_offset__, const void* __in__, uint32_t __in_cbsize__, uint32_t __src_offset__, uint32_t __length__) const override { \
      CH_FOR_EACH(CH_STRUCT_WRITE_BYTES, CH_SEP_SEMICOLON, __VA_ARGS__); \
    }

#define CH_STRUCT_READ_DATAONLY_IMPL(struct_name, ...) \
  CH_BIT_READONLY_INTERFACE(struct_name) \

#define CH_STRUCT_WRITABLE_IMPL(struct_name, ...) \
  struct_name(const const_type& __rhs__) : struct_name(reinterpret_cast<const base&>(__rhs__)) {} \
  struct_name& operator=(const struct_name& __rhs__) { \
    this->assign(__rhs__); \
    return *this; \
  } \
  struct_name& operator=(struct_name&& __rhs__) { \
    CH_FOR_EACH(CH_STRUCT_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
    return *this; \
  } \
  CH_BIT_WRITABLE_INTERFACE(struct_name)

#define CH_STRUCT_IMPL(struct_name, ...) \
  class struct_name : public ch::internal::ch_bitbase<CH_STRUCT_SIZE(__VA_ARGS__)> { \
  protected: \
    class __const_type__ : public ch::internal::ch_bitbase<CH_STRUCT_SIZE(__VA_ARGS__)> { \
      CH_STRUCT_BODY_IMPL(__const_type__, struct_name, __const_type__, CH_STRUCT_READ_DATAONLY_IMPL, CH_STRUCT_CONST_FIELD, __VA_ARGS__) \
    }; \
    CH_STRUCT_BODY_IMPL(struct_name, struct_name, __const_type__, CH_STRUCT_WRITABLE_IMPL, CH_STRUCT_FIELD, __VA_ARGS__) \
  }

#define CH_STRUCT(name, body) \
  CH_STRUCT_IMPL(name, CH_REM body)
