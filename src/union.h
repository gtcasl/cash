#pragma once

#include "bit.h"
#include "bus.h"

#define CH_UNION_SIZE(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_UNION_FIELD(i, x) \
  cash::internal::sliceref<base, CH_PAIR_L(x)::bitcount> CH_PAIR_R(x)

#define CH_UNION_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(_)

#define CH_UNION_IMPL(name, ...) \
  class name : public cash::internal::ch_bitbase<std::max({CH_FOR_EACH(CH_UNION_SIZE, CH_SEP_COMMA, __VA_ARGS__)})> { \
  public:\
    using base = cash::internal::ch_bitbase<std::max({CH_FOR_EACH(CH_UNION_SIZE, CH_SEP_COMMA, __VA_ARGS__)})>; \
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
      bus_type() : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const bus_type& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__._) {} \
      bus_type(const base& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__) {} \
      template <typename T, CH_REQUIRES(cash::internal::is_bit_convertible<T, base::bitcount>::value)> \
      explicit bus_type(const T& __rhs__) \
        : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
        _(static_cast<typename cash::internal::ch_bus_cast<T, base::bitcount>::type>(__rhs__)) {} \
      bus_type& operator=(const bus_type& __rhs__) { \
        _ = __rhs__._; \
        return *this; \
      } \
      CH_FOR_EACH(CH_UNION_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    protected: \
      ch_bus<base::bitcount> _; \
      void read_data(data_type& __inout__, size_t __offset__, size_t __length__) const { \
        cash::internal::read_data(_, __inout__, __offset__, __length__); \
      } \
      void write_data(size_t __dst_offset__, const data_type& __in__, size_t __src_offset__, size_t __length__) { \
        cash::internal::write_data(_, __dst_offset__, __in__, __src_offset__, __length__); \
      } \
    };\
    name() : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__._) {} \
    name(const base& __rhs__) : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), _(__rhs__) {} \
    template <typename T, CH_REQUIRES(cash::internal::is_bit_convertible<T, base::bitcount>::value)> \
    explicit name(const T& __rhs__) \
      : CH_FOR_EACH(CH_UNION_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__), \
      _(static_cast<typename cash::internal::ch_bit_cast<T, base::bitcount>::type>(__rhs__)) {} \
    name& operator=(const name& __rhs__) { \
      _ = __rhs__._; \
      return *this; \
    } \
    CH_FOR_EACH(CH_UNION_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    name clone() const { \
      return name(_.clone()); \
    } \
  protected: \
    ch_bit<base::bitcount> _; \
    void read_data(data_type& __inout__, size_t __offset__, size_t __length__) const { \
      cash::internal::read_data(_, __inout__, __offset__, __length__); \
    } \
    void write_data(size_t __dst_offset__, const data_type& __in__, size_t __src_offset__, size_t __length__) { \
      cash::internal::write_data(_, __dst_offset__, __in__, __src_offset__, __length__); \
    } \
  }

#define CH_UNION(name, body) CH_UNION_IMPL(name, CH_REM body)
