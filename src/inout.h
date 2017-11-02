#pragma once

#include "port.h"

#define CH_INOUT_DIRECTION_EACH(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)>::traits::direction

#define CH_INOUT_DIRECTION(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_DIRECTION_EACH, CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_FLIP_DIRECTION_EACH(i, x) \
  ch_flip_t<ch::internal::identity_t<CH_PAIR_L(x)>>::traits::direction

#define CH_INOUT_FLIP_DIRECTION(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_FLIP_DIRECTION_EACH, CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_FIELD(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)> CH_PAIR_R(x)

#define CH_INOUT_FLIP_FIELD(i, x) \
  ch_flip_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_INOUT_COPY_CTOR(i, x) \
  CH_PAIR_R(x)(rhs.CH_PAIR_R(x))

#define CH_INOUT_CTOR_BODY(i, x) \
  CH_PAIR_R(x)(ch::internal::fstring("%s_%s", name.c_str(), CH_STRINGIZE(CH_PAIR_R(x))).c_str())

#define CH_INOUT_BIND_BODY(i, x) \
  this->CH_PAIR_R(x)(rhs.CH_PAIR_R(x))

#define CH_INOUT_BUFFER_FIELD(i, x) \
  ch::internal::buffer_type_t<ch::internal::identity_t<CH_PAIR_L(x)>> CH_PAIR_R(x)

#define CH_INOUT_FLIP_BUFFER_FIELD(i, x) \
  ch::internal::buffer_type_t<ch_flip_t<ch::internal::identity_t<CH_PAIR_L(x)>>> CH_PAIR_R(x)


#define CH_INOUT_BODY_IMPL2(inout_name, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  inout_name(const std::string& name = "io") \
    : CH_FOR_EACH(CH_INOUT_CTOR_BODY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const typename traits::flip_type& rhs) \
    : CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& rhs) \
    : CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& rhs) \
    : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  void operator()(const typename traits::flip_type& rhs) const { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  }

#define CH_INOUT_BODY_IMPL3(inout_name, parent, field_body, ...) \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  inout_name(const std::string& name = "io") \
    : parent(name) \
    , CH_FOR_EACH(CH_INOUT_CTOR_BODY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const typename traits::flip_type& rhs) \
    : parent(rhs) \
    , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& rhs) \
    : parent(rhs) \
    , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& rhs) \
    : parent(std::move(rhs)) \
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  void operator()(const typename traits::flip_type& rhs) const { \
    parent::operator()(rhs); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  }

