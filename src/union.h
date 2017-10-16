#pragma once

#include "bit.h"

#define CH_UNION_SIZE_EACH(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)>::bitsize

#define CH_UNION_SIZE(...) \
  std::max({CH_FOR_EACH(CH_UNION_SIZE_EACH, CH_SEP_COMMA, __VA_ARGS__)})

#define CH_UNION_SIM_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::traits::scalar_type CH_PAIR_R(x)

#define CH_UNION_SIM_MOVE_CTOR(i, x) \
  CH_PAIR_R(x)(std::move(__rhs__.CH_PAIR_R(x)))

#define CH_UNION_SIM_MOVE_ASSIGN(i, x) \
  CH_PAIR_R(x) = std::move(__rhs__.CH_PAIR_R(x))

#define CH_UNION_FIELD(i, x) \
  ch::internal::sliceref< \
    base, ch::internal::identity_t<CH_PAIR_L(x)>::bitsize> CH_PAIR_R(x)

#define CH_UNION_CONST_FIELD(i, x) \
  ch::internal::const_sliceref< \
    ch::internal::refproxy<base>, \
    ch::internal::identity_t<CH_PAIR_L(x)>::bitsize> CH_PAIR_R(x)

#define CH_UNION_COPY_CTOR(i, x) \
  CH_PAIR_R(x)(_)

#define CH_UNION_SIM_IMPL(union_name, value_name, ...) \
  class union_name { \
  public: \
    static constexpr unsigned bitsize = CH_UNION_SIZE(__VA_ARGS__); \
    using traits = ch::internal::scalar_traits<union_name, value_name>; \
  protected: \
    ch::internal::bytes_store _; \
  public: \
    union_name() \
      : _(bitsize) \
      , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    union_name(const union_name& __rhs__) \
      : _(__rhs__._) \
      , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    union_name(union_name&& __rhs__) \
      : _(std::move(__rhs__._)) \
      , CH_FOR_EACH(CH_UNION_SIM_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    union_name(const ch::internal::bytes_store& store, unsigned offset = 0) \
      : _(bitsize, store, offset) \
      , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    template <typename U, CH_REQUIRES(ch::internal::is_cast_convertible<ch_scalar<bitsize>, U>::value)> \
    explicit union_name(const U& __rhs__) \
      : _(__rhs__) \
      , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
    union_name& operator=(const union_name& __rhs__) { \
      _ = __rhs__._; \
      return *this; \
    } \
    union_name& operator=(union_name&& __rhs__) { \
      _ = std::move(__rhs__._); \
      CH_FOR_EACH(CH_UNION_SIM_MOVE_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_FOR_EACH(CH_UNION_SIM_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    CH_SCALAR_TYPE_INTERFACE() \
  }

#define CH_UNION_BODY_IMPL(union_name, assignment_body, field_body, ...) \
protected: \
  ch_bit<base::bitsize> _; \
public: \
  union_name() \
    : CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& __rhs__) \
    : _(__rhs__._) \
    , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(union_name&& __rhs__) \
    : _(std::move(__rhs__._)) \
    , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const ch::internal::bitbase<union_name::bitsize>& __rhs__) \
    : _(__rhs__) \
    , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  template <typename T, \
            CH_REQUIRES(ch::internal::is_ch_bit_convertible<T, base::bitsize>::value)> \
  explicit union_name(const T& __rhs__) \
    : _(static_cast<ch::internal::bitbase_cast_t<T, base::bitsize>>(__rhs__)) \
    , CH_FOR_EACH(CH_UNION_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  assignment_body(union_name, __VA_ARGS__) \
  const auto clone() const { \
    return traits::value_type(_.clone()); \
  } \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
protected: \
  void read_lnode(ch::internal::nodelist& __inout__, size_t __offset__, size_t __length__) const override { \
    ch::internal::read_lnode(_, __inout__, __offset__, __length__); \
  } \
  void write_lnode(size_t __dst_offset__, const ch::internal::nodelist& __in__, size_t __src_offset__, size_t __length__) override { \
    ch::internal::write_lnode(_, __dst_offset__, __in__, __src_offset__, __length__); \
  } \
  void read_bytes(uint32_t __dst_offset__, void* __out__, uint32_t __out_bitsize__, uint32_t __src_offset__, uint32_t __length__) const override { \
    ch::internal::read_bytes(_, __dst_offset__, __out__, __out_bitsize__, __src_offset__, __length__); \
  } \
  void write_bytes(uint32_t __dst_offset__, const void* __in__, uint32_t __in_bitsize__, uint32_t __src_offset__, uint32_t __length__) override { \
    ch::internal::write_bytes(_, __dst_offset__, __in__, __in_bitsize__, __src_offset__, __length__); \
  }

#define CH_UNION_READONLY_IMPL(union_name, ...) \
  CH_BIT_READONLY_INTERFACE(union_name)

#define CH_UNION_WRITABLE_IMPL(union_name, ...) \
  union_name(const __const_type__& __rhs__) \
    : union_name(reinterpret_cast<const base&>(__rhs__)) {} \
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
  class union_name : public ch::internal::bitbase<CH_UNION_SIZE(__VA_ARGS__)> { \
  protected: \
    CH_UNION_SIM_IMPL(__scalar_type__, union_name, __VA_ARGS__); \
    class __const_type__ : public ch::internal::bitbase<CH_UNION_SIZE(__VA_ARGS__)> { \
    public: \
      using base = ch::internal::bitbase<CH_UNION_SIZE(__VA_ARGS__)>; \
      using traits = ch::internal::logic_traits<__const_type__, __const_type__, union_name, __scalar_type__>; \
      CH_UNION_BODY_IMPL(__const_type__, CH_UNION_READONLY_IMPL, CH_UNION_CONST_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using base = ch::internal::bitbase<CH_UNION_SIZE(__VA_ARGS__)>; \
    using traits = ch::internal::logic_traits<union_name, __const_type__, union_name, __scalar_type__>; \
    CH_UNION_BODY_IMPL(union_name, CH_UNION_WRITABLE_IMPL, CH_UNION_FIELD, __VA_ARGS__) \
  }

#define CH_UNION(name, body) \
  CH_UNION_IMPL(name, CH_REM body)
