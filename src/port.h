#pragma once

#include "struct.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const std::string& name, uint32_t size);

lnodeimpl* createOutputNode(const std::string& name, const lnode& src);

void bindInput(const lnode& input, const lnode& src);

void bindOutput(const lnode& dst, const lnode& output);

///////////////////////////////////////////////////////////////////////////////

enum class ch_direction {
  in    = 0x1,
  out   = 0x2,
  inout = 0x3,
};

template <typename IoType, ch_direction Direction, typename FlipType, typename PortType, typename LogicType>
struct io_traits {
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using port_type   = PortType;
  using logic_type  = LogicType;
  using const_type  = typename LogicType::traits::const_type;
  using value_type  = typename LogicType::traits::value_type;
  using scalar_type = typename LogicType::traits::scalar_type;
};

template <typename T>
struct is_io_traits : std::false_type {};

template <typename IoType, ch_direction Direction, typename FlipType, typename PortType, typename LogicType>
struct is_io_traits<io_traits<IoType, Direction, FlipType, PortType, LogicType>> : std::true_type {};

template <typename T>
using is_io_type = is_io_traits<typename T::traits>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class connector {
public:
  connector(const T& obj) : obj_(obj) {}

  template <typename U>
  void bind(const connector<U>& rhs) const {
    obj_(rhs.obj_);
  }

protected:     
  const T& obj_;

  template <typename U> friend class connector;
};

