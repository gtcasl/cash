#pragma once

#include "logic.h"
#include "system.h"

#define CH_STRUCT_SIZE_EACH(a, i, x) \
  ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_STRUCT_SIZE(...) \
  (CH_FOR_EACH(CH_STRUCT_SIZE_EACH, , CH_SEP_PLUS, __VA_ARGS__))

#define CH_STRUCT_FIELD_OFFSET(a, i, x) \
  CH_CONCAT(__field_offset, CH_INC(i)) = __field_offset##i + ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>

#define CH_STRUCT_SYSTEM_FIELD(a, i, x) \
  ch_system_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_LOGIC_FIELD(a, i, x) \
  ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_STRUCT_SYSTEM_FIELD_CTOR_ARGS(a, i, x) \
  const ch_system_t<ch::internal::identity_t<CH_PAIR_L(x)>>& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_LOGIC_FIELD_CTOR_ARGS(a, i, x) \
  const ch_logic_t<ch::internal::identity_t<CH_PAIR_L(x)>>& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_SYSTEM_CTOR(a, i, x) \
  CH_PAIR_R(x)(ch::internal::make_system_buffer( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, __field_offset##i))

#define CH_STRUCT_LOGIC_CTOR(a, i, x) \
  CH_PAIR_R(x)(ch::internal::make_logic_buffer( \
    ch_width_v<ch::internal::identity_t<CH_PAIR_L(x)>>, buffer, __field_offset##i, \
    ch::internal::source_info(buffer.sloc(), CH_STRINGIZE(CH_PAIR_R(x)))))

#define CH_STRUCT_FIELD_CTOR_INIT(a, i, x) \
  CH_PAIR_R(x) = CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_SYSTEM_SOURCE(i, x) \
  ch::internal::system_accessor::source(CH_PAIR_R(x))

#define CH_STRUCT_LOGIC_SOURCE(i, x) \
  ch::internal::logic_accessor::source(CH_PAIR_R(x))

#define CH_STRUCT_OSTREAM(a, i, x) \
  if (i) { __out << ", "; } \
  __out << CH_STRINGIZE(CH_PAIR_R(x)) << "=" << __in.CH_PAIR_R(x)

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_STRUCT_SYSTEM_IMPL(type_name, struct_name, ...) \
private: \
  enum { __field_offset0 = 0, \
         CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(CH_STRUCT_SYSTEM_FIELD, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const ch::internal::system_buffer& buffer = \
    ch::internal::make_system_buffer(traits::bitwidth)) \
    : CH_FOR_EACH(CH_STRUCT_SYSTEM_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(CH_REVERSE_FOR_EACH(CH_STRUCT_SYSTEM_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__)) \
    : type_name(ch::internal::make_system_buffer(traits::bitwidth)) { \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  type_name(const type_name& __other) \
    : type_name(ch::internal::make_system_buffer(traits::bitwidth)) { \
    this->operator=(__other); \
  } \
  type_name(type_name&& __other) \
    : type_name(ch::internal::system_accessor::move(__other)) { \
  } \
  type_name& operator=(const type_name& __other) { \
    ch::internal::system_accessor::assign(*this, __other); \
    return *this; \
  } \
  type_name& operator=(type_name&& __other) { \
    ch::internal::system_accessor::move(*this, std::move(__other)); \
    return *this; \
  } \
protected: \
  const ch::internal::system_buffer& __buffer() const { \
    return CH_STRUCT_SYSTEM_SOURCE(0, CH_FIRST_ARG(__VA_ARGS__)); \
  } \
  friend std::ostream& operator<<(std::ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_STRUCT_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ")"; \
    return __out; \
  } \
  friend class ch::internal::system_accessor; \
public:

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_STRUCT_LOGIC_IMPL(type_name, struct_name, ...) \
private: \
  enum { __field_offset0 = 0, \
           CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(CH_STRUCT_LOGIC_FIELD, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const ch::internal::logic_buffer& buffer = \
    ch::internal::make_logic_buffer(traits::bitwidth, CH_CUR_SRC_INFO)) \
    : CH_FOR_EACH(CH_STRUCT_LOGIC_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(CH_REVERSE_FOR_EACH(CH_STRUCT_LOGIC_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__), CH_SRC_INFO) \
    : type_name(ch::internal::make_logic_buffer(traits::bitwidth, srcinfo)) { \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  type_name(const type_name& __other, CH_SRC_INFO) \
    : type_name(ch::internal::make_logic_buffer(traits::bitwidth, srcinfo)) { \
    this->operator=(__other); \
  } \
  type_name(type_name&& __other) \
    : type_name(ch::internal::logic_accessor::move(__other)) { \
  } \
  type_name& operator=(const type_name& __other) { \
    ch::internal::logic_accessor::assign(*this, __other); \
    return *this; \
  } \
  type_name& operator=(type_name&& __other) { \
    ch::internal::logic_accessor::move(*this, std::move(__other)); \
    return *this; \
  } \
protected: \
  const ch::internal::logic_buffer& __buffer() const { \
    return CH_STRUCT_LOGIC_SOURCE(0, CH_FIRST_ARG(__VA_ARGS__)); \
  } \
  friend ch_ostream& operator<<(ch_ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_STRUCT_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ")"; \
    return __out; \
  } \
  friend class ch::internal::logic_accessor; \
public:

///////////////////////////////////////////////////////////////////////////////

#define CH_DERIVED_STRUCT_SYSTEM_IMPL(type_name, struct_name, ...) \
private: \
  enum { __field_offset0 = ch_width_v<base>, \
         CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(CH_STRUCT_SYSTEM_FIELD, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const ch::internal::system_buffer& buffer = \
    ch::internal::make_system_buffer(traits::bitwidth)) \
    : base(buffer) \
    , CH_FOR_EACH(CH_STRUCT_SYSTEM_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(CH_REVERSE_FOR_EACH(CH_STRUCT_SYSTEM_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__), const base& __base) \
    : type_name(ch::internal::make_system_buffer(traits::bitwidth)) { \
    ch::internal::system_accessor::write(*this, 0, __base, 0, ch_width_v<base>); \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  type_name(const type_name& __other) \
    : type_name(ch::internal::make_system_buffer(traits::bitwidth)) { \
    this->operator=(__other); \
  } \
  type_name(type_name&& __other) \
    : type_name(ch::internal::system_accessor::move(__other)) { \
  } \
  type_name& operator=(const type_name& __other) { \
    ch::internal::system_accessor::assign(*this, __other); \
    return *this; \
  } \
  type_name& operator=(type_name&& __other) { \
    ch::internal::system_accessor::move(*this, std::move(__other)); \
    return *this; \
  } \
protected: \
  const ch::internal::system_buffer& __buffer() const { \
    return base::__buffer(); \
  } \
  friend std::ostream& operator<<(std::ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_STRUCT_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ", "; \
    __out << CH_STRINGIZE(base) << "=" << reinterpret_cast<const base&>(__in); \
    __out << ")"; \
    return __out; \
  } \
  friend class ch::internal::system_accessor; \
public:

///////////////////////////////////////////////////////////////////////////////

#define CH_DERIVED_STRUCT_LOGIC_IMPL(type_name, struct_name, ...) \
private: \
  enum { __field_offset0 = ch_width_v<base>, \
         CH_FOR_EACH(CH_STRUCT_FIELD_OFFSET, , CH_SEP_COMMA, __VA_ARGS__) }; \
public: \
  CH_FOR_EACH(CH_STRUCT_LOGIC_FIELD, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const ch::internal::logic_buffer& buffer = \
    ch::internal::make_logic_buffer(traits::bitwidth, CH_CUR_SRC_INFO)) \
    : base(buffer) \
    , CH_FOR_EACH(CH_STRUCT_LOGIC_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(CH_REVERSE_FOR_EACH(CH_STRUCT_LOGIC_FIELD_CTOR_ARGS, , CH_SEP_COMMA, __VA_ARGS__), const base& __base, CH_SRC_INFO) \
    : type_name(ch::internal::make_logic_buffer(traits::bitwidth, srcinfo)) { \
    ch::internal::logic_accessor::write(*this, 0, __base, 0, ch_width_v<base>); \
    CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_INIT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  type_name(const type_name& __other, CH_SRC_INFO) \
    : type_name(ch::internal::make_logic_buffer(traits::bitwidth, srcinfo)) { \
    this->operator=(__other); \
  } \
  type_name(type_name&& __other) \
    : type_name(ch::internal::logic_accessor::move(__other)) { \
  } \
  type_name& operator=(const type_name& __other) { \
    ch::internal::logic_accessor::assign(*this, __other); \
    return *this; \
  } \
  type_name& operator=(type_name&& __other) { \
    ch::internal::logic_accessor::move(*this, std::move(__other)); \
    return *this; \
  } \
protected: \
  const ch::internal::logic_buffer& __buffer() const { \
    return base::__buffer(); \
  } \
  friend ch_ostream& operator<<(ch_ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_STRUCT_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ", "; \
    __out << CH_STRINGIZE(base) << "=" << reinterpret_cast<const base&>(__in); \
    __out << ")"; \
    return __out; \
  } \
  friend class ch::internal::logic_accessor; \
public:

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_STRUCT_IMPL(struct_name, ...) \
  class struct_name { \
  private: \
    class __system_type__ { \
    public: \
      using traits = ch::internal::system_traits<CH_STRUCT_SIZE(__VA_ARGS__), false, __system_type__, struct_name>; \
      CH_BASIC_STRUCT_SYSTEM_IMPL(__system_type__, struct_name, __VA_ARGS__) \
      CH_SYSTEM_INTERFACE(__system_type__) \
    }; \
  public: \
    using traits = ch::internal::logic_traits<CH_STRUCT_SIZE(__VA_ARGS__), false, struct_name, __system_type__>; \
    CH_BASIC_STRUCT_LOGIC_IMPL(struct_name, struct_name, __VA_ARGS__) \
    CH_LOGIC_INTERFACE(struct_name) \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_DERIVED_STRUCT_IMPL(struct_name, parent, ...) \
  class struct_name : public parent { \
  private: \
    class __system_type__ : public ch_system_t<parent> { \
    public: \
      using base = ch_system_t<parent>; \
      using traits = ch::internal::system_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), false, __system_type__, struct_name>; \
      CH_DERIVED_STRUCT_SYSTEM_IMPL(__system_type__, struct_name, __VA_ARGS__) \
      CH_SYSTEM_INTERFACE(__system_type__) \
    }; \
  public: \
    using base = parent; \
    using traits = ch::internal::logic_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), false, struct_name, __system_type__>; \
    CH_DERIVED_STRUCT_LOGIC_IMPL(struct_name, struct_name, __VA_ARGS__) \
    CH_LOGIC_INTERFACE(struct_name) \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_STRUCT(name, body) \
  CH_BASIC_STRUCT_IMPL(name, CH_REM body)

#define CH_DERIVED_STRUCT(name, parent, body) \
  CH_DERIVED_STRUCT_IMPL(name, parent, CH_REM body)

#define GET_STRUCT(_1, _2, _3, NAME, ...) NAME
#define CH_STRUCT(...) GET_STRUCT(__VA_ARGS__, CH_DERIVED_STRUCT, CH_BASIC_STRUCT, ignore)(__VA_ARGS__)
