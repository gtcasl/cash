#pragma once

#include "bit.h"

#define CH_UNION_SIZE_EACH(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)>::bitcount

#define CH_UNION_SIZE(...) \
  std::max({CH_FOR_EACH(CH_UNION_SIZE_EACH, CH_SEP_COMMA, __VA_ARGS__)})

#define CH_UNION_FIELD(i, x) \
  ch::internal::sliceref< \
    base, ch::internal::identity_t<CH_PAIR_L(x)>::bitcount> CH_PAIR_R(x)

#define CH_UNION_CONST_FIELD(i, x) \
  ch::internal::const_sliceref< \
    ch::internal::refproxy<base>, \
    ch::internal::identity_t<CH_PAIR_L(x)>::bitcount> CH_PAIR_R(x)

#define CH_UNION_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(_)

#define CH_UNION_BODY_IMPL(union_name, assignment_body, field_body, ...) \
  union_name() : \
    CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& __rhs__) \
    : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
    _(__rhs__._) {} \
  union_name(union_name&& __rhs__) \
    : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
    _(std::move(__rhs__._)) {} \
  union_name(const ch_bitbase<union_name::bitcount>& __rhs__) \
    : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
    _(__rhs__) {} \
  template <typename T, \
            CH_REQUIRES(ch::internal::is_bit_convertible<T, base::bitcount>::value)> \
  explicit union_name(const T& __rhs__) \
    : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
    _(static_cast<ch::internal::bitbase_cast_t<T, base::bitcount>>(__rhs__)) {} \
  assignment_body(union_name, __VA_ARGS__) \
  const auto clone() const { \
    return value_type(_.clone()); \
  } \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
protected: \
  ch_bit<base::bitcount> _; \
  void read_data(ch::internal::nodelist& __inout__, size_t __offset__, size_t __length__) const override { \
    ch::internal::read_data(_, __inout__, __offset__, __length__); \
  } \
  void write_data(size_t __dst_offset__, const ch::internal::nodelist& __in__, size_t __src_offset__, size_t __length__) override { \
    ch::internal::write_data(_, __dst_offset__, __in__, __src_offset__, __length__); \
  } \
  void read_bytes(uint32_t __dst_offset__, void* __out__, uint32_t __out_cbsize__, uint32_t __src_offset__, uint32_t __length__) const override { \
    ch::internal::read_bytes(_, __dst_offset__, __out__, __out_cbsize__, __src_offset__, __length__); \
  } \
  void write_bytes(uint32_t __dst_offset__, const void* __in__, uint32_t __in_cbsize__, uint32_t __src_offset__, uint32_t __length__) override { \
    ch::internal::write_bytes(_, __dst_offset__, __in__, __in_cbsize__, __src_offset__, __length__); \
  }

#define CH_UNION_READONLY_IMPL(union_name, ...) \
  CH_BIT_READONLY_INTERFACE(union_name)

#define CH_UNION_WRITABLE_IMPL(union_name, ...) \
  union_name(const const_type& __rhs__) : union_name(reinterpret_cast<const base&>(__rhs__)) {} \
  union_name& operator=(const union_name& __rhs__) { \
    base::assign(__rhs__); \
    return *this; \
  } \
  union_name& operator=(union_name&& __rhs__) { \
    _ = std::move(__rhs__._); \
    return *this; \
  } \
  CH_BIT_WRITABLE_INTERFACE(union_name)

#define CH_UNION_IMPL(union_name, ...) \
  class union_name : public ch_bitbase<CH_UNION_SIZE(__VA_ARGS__)> { \
  protected: \
    class __const_type__ : public ch_bitbase<CH_UNION_SIZE(__VA_ARGS__)> { \
    public: \
      using base = ch_bitbase<CH_UNION_SIZE(__VA_ARGS__)>; \
      using value_type = union_name; \
      using const_type = __const_type__; \
      CH_UNION_BODY_IMPL(__const_type__, CH_UNION_READONLY_IMPL, CH_UNION_CONST_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using base = ch_bitbase<CH_UNION_SIZE(__VA_ARGS__)>; \
    using value_type = union_name; \
    using const_type = __const_type__; \
    CH_UNION_BODY_IMPL(union_name, CH_UNION_WRITABLE_IMPL, CH_UNION_FIELD, __VA_ARGS__) \
  }

#define CH_UNION(name, body) \
  CH_UNION_IMPL(name, CH_REM body)