template <typename U, typename V>
void operator%(const connector<U>& c1, const connector<V>& c2) {
  c1.bind(c2);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in;

template <typename T>
class ch_out;

template <typename T>
class input_port;

template <typename T>
class output_port;

template <typename T>
class input_port {
public:
  static constexpr unsigned bitsize = T::bitsize;

  input_port(ch_in<T>& in) : in_(in) {}

  void operator()(const ch_in<T>& in) const {
    bindInput(in_.input_, get_lnode(in));
  }

  void operator()(const input_port& in) const {
    bindInput(in_.input_, get_lnode(in.in_));
  }

  void operator()(const output_port<T>& out) const {
    bindInput(in_.input_, get_lnode(out.out_));
  }

  void operator()(const bitbase<T::bitsize>& value) const {
    bindInput(in_.input_, get_lnode(value));
  }

  template <typename U, CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(const U& value) const {
    bindInput(in_.input_, get_lnode<U, T::bitsize>(value));
  }

  auto operator()() const {
    return ch::internal::connector<decltype(*this)>(*this);
  }

protected:
  ch_in<T>& in_;

  lnode& get_input() const {
    return in_.input_;
  }

  friend std::ostream& operator<<(std::ostream& out, const input_port& port) {
    return out << port.get_input();
  }

  template <typename U> friend class output_port;
  template <typename V, typename U> friend V ch_peek(const input_port<U>& port);
  template <typename V, typename U> friend void ch_poke(const input_port<U>& port, const V& value);
  template <typename U> friend void ch_peek(const input_port<U>& port, uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length);
  template <typename U> friend void ch_poke(const input_port<U>& port, uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length);
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class output_port {
public:
  static constexpr unsigned bitsize = T::bitsize;

  output_port(const ch_out<T>& out) : out_(out) {}

  void operator()(const ch_out<T>& out) const {
    bindOutput(get_lnode(out), out_.output_);
  }

  void operator()(const output_port& out) const {
    bindOutput(get_lnode(out.out_), out_.output_);
  }

  void operator()(const input_port<T>& in) const {
    bindOutput(in.get_input(), out_.output_);
  }

  template <typename U, CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(U& value) const {
    bindOutput(get_lnode(value), out_.output_);
  }

  auto operator()() const {
    return ch::internal::connector<decltype(*this)>(*this);
  }

protected:
  const ch_out<T>& out_;

  const lnode& get_output() const {
    return out_.output_;
  }

  friend std::ostream& operator<<(std::ostream& out, const output_port& port) {
    return out << port.get_output();
  }

  template <typename U> friend class input_port;
  template <typename V, typename U> friend V ch_peek(const output_port<U>& port);
  template <typename U> friend void ch_peek(const output_port<U>& port, uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length);
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in final : public T::traits::const_type {
public:
  static_assert(!is_io_type<T>::value, "invalid nested type");
  using traits = io_traits<ch_in, ch_direction::in, ch_out<T>, input_port<T>, T>;

  ch_in(const std::string& name = "io") {
    input_ = createInputNode(name, T::bitsize);
    nodelist data(T::bitsize, true);
    data.push(input_);
    this->init(*this, data);
  }

  ch_in(const ch_in& in) : T::traits::const_type(in) {}
  ch_in(ch_in&& in) : T::traits::const_type(std::move(in)) {}

  auto operator()() const {
    return ch::internal::connector<decltype(*this)>(*this);
  }

private:
  ch_in& operator=(const ch_in&) = delete;
  ch_in& operator=(ch_in&&) = delete;

  template <typename U>
  void init(U& x, const nodelist& data) {
    x.write_lnode(0, data, 0, T::bitsize);
  }

  template <typename U, unsigned N>
  void init(ch_in<ch_vec<U, N>>& x, const nodelist& data) {
    // TODO: ugly hack to create vec from logic
    unsigned src_offset = 0;
    for (unsigned i = 0; i < N; ++i) {
      ch::internal::write_lnode(x.items_[i], 0, data, src_offset, U::bitsize);
      src_offset += U::bitsize;
    }
  }

  lnode input_;

  template <typename U> friend class input_port;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out final : public T {
public:
  static_assert(!is_io_type<T>::value, "invalid nested type");
  using traits = io_traits<ch_out, ch_direction::out, ch_in<T>, output_port<T>, T>;
  using T::operator=;

  ch_out(const std::string& name = "io") {
    output_ = createOutputNode(name, get_lnode(*this));
  }

  ch_out(const ch_out& out) : T(out) {}
  ch_out(ch_out&& out) : T(std::move(out)) {}

  auto operator()() const {
    return ch::internal::connector<decltype(*this)>(*this);
  }

private:
  ch_out& operator=(const ch_out&) = delete;
  ch_out& operator=(ch_out&&) = delete;

  lnode output_;

  template <typename U> friend class output_port;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
struct peek_impl {
  static const T read_bytes(const lnode& node) {
    T ret(0);
    node.read_bytes(0, &ret, sizeof(T), 0, N, N);
    return ret;
  }
};

template <unsigned N>
struct peek_impl<ch_scalar<N>, N> {
  static const ch_scalar<N> read_bytes(const lnode& node) {
    ch_scalar<N> ret;
    node.read_bytes(0, ret.get_words(), ret.get_cbsize(), 0, N, N);
    return ret;
  }
};

template <typename T, unsigned N>
struct poke_impl {
  static void write_bytes(lnode& node, const T& value) {
    node.write_bytes(0, &value, sizeof(T), 0, N, N);
  }
};

template <unsigned N>
struct poke_impl<ch_scalar<N>, N> {
  static void write_bytes(lnode& node, const ch_scalar<N>& value) {
    node.write_bytes(0, value.get_words(), value.get_cbsize(), 0, N, N);
  }
};

template <typename V, typename T>
V ch_peek(const output_port<T>& port) {
  return peek_impl<std::decay_t<V>, T::bitsize>::read_bytes(port.get_output());
}

template <typename T>
void ch_peek(const output_port<T>& port,
             uint32_t dst_offset,
             void* out,
             uint32_t out_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = T::bitsize) {
  port.get_output().read_bytes(dst_offset, out, out_cbsize, src_offset, length, T::bitsize);
}

template <typename V, typename T>
V ch_peek(const input_port<T>& port) {
  return peek_impl<std::decay_t<V>, T::bitsize>::read_bytes(port.get_input());
}

template <typename T>
void ch_peek(const input_port<T>& port,
             uint32_t dst_offset,
             void* out,
             uint32_t out_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = T::bitsize) {
  port.get_input().read_bytes(dst_offset, out, out_cbsize, src_offset, length, T::bitsize);
}

template <typename V, typename T>
void ch_poke(const input_port<T>& port, const V& value) {
  poke_impl<std::decay_t<V>, T::bitsize>::write_bytes(port.get_input(), value);
}

template <typename T>
void ch_poke(const input_port<T>& port,
             uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = T::bitsize) {
  port.get_input().write_bytes(dst_offset, in, in_cbsize, src_offset, length, T::bitsize);
}

template <typename T>
using ch_flip_t = typename T::traits::flip_type;

template <typename T>
using ch_ioport_t = typename T::traits::port_type;

}
}

///////////////////////////////////////////////////////////////////////////////

#define CH_INOUT_DIRECTION_EACH(i, x) \
  (int)ch::internal::identity_t<CH_PAIR_L(x)>::traits::direction

#define CH_INOUT_DIRECTION(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_DIRECTION_EACH, CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_FLIP_DIRECTION_EACH(i, x) \
  (int)ch::internal::identity_t<CH_PAIR_L(x)>::traits::flip_type::traits::direction

#define CH_INOUT_FLIP_DIRECTION(...) \
  ch_direction(CH_FOR_EACH(CH_INOUT_FLIP_DIRECTION_EACH, CH_SEP_OR, __VA_ARGS__))

#define CH_INOUT_FIELD(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)> CH_PAIR_R(x)

#define CH_INOUT_FLIP_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::traits::flip_type CH_PAIR_R(x)

#define CH_INOUT_BIND_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::traits::port_type CH_PAIR_R(x)

#define CH_INOUT_FLIP_BIND_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::traits::flip_type::traits::port_type CH_PAIR_R(x)

#define CH_INOUT_CTOR_BODY(i, x) \
  CH_PAIR_R(x)(ch::internal::fstring("%s_%s", name.c_str(), CH_STRINGIZE(CH_PAIR_R(x))).c_str())

#define CH_INOUT_BIND_BODY(i, x) \
  this->CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_ARGS(i, x) \
  __T##i&& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_BODY(i, x) \
  this->CH_PAIR_R(x)(std::forward<__T##i>(CH_CONCAT(_,CH_PAIR_R(x))))

#define CH_INOUT_FIELD_BIND_REQUIRES(i, x) \
  CH_REQUIRES(!std::is_same<std::decay_t<__T##i>, __self_type__>::value \
           && !std::is_same<std::decay_t<__T##i>, __port_type__>::value \
           && !std::is_same<std::decay_t<__T##i>, __flip_port_type__>::value)

#define CH_INOUT_BODY_IMPL2(inout_name, field_body, ...) \
  inout_name(const std::string& name = "io") \
    : CH_FOR_EACH(CH_INOUT_CTOR_BODY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& __rhs__) \
    : CH_FOR_EACH(CH_STRUCT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __rhs__) \
    : CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_BIND_IMPL2(field_body, ...) \
  void operator()(const __self_type__& __rhs__) const { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __port_type__& __rhs__) const { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __flip_port_type__& __rhs__) const { \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_REVERSE_FOR_EACH(CH_INOUT_FIELD_BIND_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) const { \
    CH_FOR_EACH(CH_INOUT_BIND_FIELD_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_BODY_IMPL3(inout_name, parent, field_body, ...) \
  inout_name(const std::string& name = "io") \
    : parent(name) \
    , CH_FOR_EACH(CH_INOUT_CTOR_BODY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& __rhs__) \
    : parent(__rhs__) \
    , CH_FOR_EACH(CH_STRUCT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __rhs__) \
    : parent(std::move(__rhs__)) \
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_BIND_IMPL3(parent, field_body, ...) \
  void operator()(const __self_type__& __rhs__) const { \
    parent::operator()(__rhs__); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __port_type__& __rhs__) const { \
    parent::operator()(__rhs__); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __flip_port_type__& __rhs__) const { \
    parent::operator()(__rhs__); \
    CH_FOR_EACH(CH_INOUT_BIND_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), typename... __Ts__, \
            CH_REVERSE_FOR_EACH(CH_INOUT_FIELD_BIND_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__), __Ts__&&... __args__) const { \
    parent::operator()(__args__...); \
    CH_FOR_EACH(CH_INOUT_BIND_FIELD_BODY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_IMPL2(inout_name, ...) \
  class inout_name { \
  private: \
    CH_STRUCT_IMPL2(__value_type__, __VA_ARGS__); \
    class __flop_port_type__; \
    class __flip_type__ { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      static constexpr unsigned bitsize = CH_STRUCT_SIZE(__VA_ARGS__); \
      CH_INOUT_BODY_IMPL2(__flip_type__, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    private: \
      class __port_type__ { \
      public: \
        static constexpr unsigned bitsize = __flip_type__::bitsize; \
        using __self_type__ = __flip_type__; \
        using __flip_port_type__ = __flop_port_type__; \
        __port_type__(__flip_type__& __rhs__) \
          : CH_FOR_EACH(CH_STRUCT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
        CH_INOUT_BIND_IMPL2(CH_INOUT_FLIP_BIND_FIELD, __VA_ARGS__) \
      }; \
    public: \
      using traits = ch::internal::io_traits<__flip_type__, CH_INOUT_FLIP_DIRECTION(__VA_ARGS__), inout_name, __port_type__, __value_type__>; \
    }; \
    inout_name& operator=(const inout_name&) = delete; \
  public: \
    static constexpr unsigned bitsize = CH_STRUCT_SIZE(__VA_ARGS__); \
    CH_INOUT_BODY_IMPL2(inout_name, CH_INOUT_FIELD, __VA_ARGS__) \
  private: \
    class __flop_port_type__ { \
    public: \
      static constexpr unsigned bitsize = inout_name::bitsize; \
      using __port_type__ = __flop_port_type__; \
      using __self_type__ = inout_name; \
      using __flip_port_type__ = typename __flip_type__::traits::port_type; \
      __flop_port_type__(inout_name& __rhs__) \
        : CH_FOR_EACH(CH_STRUCT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BIND_IMPL2(CH_INOUT_BIND_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::io_traits<inout_name, CH_INOUT_FLIP_DIRECTION(__VA_ARGS__), __flip_type__, __flop_port_type__, __value_type__>; \
  }

#define CH_INOUT_IMPL3(inout_name, parent, ...) \
  class inout_name : public parent { \
  private: \
    CH_STRUCT_IMPL3(__value_type__, parent, __VA_ARGS__); \
    class __flop_port_type__; \
    class __flip_type__ : public parent::traits::flip_type { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      static constexpr unsigned bitsize = parent::bitsize + CH_STRUCT_SIZE(__VA_ARGS__); \
      CH_INOUT_BODY_IMPL3(__flip_type__, parent::traits::flip_type, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    private: \
      class __port_type__ : public parent::traits::flip_type::traits::port_type { \
      public: \
        static constexpr unsigned bitsize = __flip_type__::bitsize; \
        using __self_type__ = __flip_type__; \
        using __flip_port_type__ = __flop_port_type__; \
        __port_type__(__flip_type__& __rhs__) \
          : parent::traits::flip_type::traits::port_type(__rhs__) \
          , CH_FOR_EACH(CH_STRUCT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
        CH_INOUT_BIND_IMPL3(parent::traits::flip_type::traits::port_type, CH_INOUT_FLIP_BIND_FIELD, __VA_ARGS__) \
      }; \
    public: \
      using traits = ch::internal::io_traits<__flip_type__, ch_direction((int)parent::traits::flip_type::traits::direction | (int)CH_INOUT_FLIP_DIRECTION(__VA_ARGS__)), inout_name, __port_type__, __value_type__>; \
    }; \
    inout_name& operator=(const inout_name&) = delete; \
  public: \
    static constexpr unsigned bitsize = parent::bitsize + CH_STRUCT_SIZE(__VA_ARGS__); \
    CH_INOUT_BODY_IMPL3(inout_name, parent, CH_INOUT_FIELD, __VA_ARGS__) \
  private: \
    class __flop_port_type__ : public parent::traits::port_type { \
    public: \
      static constexpr unsigned bitsize = inout_name::bitsize; \
      using __port_type__ = __flop_port_type__; \
      using __self_type__ = inout_name; \
      using __flip_port_type__ = typename __flip_type__::traits::port_type; \
      __flop_port_type__(inout_name& __rhs__) \
        : parent::traits::port_type(__rhs__) \
        , CH_FOR_EACH(CH_STRUCT_COPY_CTOR, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BIND_IMPL3(parent::traits::port_type, CH_INOUT_BIND_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using traits = ch::internal::io_traits<inout_name, ch_direction((int)parent::traits::direction | (int)CH_INOUT_DIRECTION(__VA_ARGS__)), __flip_type__, __flop_port_type__, __value_type__>; \
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
