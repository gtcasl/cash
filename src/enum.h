#pragma once

#include "logic.h"

namespace ch {
namespace internal {

void register_enum_string(const lnode& node, void* callback);

}
}

#define CH_ENUM_VALUE_1(x, i) i
#define CH_ENUM_VALUE_2(x, i) CH_PAIR_SECOND(x)
#define CH_ENUM_VALUE_(c) CH_CONCAT(CH_ENUM_VALUE_, c)
#define CH_ENUM_VALUE(i, x) CH_ENUM_VALUE_(CH_NARG(CH_REM x))(CH_REM x, i)

#define CH_ENUM_SIZE(...) \
  log2ceil(std::max({1, CH_FOR_EACH(CH_ENUM_VALUE, CH_SEP_COMMA, __VA_ARGS__)}) + 1)

#define CH_ENUM_FIELD_1(x, y) y
#define CH_ENUM_FIELD_2(x, y) CH_PAIR_FIRST(x) = CH_PAIR_SECOND(x)
#define CH_ENUM_FIELD_(c) CH_CONCAT(CH_ENUM_FIELD_, c)
#define CH_ENUM_FIELD(i, x) CH_ENUM_FIELD_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_STRING_1(x, y) y : return CH_STRINGIZE(y)
#define CH_ENUM_STRING_2(x, y) CH_PAIR_FIRST(x) : return CH_STRINGIZE(CH_PAIR_FIRST(x))
#define CH_ENUM_STRING_(c) CH_CONCAT(CH_ENUM_STRING_, c)
#define CH_ENUM_STRING(i, x) case CH_ENUM_STRING_(CH_NARG(CH_REM x))(CH_REM x, x)

#define CH_ENUM_SCALAR_IMPL(enum_name) \
  enum_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth)) : base(buffer) {} \
  enum_name(const enum_name& rhs) : base(rhs) {} \
  enum_name(enum_name&& rhs) : base(std::move(rhs)) {} \
  enum_name(enum_type rhs) : base(rhs) {}

#define CH_ENUM_LOGIC_IMPL(enum_name) \
  enum_name(const std::shared_ptr<ch::internal::type_buffer_t<traits>>& buffer = \
    std::make_shared<ch::internal::type_buffer_t<traits>>(traits::bitwidth, CH_SRC_LOCATION)) \
    : base(buffer) { ch::internal::register_enum_string(ch::internal::logic_accessor::data(*this), (void*)to_string); } \
  enum_name(const enum_name& rhs, const source_location& sloc = CH_SRC_LOCATION) \
    : base(rhs, sloc) { ch::internal::register_enum_string(ch::internal::logic_accessor::data(*this), (void*)to_string); } \
  enum_name(enum_name&& rhs) \
    : base(std::move(rhs)) { ch::internal::register_enum_string(ch::internal::logic_accessor::data(*this), (void*)to_string); } \
  enum_name(enum_type rhs, const source_location& sloc = CH_SRC_LOCATION) \
    : base(rhs, sloc) { ch::internal::register_enum_string(ch::internal::logic_accessor::data(*this), (void*)to_string); }

#define CH_ENUM_ASSIGN_IMPL(enum_name) \
  enum_name& operator=(const enum_name& rhs) { \
    base::operator=(rhs); \
    return *this; \
  } \
  enum_name& operator=(enum_name&& rhs) { \
    base::operator=(std::move(rhs)); \
    return *this; \
  } \
  enum_name& operator=(enum_type rhs) { \
    base::operator=(rhs); \
    return *this; \
  }

#define CH_ENUM_IMPL(enum_name, size, ...) \
  class enum_name : public ch::internal::ch_logic<size> { \
  public: \
    enum enum_type { \
    CH_FOR_EACH(CH_ENUM_FIELD, CH_SEP_COMMA, __VA_ARGS__) \
    , __MAX_VALUE__ \
    }; \
    static_assert(ilog2(__MAX_VALUE__) <= size, "size mismatch"); \
    static const char* to_string(enum_type value) { \
      switch (value) { \
      CH_FOR_EACH(CH_ENUM_STRING, CH_SEP_SEMICOLON, __VA_ARGS__); \
      default: \
        return "undefined"; \
      } \
    }\
  private: \
    class __scalar_type__ : public ch::internal::ch_scalar<size> { \
    public: \
      using traits = ch::internal::scalar_traits<size, false, __scalar_type__, enum_name>; \
      using base = ch::internal::ch_scalar<size>; \
      CH_ENUM_SCALAR_IMPL(__scalar_type__) \
      CH_ENUM_ASSIGN_IMPL(__scalar_type__) \
      CH_SCALAR_INTERFACE(__scalar_type__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<size, false, enum_name, __scalar_type__>; \
    using base = ch::internal::ch_logic<size>; \
    CH_ENUM_LOGIC_IMPL(enum_name) \
    CH_ENUM_ASSIGN_IMPL(enum_name) \
    CH_LOGIC_INTERFACE(enum_name) \
  }

#define CH_ENUM3(name, size, body) \
  CH_ENUM_IMPL(name, size, CH_REM body)

#define CH_ENUM2(name, body) \
  CH_ENUM_IMPL(name, CH_ENUM_SIZE(CH_REM body), CH_REM body)

#define GET_ENUM(_1, _2, _3, NAME, ...) NAME
#define CH_ENUM(...) GET_ENUM(__VA_ARGS__, CH_ENUM3, CH_ENUM2, ignore)(__VA_ARGS__)