#define CH_INOUT_BUFFER_READ(i, x) \
  if (__src_offset__ < ch_bitwidth_v<CH_PAIR_L(x)>) { \
    size_t __len__ = std::min<size_t>(__length__, ch_bitwidth_v<CH_PAIR_L(x)> - __src_offset__); \
    CH_PAIR_R(x).read(__dst_offset__, __out__, __out_cbsize__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __dst_offset__ += __len__; \
    __src_offset__ = ch_bitwidth_v<CH_PAIR_L(x)>; \
  } \
  __src_offset__ -= ch_bitwidth_v<CH_PAIR_L(x)>

#define CH_INOUT_BUFFER_WRITE(i, x) \
  if (__dst_offset__ < ch_bitwidth_v<CH_PAIR_L(x)>) { \
    size_t __len__ = std::min<size_t>(__length__, ch_bitwidth_v<CH_PAIR_L(x)> - __dst_offset__); \
    CH_PAIR_R(x).write(__dst_offset__, __in__, __in_cbsize__, __src_offset__, __len__); \
    __length__ -= __len__; \
    if (0 == __length__) \
      return; \
    __src_offset__ += __len__; \
    __dst_offset__ = ch_bitwidth_v<CH_PAIR_L(x)>; \
  } \
  __dst_offset__ -= ch_bitwidth_v<CH_PAIR_L(x)>

#define CH_INOUT_BUFFER_ACCESS(...) \
  void read(uint32_t __dst_offset__, \
            void* __out__, \
            uint32_t __out_cbsize__, \
            uint32_t __src_offset__, \
            uint32_t __length__) const override { \
    CH_FOR_EACH(CH_INOUT_BUFFER_READ, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void write(uint32_t __dst_offset__, \
             const void* __in__, \
             uint32_t __in_cbsize__, \
             uint32_t __src_offset__, \
             uint32_t __length__) override { \
     CH_FOR_EACH(CH_INOUT_BUFFER_WRITE, CH_SEP_SEMICOLON, __VA_ARGS__); \
  }

#define CH_INOUT_IMPL2(inout_name, ...) \
  class inout_name { \
  private: \
    CH_STRUCT_IMPL2(__logic_type__, __VA_ARGS__); \
    class __flop_buffer_type__; \
    class __flip_type__; \
    class __flip_buffer_type__ : public ch::internal::scalar_buffer_io { \
    public: \
      using base = ch::internal::scalar_buffer_io; \
      CH_FOR_EACH(CH_INOUT_FLIP_BUFFER_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
      __flip_buffer_type__(__flip_type__& rhs) \
        : base(__logic_type__::traits::bitwidth) \
        , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BUFFER_ACCESS(__VA_ARGS__) \
    }; \
    class __flip_type__ { \
    public: \
      using traits = ch::internal::io_traits<__flip_type__, \
        CH_INOUT_FLIP_DIRECTION(__VA_ARGS__), inout_name, __flip_buffer_type__, __logic_type__>; \
      CH_INOUT_BODY_IMPL2(__flip_type__, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    protected: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
      __flip_type__& operator=(__flip_type__&&) = delete; \
    }; \
    class __flop_buffer_type__ : public ch::internal::scalar_buffer_io { \
    public: \
      using base = ch::internal::scalar_buffer_io; \
      CH_FOR_EACH(CH_INOUT_BUFFER_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
      __flop_buffer_type__(inout_name& rhs) \
        : base(__logic_type__::traits::bitwidth) \
        , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BUFFER_ACCESS(__VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::io_traits<inout_name, \
      CH_INOUT_DIRECTION(__VA_ARGS__), __flip_type__, __flop_buffer_type__, __logic_type__>; \
    CH_INOUT_BODY_IMPL2(inout_name, CH_INOUT_FIELD, __VA_ARGS__) \
  protected: \
    inout_name& operator=(const inout_name&) = delete; \
    inout_name& operator=(inout_name&&) = delete; \
  }

#define CH_INOUT_IMPL3(inout_name, parent, ...) \
  class inout_name : public parent { \
  private: \
    CH_STRUCT_IMPL3(__logic_type__, parent, __VA_ARGS__); \
    class __flop_buffer_type__; \
    class __flip_type__; \
    class __flip_buffer_type__ : public ch::internal::scalar_buffer_io { \
    public: \
      using base = ch::internal::scalar_buffer_io; \
      ch::internal::buffer_type_t<ch_flip_t<parent>> __parent__; \
      CH_FOR_EACH(CH_INOUT_FLIP_BUFFER_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
      __flip_buffer_type__(__flip_type__& rhs) \
        : base(__logic_type__::traits::bitwidth), __parent__(rhs) \
        , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BUFFER_ACCESS((ch_flip_t<parent>) __parent__, __VA_ARGS__) \
    }; \
    class __flip_type__ : public ch_flip_t<parent> { \
    public: \
      using traits = ch::internal::io_traits<__flip_type__, \
        ch_direction(ch_direction_v<ch_flip_t<parent>> | CH_INOUT_FLIP_DIRECTION(__VA_ARGS__)), \
        inout_name, __flip_buffer_type__, __logic_type__>; \
      CH_INOUT_BODY_IMPL3(__flip_type__, ch_flip_t<parent>, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
      __flip_type__& operator=(__flip_type__&&) = delete; \
    }; \
    class __flop_buffer_type__ : public ch::internal::scalar_buffer_io { \
    public: \
      using base = ch::internal::scalar_buffer_io; \
      ch::internal::buffer_type_t<parent> __parent__; \
      CH_FOR_EACH(CH_INOUT_BUFFER_FIELD, CH_SEP_SEMICOLON, __VA_ARGS__); \
      __flop_buffer_type__(inout_name& rhs) \
        : base(__logic_type__::traits::bitwidth), __parent__(rhs) \
        , CH_FOR_EACH(CH_INOUT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BUFFER_ACCESS((parent) __parent__, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::io_traits<inout_name, \
      ch_direction(ch_direction_v<parent> | CH_INOUT_DIRECTION(__VA_ARGS__)), \
      __flip_type__, __flop_buffer_type__, __logic_type__>; \
    CH_INOUT_BODY_IMPL3(inout_name, parent, CH_INOUT_FIELD, __VA_ARGS__) \
  private: \
    inout_name& operator=(const inout_name&) = delete; \
    inout_name& operator=(inout_name&&) = delete; \
  }

#define CH_INOUT2(name, body) \
  CH_INOUT_IMPL2(name, CH_REM body)

#define CH_INOUT3(name, parent, body) \
  CH_INOUT_IMPL3(name, parent, CH_REM body)

#define GET_INOUT(_1, _2, _3, NAME, ...) NAME
#define CH_INOUT(...) GET_INOUT(__VA_ARGS__, CH_INOUT3, CH_INOUT2)(__VA_ARGS__)

#define CH_IO(...) \
  CH_INOUT_IMPL2(__io_type__, __VA_ARGS__); \
  __io_type__ io

#define CH_FLIP(x) (ch_flip_t<x>)
