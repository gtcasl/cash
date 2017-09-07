#pragma once

#include "bit.h"
#include "bus.h"

#define CH_UNION_SIZE(i, x) \
  CH_PAIR_L(x)::bitcount

#define CH_UNION_FIELD(i, x) \
  cash::internal::sliceref<base, CH_PAIR_L(x)::bitcount> CH_PAIR_R(x)

#define CH_UNION_CTOR_INIT(i, x) \
  CH_PAIR_R(x)(_)

#define CH_UNION_IMPL(name, ...) \
  class name : public cash::internal::ch_bitbase<std::max({CH_FOR_EACH(CH_UNION_SIZE, CH_SEP_COMMA, __VA_ARGS__)})> { \
  public:\
    using base = cash::internal::ch_bitbase<std::max({CH_FOR_EACH(CH_UNION_SIZE, CH_SEP_COMMA, __VA_ARGS__)})>; \
    using base::operator=; \
    using data_type = typename base::data_type; \
    class bus_type : public cash::internal::ch_busbase<base::bitcount> { \
    public: \
      using base = cash::internal::ch_busbase<name::base::bitcount>; \
      using base::operator=; \
      using data_type = typename base::data_type; \
      bus_type() : CH_FOR_EACH(CH_UNION_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
      bus_type(const bus_type& rhs) : CH_FOR_EACH(CH_UNION_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__), _(rhs._) {} \
      bus_type& operator=(const bus_type& rhs) { \
        _ = rhs._; \
        return *this; \
      } \
      CH_FOR_EACH(CH_UNION_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    protected: \
      ch_bus<base::bitcount> _; \
      void read_data(data_type& inout, size_t offset, size_t length) const override { \
        cash::internal::read_data(_, inout, offset, length); \
      } \
      void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override { \
        cash::internal::write_data(_, dst_offset, in, src_offset, length); \
      } \
    };\
    name() : CH_FOR_EACH(CH_UNION_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const name& rhs) : CH_FOR_EACH(CH_UNION_CTOR_INIT, CH_SEP_COMMA, __VA_ARGS__), _(rhs._) {} \
    name& operator=(const name& rhs) { \
      _ = rhs._; \
      return *this; \
    } \
    CH_FOR_EACH(CH_UNION_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    name clone() const { \
      return name(_.clone()); \
    } \
  protected: \
    ch_bit<base::bitcount> _; \
    void read_data(data_type& inout, size_t offset, size_t length) const override { \
      cash::internal::read_data(_, inout, offset, length); \
    } \
    void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override { \
      cash::internal::write_data(_, dst_offset, in, src_offset, length); \
    } \
  public:

#define CH_UNION(name, body, ...) CH_UNION_IMPL(name, CH_REM body) __VA_ARGS__ }
