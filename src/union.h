#pragma once

#include "bit.h"
#include "bus.h"

#define CH_UNION_SIZE_EACH(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_UNION_SIZE(...) \
  std::max({CH_FOR_EACH(CH_UNION_SIZE_EACH, CH_SEP_COMMA, __VA_ARGS__)})

#define CH_UNION_FIELD(i, x) \
  cash::internal::sliceref<base, CH_PAIR_L(x)::bitcount> CH_PAIR_R(x)

#define CH_UNION_CONST_FIELD(i, x) \
  cash::internal::const_sliceref<cash::internal::refproxy<base>, CH_PAIR_L(x)::bitcount> CH_PAIR_R(x)

#define CH_UNION_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(_)

#define CH_UNION_BUS_IMPL(name, ...) \
  class name : public cash::internal::ch_busbase<CH_UNION_SIZE(__VA_ARGS__)> { \
  public: \
    using base = cash::internal::ch_busbase<CH_UNION_SIZE(__VA_ARGS__)>; \
    using data_t = typename base::data_t; \
    using value_t = name; \
    name() : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__._) {} \
    name(name&& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(std::move(__rhs__._)) {} \
    name(const base& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__) {} \
    template <typename T, CH_REQUIRES(cash::internal::is_bus_convertible<T, base::bitcount>::value)> \
    explicit name(const T& __rhs__) \
      : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
      _(static_cast<typename cash::internal::bus_cast<T, base::bitcount>::type>(__rhs__)) {} \
    name& operator=(const name& __rhs__) { \
      this->assign(__rhs__); \
      return *this; \
    } \
    name& operator=(name&& __rhs__) { \
      _ = std::move(__rhs__._); \
      return *this; \
    } \
    CH_BUS_INTERFACE(name) \
    void write(uint32_t dst_offset, const void* in, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = CH_UNION_SIZE(__VA_ARGS__)) { \
      _.write(dst_offset, in, sizeInBytes, src_offset, length); \
    } \
    CH_FOR_EACH(CH_UNION_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    ch_bus<base::bitcount> _; \
    void read_data(cash::internal::nodelist<data_t>& __inout__, size_t __offset__, size_t __length__) const override { \
      cash::internal::read_data(_, __inout__, __offset__, __length__); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_t>& __in__, size_t __src_offset__, size_t __length__) override { \
      cash::internal::write_data(_, __dst_offset__, __in__, __src_offset__, __length__); \
    } \
  }

#define CH_UNION_BODY_IMPL(name, value_name, const_name, bus_name, assignment_body, field_body, ...) \
  public: \
    using base = cash::internal::ch_bitbase<CH_UNION_SIZE(__VA_ARGS__)>; \
    using data_t  = typename base::data_t; \
    using value_t = value_name; \
    using const_t = const_name; \
    using bus_t   = bus_name; \
    name() : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__._) {} \
    name(name&& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(std::move(__rhs__._)) {} \
    name(const base& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__) {} \
    template <typename T, CH_REQUIRES(cash::internal::is_bit_convertible<T, base::bitcount>::value)> \
    explicit name(const T& __rhs__) \
      : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
      _(static_cast<typename cash::internal::bit_cast<T, base::bitcount>::type>(__rhs__)) {} \
    assignment_body(name, __VA_ARGS__) \
    const auto clone() const { \
      return value_t(_.clone()); \
    } \
    CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    ch_bit<base::bitcount> _; \
    void read_data(cash::internal::nodelist<data_t>& __inout__, size_t __offset__, size_t __length__) const override { \
      cash::internal::read_data(_, __inout__, __offset__, __length__); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_t>& __in__, size_t __src_offset__, size_t __length__) override { \
      cash::internal::write_data(_, __dst_offset__, __in__, __src_offset__, __length__); \
    }


#define CH_UNION_READONLY_IMPL(name, ...) \
  CH_BIT_READONLY_INTERFACE(name)

#define CH_UNION_WRITABLE_IMPL(name, ...) \
  name& operator=(const name& __rhs__) { \
    this->assign(__rhs__); \
    return *this; \
  } \
  name& operator=(name&& __rhs__) { \
    _ = std::move(__rhs__._); \
    return *this; \
  } \
  CH_BIT_WRITABLE_INTERFACE(name)

#define CH_UNION_IMPL(name, ...) \
  class name : public cash::internal::ch_bitbase<CH_UNION_SIZE(__VA_ARGS__)> { \
  protected: \
    CH_UNION_BUS_IMPL(__bus_type__, __VA_ARGS__); \
    class __const_type__ : public cash::internal::ch_bitbase<CH_UNION_SIZE(__VA_ARGS__)> { \
      CH_UNION_BODY_IMPL(__const_type__, name, __const_type__, __bus_type__, CH_UNION_READONLY_IMPL, CH_UNION_CONST_FIELD, __VA_ARGS__) \
    }; \
    CH_UNION_BODY_IMPL(name, name, __const_type__, __bus_type__, CH_UNION_WRITABLE_IMPL, CH_UNION_FIELD, __VA_ARGS__) \
  }

#define CH_UNION(name, body) \
  CH_UNION_IMPL(name, CH_REM body)
