#pragma once

#include "ioport.h"
#include "struct.h"

#define CH_INTERFACE_DIR_EACH(a, i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)>::traits::direction

#define CH_INTERFACE_DIR(...) \
  ch_direction(CH_FOR_EACH(CH_INTERFACE_DIR_EACH, , CH_SEP_OR, __VA_ARGS__))

#define CH_INTERFACE_FLIP_DIR_EACH(a, i, x) \
  ch_flip_io<ch::internal::identity_t<CH_PAIR_L(x)>>::traits::direction

#define CH_INTERFACE_FLIP_DIR(...) \
  ch_direction(CH_FOR_EACH(CH_INTERFACE_FLIP_DIR_EACH, , CH_SEP_OR, __VA_ARGS__))

#define CH_INTERFACE_LOGIC_FIELD(a, i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)> CH_PAIR_R(x)

#define CH_INTERFACE_LOGIC_FLIP_FIELD(a, i, x) \
  ch_flip_io<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_INTERFACE_SYSTEM_COPY_CTOR(a, i, x) \
  CH_PAIR_R(x)(__other.CH_PAIR_R(x))

#define CH_INTERFACE_LOGIC_COPY_CTOR(a, i, x) \
  CH_PAIR_R(x)(__other.CH_PAIR_R(x))

#define CH_INTERFACE_LOGIC_COPY_CTOR2(a, i, x) \
  CH_PAIR_R(x)(__other.CH_PAIR_R(x), sloc)

#define CH_INTERFACE_LOGIC_CTOR_BODY(a, i, x) \
  CH_PAIR_R(x)(ch::internal::stringf("%s.%s", name.c_str(), CH_STRINGIZE(CH_PAIR_R(x))), sloc)

#define CH_INTERFACE_SYSTEM_CTOR_BODY(a, i, x) \
  CH_PAIR_R(x)(ch::internal::stringf("%s.%s", name.c_str(), CH_STRINGIZE(CH_PAIR_R(x))))

#define CH_INTERFACE_BIND_BODY(a, i, x) \
  this->CH_PAIR_R(x)(__other.CH_PAIR_R(x))

#define CH_INTERFACE_SYSTEM_FIELD(a, i, x) \
  ch_system_io<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_INTERFACE_SYSTEM_FLIP_FIELD(a, i, x) \
  ch_system_io<ch_flip_io<ch::internal::identity_t<CH_PAIR_L(x)>>> CH_PAIR_R(x)

#define CH_INTERFACE_MOVE_CTOR(a, i, x) \
  CH_PAIR_R(x)(std::move(__other.CH_PAIR_R(x)))

