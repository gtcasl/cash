#pragma once

#include "bit.h"

namespace ch {
namespace internal {

void registerEnumString(const lnode& node, void* callback);

}
}

#define CH_ENUM_VALUE_1(x, i) i
#define CH_ENUM_VALUE_2(x, i) CH_PAIR_SECOND(x)
#define CH_ENUM_VALUE_(c) CH_CONCAT(CH_ENUM_VALUE_, c)
#define CH_ENUM_VALUE(a, i, x) CH_ENUM_VALUE_(CH_NARG(CH_REM x))(CH_REM x, i)

#define CH_ENUM_SIZE(...) \
  log2up(std::max({1, CH_FOR_EACH(CH_ENUM_VALUE, , CH_SEP_COMMA, __VA_ARGS__)}) + 1)

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(a, i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_STRING_1(x, y) y : return CH_STRINGIZE(y)
#define CH_ENUM_STRING_2(x, y) CH_PAIR_FIRST(x) : return CH_STRINGIZE(CH_PAIR_FIRST(x))
#define CH_ENUM_STRING_(c) CH_CONCAT(CH_ENUM_STRING_, c)
#define CH_ENUM_STRING(a, i, x) case CH_ENUM_STRING_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_SYSTEM_IMPL(enum_name) \
  enum_name(const ch::internal::system_buffer& buffer = \
    ch::internal::make_system_buffer(traits::bitwidth, CH_STRINGIZE(enum_name))) \
    : buffer_(buffer) {} \
  enum_name(type __other) \
    : enum_name(ch::internal::make_system_buffer(traits::bitwidth, CH_STRINGIZE(enum_name))) { \
    this->operator=(__other); \
  } \
  enum_name(const enum_name& __other) \
    : enum_name(ch::internal::make_system_buffer(traits::bitwidth, CH_STRINGIZE(enum_name))) { \
    this->operator=(__other); \
  } \
  enum_name(enum_name&& __other) : buffer_(std::move(__other.buffer_)) {} \
  enum_name& operator=(const enum_name& __other) { \
    ch::internal::system_accessor::assign(*this, __other); \
    return *this; \
  } \
  enum_name& operator=(enum_name&& __other) { \
    ch::internal::system_accessor::move(*this, std::move(__other)); \
    return *this; \
  } \
  enum_name& operator=(type __other) { \
    base::operator=(static_cast<unsigned>(__other)); \
    return *this; \
  }

#define CH_ENUM_LOGIC_IMPL(enum_name) \
  enum_name(const ch::internal::logic_buffer& buffer = \
    ch::internal::make_logic_buffer(traits::bitwidth, CH_STRINGIZE(enum_name))) \
    : buffer_(buffer) { \
    ch::internal::registerEnumString(ch::internal::get_lnode(*this), (void*)to_string); \
  } \
  enum_name(type __other) \
    : enum_name(ch::internal::make_logic_buffer(traits::bitwidth, CH_STRINGIZE(enum_name))) { \
    CH_SOURCE_LOCATION(1); \
    this->operator=(__other); \
  } \
  enum_name(const enum_name& __other) \
    : enum_name(ch::internal::make_logic_buffer(traits::bitwidth, CH_STRINGIZE(enum_name))) { \
    CH_SOURCE_LOCATION(1); \
    this->operator=(__other); \
  } \
  enum_name(enum_name&& __other) : buffer_(std::move(__other.buffer_)) {} \
  enum_name& operator=(const enum_name& __other) { \
    CH_SOURCE_LOCATION(1); \
    ch::internal::logic_accessor::assign(*this, __other); \
    return *this; \
  } \
  enum_name& operator=(enum_name&& __other) { \
    CH_SOURCE_LOCATION(1); \
    ch::internal::logic_accessor::move(*this, std::move(__other)); \
    return *this; \
  } \
  enum_name& operator=(type __other) { \
    CH_SOURCE_LOCATION(1); \
    base::operator=(static_cast<unsigned>(__other)); \
    return *this; \
  }

#define CH_ENUM_IMPL(enum_name, size, ...) \
  class enum_name : public ch::internal::ch_bit_base<enum_name> { \
  public: \
    enum type { \
      CH_FOR_EACH(CH_ENUM_FIELD, , CH_SEP_COMMA, __VA_ARGS__) \
      , __MAX_VALUE__ \
    }; \
    static_assert(log2floor<int>(__MAX_VALUE__) <= size, "size mismatch"); \
    static const char* to_string(type value) { \
      switch (value) { \
      CH_FOR_EACH(CH_ENUM_STRING, , CH_SEP_SEMICOLON, __VA_ARGS__); \
      default: \
        return "undefined"; \
      } \
    }\
  private: \
    const ch::internal::logic_buffer& __buffer() const { \
      return buffer_; \
    } \
    ch::internal::logic_buffer buffer_; \
    friend class ch::internal::logic_accessor; \
    \
    class __system_type__ : public ch::internal::ch_sbit_base<__system_type__> { \
    private: \
      const ch::internal::system_buffer& __buffer() const { \
        return buffer_; \
      } \
      ch::internal::system_buffer buffer_; \
      friend class ch::internal::system_accessor; \
    public: \
      using traits = ch::internal::system_traits<size, false, __system_type__, enum_name>; \
      using base = ch::internal::ch_sbit_base<__system_type__>; \
      CH_ENUM_SYSTEM_IMPL(__system_type__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<size, false, enum_name, __system_type__>; \
    using base = ch::internal::ch_bit_base<enum_name>; \
    CH_ENUM_LOGIC_IMPL(enum_name) \
  }

#define CH_ENUM3(name, size, body) \
  CH_ENUM_IMPL(name, size, CH_REM body)

#define CH_ENUM2(name, body) \
  CH_ENUM_IMPL(name, CH_ENUM_SIZE(CH_REM body), CH_REM body)

#define GET_ENUM(_1, _2, _3, NAME, ...) NAME
#define CH_ENUM(...) GET_ENUM(__VA_ARGS__, CH_ENUM3, CH_ENUM2, ignore)(__VA_ARGS__)

