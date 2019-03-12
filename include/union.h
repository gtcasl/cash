#pragma once

#include "logic.h"

#define CH_UNION_SIZE_EACH(a, i, x) \
  ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_UNION_SIZE(...) \
  std::max({CH_FOR_EACH(CH_UNION_SIZE_EACH, , CH_SEP_COMMA, __VA_ARGS__)})

#define CH_UNION_SYSTEM_CTOR(a, i, x) \
  CH_PAIR_R(x)(ch::internal::make_system_buffer( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0))

#define CH_UNION_LOGIC_CTOR(a, i, x) \
  CH_PAIR_R(x)(ch::internal::logic_buffer( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, 0, buffer.sloc(), CH_STRINGIZE(CH_PAIR_R(x))))

#define CH_UNION_SYSTEM_FIELD(a, i, x) \
  ch_system_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_LOGIC_FIELD(a, i, x) \
  ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_UNION_OSTREAM(a, i, x) \
  if (i) { \
    __out << ",";  \
  } \
  __out << __in.CH_PAIR_R(x)

#define CH_UNION_SYSTEM_IMPL(union_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  union_name(const ch::internal::system_buffer_ptr& buffer = \
  ch::internal::make_system_buffer(traits::bitwidth)) \
    : CH_FOR_EACH(CH_UNION_SYSTEM_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& __other) \
    : union_name(ch::internal::system_accessor::copy(__other)) {} \
  union_name(union_name&& __other) \
   : union_name(ch::internal::system_accessor::move(__other)) {} \
  union_name(const ch_scbit<traits::bitwidth>& other) \
    : union_name() { \
    this->operator =(other.as<union_name>()); \
  } \
  union_name& operator=(const union_name& __other) { \
    ch::internal::system_accessor::assign(*this, __other); \
    return *this; \
  } \
  union_name& operator=(union_name&& __other) { \
    ch::internal::system_accessor::move(*this, std::move(__other)); \
    return *this; \
  } \
protected: \
  const ch::internal::system_buffer_ptr& buffer() const { \
    CH_STRUCT_SYSTEM_SOURCE(0, CH_FIRST_ARG(__VA_ARGS__)); \
  } \
  friend std::ostream& operator<<(std::ostream& __out, const union_name& __in) { \
    __out << "("; \
    CH_FOR_EACH(CH_UNION_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ")"; \
    return __out; \
  } \
  friend class ch::internal::system_accessor; \
public:

#define CH_UNION_LOGIC_IMPL(union_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  union_name(const ch::internal::logic_buffer& buffer = \
    ch::internal::logic_buffer(traits::bitwidth, CH_CUR_SLOC, CH_STRINGIZE(union_name))) \
    : CH_FOR_EACH(CH_UNION_LOGIC_CTOR, , CH_SEP_COMMA, __VA_ARGS__) {} \
  union_name(const union_name& __other, CH_SLOC) \
    : union_name(ch::internal::logic_accessor::copy(__other, sloc)) {} \
  union_name(union_name&& __other) \
    : union_name(ch::internal::logic_accessor::move(__other)) {} \
  union_name(const ch_bit<traits::bitwidth>& other, CH_SLOC) \
    : union_name(ch::internal::logic_buffer(traits::bitwidth, sloc, CH_STRINGIZE(name))) { \
    this->operator =(other.as<union_name>()); \
  } \
  union_name& operator=(const union_name& __other) { \
    auto sloc = ch::internal::caller_srcinfo(1); \
    ch::internal::logic_accessor::assign(*this, __other, sloc); \
    return *this; \
  } \
  union_name& operator=(union_name&& __other) { \
    auto sloc = ch::internal::caller_srcinfo(1); \
    ch::internal::logic_accessor::move(*this, std::move(__other), sloc); \
    return *this; \
  } \
protected: \
  const ch::internal::logic_buffer& buffer() const { \
    CH_STRUCT_LOGIC_SOURCE(0, CH_FIRST_ARG(__VA_ARGS__)); \
  } \
  friend class ch::internal::logic_accessor; \
public:

#define CH_UNION_IMPL(union_name, ...) \
  class union_name { \
  private: \
    class __system_type__ { \
    public: \
      using traits = ch::internal::system_traits<CH_UNION_SIZE(__VA_ARGS__), false, __system_type__, union_name>; \
      CH_UNION_SYSTEM_IMPL(__system_type__, CH_UNION_SYSTEM_FIELD, __VA_ARGS__) \
      CH_SYSTEM_INTERFACE(__system_type__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<CH_UNION_SIZE(__VA_ARGS__), false, union_name, __system_type__>; \
    CH_UNION_LOGIC_IMPL(union_name, CH_UNION_LOGIC_FIELD, __VA_ARGS__) \
    CH_LOGIC_INTERFACE(union_name) \
  }

#define CH_UNION(name, body) \
  CH_UNION_IMPL(name, CH_REM body)