#define CH_INTERFACE_OSTREAM(a, i, x) \
  if (i) { __out << ", "; } \
  __out << CH_STRINGIZE(CH_PAIR_R(x)) << "=" << __in.CH_PAIR_R(x)

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_INTERFACE_SYSTEM_IMPL(type_name, interface_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const std::string& name = "io") \
    : CH_FOR_EACH(CH_INTERFACE_SYSTEM_CTOR_BODY, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  explicit type_name(const typename traits::logic_flip_io& __other) \
    : CH_FOR_EACH(CH_INTERFACE_SYSTEM_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(const type_name& __other) \
    : CH_FOR_EACH(CH_INTERFACE_SYSTEM_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(type_name&& __other) \
    : CH_FOR_EACH(CH_INTERFACE_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  void operator()(typename traits::flip_io& __other) { \
    CH_FOR_EACH(CH_INTERFACE_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  type_name& operator=(const type_name&) = delete; \
  type_name& operator=(type_name&&) = delete; \
  friend std::ostream& operator<<(std::ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_INTERFACE_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ")"; \
    return __out; \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_INTERFACE_LOGIC_IMPL(type_name, interface_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const std::string& name = "io", CH_SLOC) \
    : CH_FOR_EACH(CH_INTERFACE_LOGIC_CTOR_BODY, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  explicit type_name(const typename traits::flip_io& __other, CH_SLOC) \
    : CH_FOR_EACH(CH_INTERFACE_LOGIC_COPY_CTOR2, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  explicit type_name(const typename traits::system_flip_io& __other, CH_SLOC) \
    : CH_FOR_EACH(CH_INTERFACE_LOGIC_COPY_CTOR2, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(const type_name& __other) \
    : CH_FOR_EACH(CH_INTERFACE_LOGIC_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(type_name&& __other) \
    : CH_FOR_EACH(CH_INTERFACE_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  void operator()(typename traits::flip_io& __other) { \
    CH_FOR_EACH(CH_INTERFACE_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  type_name& operator=(const type_name&) = delete; \
  type_name& operator=(type_name&&) = delete; \
  friend ch_ostream& operator<<(ch_ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_INTERFACE_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ")"; \
    return __out; \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_DERIVED_INTERFACE_SYSTEM_IMPL(type_name, interface_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const std::string& name = "io") \
    : base(name) \
    , CH_FOR_EACH(CH_INTERFACE_SYSTEM_CTOR_BODY, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  explicit type_name(const typename traits::logic_flip_io& __other) \
    : base(__other) \
    , CH_FOR_EACH(CH_INTERFACE_SYSTEM_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(const type_name& __other) \
    : base(__other) \
    , CH_FOR_EACH(CH_INTERFACE_SYSTEM_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(type_name&& __other) \
    : base(std::move(__other)) \
    , CH_FOR_EACH(CH_INTERFACE_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  void operator()(typename traits::flip_io& __other) { \
    CH_FOR_EACH(CH_INTERFACE_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  type_name& operator=(const type_name&) = delete; \
  type_name& operator=(type_name&&) = delete; \
  friend std::ostream& operator<<(std::ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_INTERFACE_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ", "; \
    __out << CH_STRINGIZE(base) << "=" << reinterpret_cast<const base&>(__in); \
    __out << ")"; \
    return __out; \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_DERIVED_INTERFACE_LOGIC_IMPL(type_name, interface_name, field_body, ...) \
  CH_FOR_EACH(field_body, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  explicit type_name(const std::string& name = "io", CH_SLOC) \
    : base(name, sloc) \
    , CH_FOR_EACH(CH_INTERFACE_LOGIC_CTOR_BODY, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  explicit type_name(const typename traits::flip_io& __other, CH_SLOC) \
    : base(__other, sloc) \
    , CH_FOR_EACH(CH_INTERFACE_LOGIC_COPY_CTOR2, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  explicit type_name(const typename traits::system_flip_io& __other, CH_SLOC) \
    : base(__other, sloc) \
    , CH_FOR_EACH(CH_INTERFACE_LOGIC_COPY_CTOR2, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(const type_name& __other) \
    : base(__other) \
    , CH_FOR_EACH(CH_INTERFACE_LOGIC_COPY_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  type_name(type_name&& __other) \
    : base(std::move(__other)) \
    , CH_FOR_EACH(CH_INTERFACE_MOVE_CTOR, , CH_SEP_COMMA, __VA_ARGS__) { \
  } \
  void operator()(typename traits::flip_io& __other) { \
    base::operator()(__other); \
    CH_FOR_EACH(CH_INTERFACE_BIND_BODY, , CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
protected: \
  type_name& operator=(const type_name&) = delete; \
  type_name& operator=(type_name&&) = delete; \
  friend ch_ostream& operator<<(ch_ostream& __out, const type_name& __in) { \
    __out << "("; \
    CH_REVERSE_FOR_EACH(CH_INTERFACE_OSTREAM, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    __out << ", "; \
    __out << CH_STRINGIZE(base) << "=" << reinterpret_cast<const base&>(__in); \
    __out << ")"; \
    return __out; \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_INTERFACE_IMPL(interface_name, ...) \
  class interface_name { \
  private: \
    class __system_io__; \
    class __system_flip_io__; \
    class __logic_struct__; \
    class __system_struct__; \
    class __logic_flip_io__ { \
    public: \
      using traits = ch::internal::logic_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
        CH_INTERFACE_FLIP_DIR(__VA_ARGS__), __logic_flip_io__, interface_name, \
        __system_flip_io__, __system_io__, __system_struct__, __logic_struct__>; \
      CH_BASIC_INTERFACE_LOGIC_IMPL(__logic_flip_io__, interface_name, CH_INTERFACE_LOGIC_FLIP_FIELD, __VA_ARGS__) \
    }; \
    class __system_io__ { \
    public: \
      using traits = ch::internal::system_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
        CH_INTERFACE_DIR(__VA_ARGS__), __system_io__, __system_flip_io__, \
        interface_name, __logic_flip_io__, __system_struct__, __logic_struct__>; \
      CH_BASIC_INTERFACE_SYSTEM_IMPL(__system_io__, interface_name, CH_INTERFACE_SYSTEM_FIELD, __VA_ARGS__) \
    }; \
    class __system_flip_io__ { \
    public: \
      using traits = ch::internal::system_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
        CH_INTERFACE_DIR(__VA_ARGS__), __system_flip_io__, __system_io__, \
        __logic_flip_io__, interface_name, __system_struct__, __logic_struct__>; \
      CH_BASIC_INTERFACE_SYSTEM_IMPL(__system_flip_io__, interface_name, CH_INTERFACE_SYSTEM_FLIP_FIELD, __VA_ARGS__) \
    }; \
    class __system_struct__ { \
    public: \
      using traits = ch::internal::system_traits<CH_STRUCT_SIZE(__VA_ARGS__), false, __system_struct__, __logic_struct__>; \
      CH_BASIC_STRUCT_SYSTEM_IMPL(__system_struct__, interface_name, __VA_ARGS__) \
      CH_SYSTEM_INTERFACE(__system_struct__) \
    }; \
    class __logic_struct__ { \
    public: \
      using traits = ch::internal::logic_traits<CH_STRUCT_SIZE(__VA_ARGS__), false, __logic_struct__, __system_struct__>; \
      CH_BASIC_STRUCT_LOGIC_IMPL(__logic_struct__, interface_name, __VA_ARGS__) \
      CH_LOGIC_INTERFACE(__logic_struct__) \
    }; \
  public: \
    using traits = ch::internal::logic_io_traits<CH_STRUCT_SIZE(__VA_ARGS__), \
      CH_INTERFACE_DIR(__VA_ARGS__), interface_name, __logic_flip_io__, \
      __system_io__, __system_flip_io__, __system_struct__, __logic_struct__>; \
    CH_BASIC_INTERFACE_LOGIC_IMPL(interface_name, interface_name, CH_INTERFACE_LOGIC_FIELD, __VA_ARGS__) \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_DERIVED_INTERFACE_IMPL(interface_name, parent, ...) \
  class interface_name : public parent { \
  private: \
    class __system_io__; \
    class __system_flip_io__; \
    class __logic_struct__; \
    class __system_struct__; \
    class __logic_flip_io__ : public ch_flip_io<parent> { \
    public: \
      using base = ch_flip_io<parent>; \
      using traits = ch::internal::logic_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
        ch_direction_v<base> | CH_INTERFACE_FLIP_DIR(__VA_ARGS__), __logic_flip_io__, interface_name, \
        __system_flip_io__, __system_io__, __system_struct__, __logic_struct__>; \
      CH_DERIVED_INTERFACE_LOGIC_IMPL(__logic_flip_io__, interface_name, CH_INTERFACE_LOGIC_FLIP_FIELD, __VA_ARGS__) \
    }; \
    class __system_io__ : public ch_system_io<parent> { \
    public: \
      using base = ch_system_io<parent>; \
      using traits = ch::internal::system_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
        ch_direction_v<base> | CH_INTERFACE_FLIP_DIR(__VA_ARGS__), __system_io__, __system_flip_io__, \
        interface_name, __logic_flip_io__, __system_struct__, __logic_struct__>; \
      CH_DERIVED_INTERFACE_SYSTEM_IMPL(__system_io__, interface_name, CH_INTERFACE_SYSTEM_FIELD, __VA_ARGS__) \
    }; \
    class __system_flip_io__ : public ch_system_io<ch_flip_io<parent>> { \
    public: \
      using base = ch_system_io<ch_flip_io<parent>>; \
      using traits = ch::internal::system_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
        ch_direction_v<base> | CH_INTERFACE_DIR(__VA_ARGS__), __system_flip_io__, __system_io__, \
        __logic_flip_io__, interface_name, __system_struct__, __logic_struct__>; \
      CH_DERIVED_INTERFACE_SYSTEM_IMPL(__system_flip_io__, interface_name, CH_INTERFACE_SYSTEM_FLIP_FIELD, __VA_ARGS__) \
    }; \
    class __system_struct__ : public ch_system_t<parent> { \
    public: \
      using base = ch_system_t<parent>; \
      using traits = ch::internal::system_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), false, __system_struct__, __logic_struct__>; \
      CH_DERIVED_STRUCT_SYSTEM_IMPL(__system_struct__, interface_name, __VA_ARGS__) \
      CH_SYSTEM_INTERFACE(__system_struct__) \
    }; \
    class __logic_struct__ : public ch_logic_t<parent> { \
    public: \
      using base = ch_logic_t<parent>; \
      using traits = ch::internal::logic_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), false, __logic_struct__, __system_struct__>; \
      CH_DERIVED_STRUCT_LOGIC_IMPL(__logic_struct__, interface_name, __VA_ARGS__) \
      CH_LOGIC_INTERFACE(__logic_struct__) \
    }; \
  public: \
    using base = parent; \
    using traits = ch::internal::logic_io_traits<ch_width_v<base> + CH_STRUCT_SIZE(__VA_ARGS__), \
      ch_direction_v<base> | CH_INTERFACE_DIR(__VA_ARGS__), interface_name, __logic_flip_io__, \
      __system_io__,  __system_flip_io__, __system_struct__, __logic_struct__>; \
    CH_DERIVED_INTERFACE_LOGIC_IMPL(interface_name, interface_name, CH_INTERFACE_LOGIC_FIELD, __VA_ARGS__) \
  }

///////////////////////////////////////////////////////////////////////////////

#define CH_BASIC_INTERFACE(name, body) \
  CH_BASIC_INTERFACE_IMPL(name, CH_REM body)

#define CH_DERIVED_INTERFACE(name, parent, body) \
  CH_DERIVED_INTERFACE_IMPL(name, parent, CH_REM body)

#define GET_INTERFACE(_1, _2, _3, NAME, ...) NAME
#define CH_INTERFACE(...) GET_INTERFACE(__VA_ARGS__, CH_DERIVED_INTERFACE, CH_BASIC_INTERFACE, ignore)(__VA_ARGS__)

#define CH_IO(...) \
  CH_BASIC_INTERFACE_IMPL(io_type, __VA_ARGS__); \
  io_type io

#define CH_SCIO(...) \
  CH_BASIC_INTERFACE_IMPL(io_type, __VA_ARGS__); \
  ch_system_io<io_type> io

#define CH_FLIP(x) (ch_flip_io<x>)
