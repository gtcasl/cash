#pragma once

#include "bit.h"
#include "bus.h"

#define CH_STRUCT_SIZE(i, x) \
  cash::internal::traits<CH_PAIR_L(x)>::bitcount

#define CH_STRUCT_FIELD(i, x) \
  typename cash::internal::traits<CH_PAIR_L(x)>::value_type CH_PAIR_R(x)

#define CH_STRUCT_BUS_FIELD(i, x) \
  typename cash::internal::traits<CH_PAIR_L(x)>::bus_type CH_PAIR_R(x)

#define CH_STRUCT_COPY_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_STRUCT_FIELD_CTOR_TMPL(i, x) \
  typename __T##i

#define CH_STRUCT_FIELD_CTOR_REQUIRES(i, x) \
  CH_REQUIRES(cash::internal::is_cast_convertible<__T##i, typename cash::internal::traits<CH_PAIR_L(x)>::value_type>::value)

#define CH_STRUCT_FIELD_CTOR_ARGS(i, x) \
  const __T##i& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_STRUCT_FIELD_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(CH_CONCAT(_,CH_PAIR_R(x)))

#define CH_STRUCT_ASSIGN(i, x) \
  this->CH_PAIR_R(x) = __rhs__.CH_PAIR_R(x)

#define CH_STRUCT_CLONE(i, x) \
  CH_PAIR_R(x).clone()

#define CH_STRUCT_READ(i, x) \
  if (__offset__ < cash::internal::traits<CH_PAIR_L(x)>::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, cash::internal::traits<CH_PAIR_L(x)>::bitcount - __offset__); \
    cash::internal::read_data(CH_PAIR_R(x), __inout__, __offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __offset__ = cash::internal::traits<CH_PAIR_L(x)>::bitcount; \
  } \
  __offset__ -= cash::internal::traits<CH_PAIR_L(x)>::bitcount
          
#define CH_STRUCT_WRITE(i, x) \
  if (__dst_offset__ < cash::internal::traits<CH_PAIR_L(x)>::bitcount) { \
    size_t __len__ = std::min<size_t>(__length__, cash::internal::traits<CH_PAIR_L(x)>::bitcount - __dst_offset__); \
    cash::internal::write_data(CH_PAIR_R(x), __dst_offset__, __in__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __src_offset__ += __len__; \
    __dst_offset__ = cash::internal::traits<CH_PAIR_L(x)>::bitcount; \
  } \
  __dst_offset__ -= cash::internal::traits<CH_PAIR_L(x)>::bitcount

#define CH_STRUCT_BUS_IMPL(name, ...) \
  namespace cash { namespace internal { \
    template <> \
    struct traits<name> { \
      static constexpr unsigned bitcount = CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__); \
      static constexpr bool readonly = false; \
      using data_type  = snode; \
      using value_type = name; \
      using const_type = name; \
      using bus_type   = name; \
    }; \
  } } \
  class name : public cash::internal::ch_busbase<name> { \
  public: \
    using base = cash::internal::ch_busbase<name>; \
    using base::operator=; \
    using data_type = typename base::data_type; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& __rhs__) { base::operator=(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    template <typename __T__, CH_REQUIRES(cash::internal::is_scalar<__T__>::value)> \
    explicit name(__T__ __rhs__) { base::operator=(__rhs__); } \
    name& operator=(const name& __rhs__) { \
      CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_FOR_EACH(CH_STRUCT_BUS_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
  protected: \
    void read_data(cash::internal::nodelist<data_type>& __inout__, size_t __offset__, size_t __length__) const { \
      CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_type>& __in__, size_t __src_offset__, size_t __length__) { \
      CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    template <typename __T__> friend class cash::internal::typebase; \
  };\

#define CH_STRUCT_IMPL(name, const_name, bus_name, is_readonly, ...) \
  namespace cash { namespace internal { \
    template <> \
    struct traits<name> { \
      static constexpr unsigned bitcount = CH_FOR_EACH(CH_STRUCT_SIZE, CH_SEP_PLUS, __VA_ARGS__); \
      static constexpr bool readonly = is_readonly; \
      using data_type  = lnode; \
      using value_type = name; \
      using const_type = const_name; \
      using bus_type   = bus_name; \
    }; \
  } } \
  class name : public cash::internal::ch_bitbase<name> { \
  public:\
    using base = cash::internal::ch_bitbase<name>; \
    using base::operator=; \
    using data_type = typename base::data_type; \
    name() {} \
    name(const name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    name(const base& __rhs__) { base::operator=(__rhs__); } \
    template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
              CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
    explicit name(CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_ARGS, CH_SEP_COMMA, __VA_ARGS__)) \
      : CH_FOR_EACH(CH_STRUCT_FIELD_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
    template <typename __T__, CH_REQUIRES(cash::internal::is_scalar<__T__>::value)> \
    explicit name(__T__ __rhs__) { base::operator=(__rhs__); } \
    name& operator=(const name& __rhs__) { \
      CH_FOR_EACH(CH_STRUCT_ASSIGN, CH_SEP_SEMICOLON, __VA_ARGS__); \
      return *this; \
    } \
    CH_FOR_EACH(CH_STRUCT_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
    name clone() const { \
      return name(CH_REVERSE_FOR_EACH(CH_STRUCT_CLONE, CH_SEP_COMMA, __VA_ARGS__)); \
    } \
  protected: \
    void read_data(cash::internal::nodelist<data_type>& __inout__, size_t __offset__, size_t __length__) const { \
      CH_FOR_EACH(CH_STRUCT_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    void write_data(size_t __dst_offset__, const cash::internal::nodelist<data_type>& __in__, size_t __src_offset__, size_t __length__) { \
      CH_FOR_EACH(CH_STRUCT_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
      CH_ABORT("invalid subscript index"); \
    } \
    template <typename __T__> friend class cash::internal::typebase; \
  }

#define CH_STRUCT(name, body) \
  class name; \
  class CH_UNAME(const, name); \
  class CH_UNAME(bus, name); \
  CH_STRUCT_BUS_IMPL(CH_UNAME(bus, name), CH_REM body); \
  CH_STRUCT_IMPL(name, CH_UNAME(const, name), CH_UNAME(bus, name), false, CH_REM body); \
  CH_STRUCT_IMPL(CH_UNAME(const, name), CH_UNAME(const, name), CH_UNAME(bus, name), true, CH_REM body)
