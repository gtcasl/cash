#pragma once

#include "struct.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const char* name, uint32_t size);

lnodeimpl* createOutputNode(const char* name, const lnode& src);

void bindInput(const lnode& input, const lnode& src);

void bindOutput(const lnode& dst, const lnode& output);

///////////////////////////////////////////////////////////////////////////////

class iobase {
public:
  iobase(const char* name) : name_(name) {}
  iobase(const iobase& rhs) : name_(rhs.name_) {}
  iobase(iobase&& rhs) : name_(std::move(rhs.name_)) {}

protected:

  const char* get_name() const {
    return name_.c_str();
  }

  std::string name_;
};

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

  void operator()(const ch_bitbase<T::bitcount>& value) const {
    bindInput(in_.input_, get_lnode(value));
  }

  template <typename U, CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(const U& value) const {
    bindInput(in_.input_, get_lnode<U, T::bitcount>(value));
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
  template <typename V, typename U> friend void ch_poke(const input_port<U>& port, const V& value);
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class output_port {
public:
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

  template <typename U, CH_REQUIRES(is_cast_convertible<T, U>::value)>
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
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in final : public iobase, public T::const_type {
public:
  using base = iobase;
  using value_type = T;
  using const_type = typename T::const_type;
  using flip_type = ch_out<T>;
  using port_type = input_port<T>;

  ch_in(const char* name = "io") : base(name) {
    input_ = createInputNode(name, T::bitcount);
    nodelist data(T::bitcount, true);
    data.push(input_);
    this->write_data(0, data, 0, T::bitcount);
  }

  ch_in(const ch_in& in) : base(in), T::const_type(in) {}
  ch_in(ch_in&& in) : base(std::move(in)), T::const_type(std::move(in)) {}

  auto operator()() const {
    return ch::internal::connector<decltype(*this)>(*this);
  }

private:
  ch_in& operator=(const ch_in&) = delete;
  ch_in& operator=(ch_in&&) = delete;

  lnode input_;

  template <typename U> friend class input_port;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out final : public iobase, public T {
public:
  using base = iobase;
  using value_type = T;
  using const_type = typename T::const_type;
  using flip_type = ch_in<T>;  
  using port_type = output_port<T>;
  using T::operator=;

  ch_out(const char* name = "io") : base(name) {
    output_ = createOutputNode(name, get_lnode(*this));
  }

  ch_out(const ch_out& out) : base(out), T(out) {}
  ch_out(ch_out&& out) : base(std::move(out)), T(std::move(out)) {}    

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
  return peek_impl<std::decay_t<V>, T::bitcount>::read_bytes(port.get_output());
}

template <typename V, typename T>
V ch_peek(const input_port<T>& port) {
  return peek_impl<std::decay_t<V>, T::bitcount>::read_bytes(port.get_input());
}

template <typename V, typename T>
void ch_poke(const input_port<T>& port, const V& value) {
  poke_impl<std::decay_t<V>, T::bitcount>::write_bytes(port.get_input(), value);
}

template <typename T>
using ch_flip_t = typename T::flip_type;

}
}

///////////////////////////////////////////////////////////////////////////////

#define CH_INOUT_FIELD(i, x) \
  ch::internal::identity_t<CH_PAIR_L(x)> CH_PAIR_R(x)

#define CH_INOUT_FLIP_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::flip_type CH_PAIR_R(x)

#define CH_INOUT_BIND_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::port_type CH_PAIR_R(x)

#define CH_INOUT_FLIP_BIND_FIELD(i, x) \
  typename ch::internal::identity_t<CH_PAIR_L(x)>::flip_type::port_type CH_PAIR_R(x)

#define CH_INOUT_CTOR_APPLY(i, x) \
  CH_PAIR_R(x)(ch::internal::fstring("%s_%s", this->get_name(), CH_STRINGIZE(CH_PAIR_R(x))).c_str())

#define CH_INOUT_BIND_APPLY(i, x) \
  this->CH_PAIR_R(x)(__rhs__.CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_ARGS(i, x) \
  __T##i&& CH_CONCAT(_,CH_PAIR_R(x))

#define CH_INOUT_BIND_FIELD_APPLY(i, x) \
  this->CH_PAIR_R(x)(std::forward<__T##i>(CH_CONCAT(_,CH_PAIR_R(x))))

#define CH_INOUT_FIELD_BIND_REQUIRES(i, x) \
  CH_REQUIRES(!std::is_same<std::decay_t<__T##i>, __self_type__>::value \
           && !std::is_same<std::decay_t<__T##i>, __port_type__>::value \
           && !std::is_same<std::decay_t<__T##i>, __flip_port_type__>::value)

#define CH_INOUT_BODY_IMPL2(inout_name, field_body, ...) \
  inout_name(const char* name = "io") \
    : base(name)\
    , CH_FOR_EACH(CH_INOUT_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& __rhs__) \
    : base(__rhs__)\
    , CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __rhs__) \
    : base(std::move(__rhs__))\
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_BIND_IMPL2(field_body, ...) \
  void operator()(const __self_type__& __rhs__) const { \
    CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __port_type__& __rhs__) const { \
    CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __flip_port_type__& __rhs__) const { \
    CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_REVERSE_FOR_EACH(CH_INOUT_FIELD_BIND_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__)) const { \
    CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_BODY_IMPL3(inout_name, parent, field_body, ...) \
  inout_name(const char* name = "io") \
    : base(name) \
    , parent(name) \
    , CH_FOR_EACH(CH_INOUT_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(const inout_name& __rhs__) \
    : base(__rhs__) \
    , parent(__rhs__) \
    , CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  inout_name(inout_name&& __rhs__) \
    : base(std::move(__rhs__)) \
    , parent(std::move(__rhs__)) \
    , CH_FOR_EACH(CH_STRUCT_MOVE_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_BIND_IMPL3(parent, field_body, ...) \
  void operator()(const __self_type__& __rhs__) const { \
    parent::operator()(__rhs__); \
    CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __port_type__& __rhs__) const { \
    parent::operator()(__rhs__); \
    CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  void operator()(const __flip_port_type__& __rhs__) const { \
    parent::operator()(__rhs__); \
    CH_FOR_EACH(CH_INOUT_BIND_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  template <CH_REVERSE_FOR_EACH(CH_STRUCT_FIELD_CTOR_TMPL, CH_SEP_COMMA, __VA_ARGS__), typename... __Ts__, \
            CH_REVERSE_FOR_EACH(CH_INOUT_FIELD_BIND_REQUIRES, CH_SEP_COMMA, __VA_ARGS__)> \
  void operator()(CH_REVERSE_FOR_EACH(CH_INOUT_BIND_FIELD_ARGS, CH_SEP_COMMA, __VA_ARGS__), __Ts__&&... __args__) const { \
    parent::operator()(__args__...); \
    CH_FOR_EACH(CH_INOUT_BIND_FIELD_APPLY, CH_SEP_SEMICOLON, __VA_ARGS__); \
  } \
  CH_FOR_EACH(field_body, CH_SEP_SEMICOLON, __VA_ARGS__); \
  auto operator()() const { \
    return ch::internal::connector<decltype(*this)>(*this); \
  }

#define CH_INOUT_IMPL2(inout_name, ...) \
  class inout_name : public virtual ch::internal::iobase { \
  private: \
    class __flop_port_type__; \
    class __flip_type__ : public virtual ch::internal::iobase { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      static constexpr unsigned bitcount = CH_STRUCT_SIZE(__VA_ARGS__); \
      using base = ch::internal::iobase; \
      using flip_type = inout_name; \
      CH_INOUT_BODY_IMPL2(__flip_type__, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    private: \
      class __port_type__ { \
      public: \
        using __self_type__ = __flip_type__; \
        using __flip_port_type__ = __flop_port_type__; \
        __port_type__(__flip_type__& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
        CH_INOUT_BIND_IMPL2(CH_INOUT_FLIP_BIND_FIELD, __VA_ARGS__) \
      }; \
    public: \
      using port_type = __port_type__; \
    }; \
    inout_name& operator=(const inout_name&) = delete; \
  public: \
    static constexpr unsigned bitcount = CH_STRUCT_SIZE(__VA_ARGS__); \
    using base = ch::internal::iobase; \
    using flip_type = __flip_type__; \
    CH_INOUT_BODY_IMPL2(inout_name, CH_INOUT_FIELD, __VA_ARGS__) \
  private: \
    class __flop_port_type__ { \
    public: \
      using __port_type__ = __flop_port_type__; \
      using __self_type__ = inout_name; \
      using __flip_port_type__ = typename __flip_type__::port_type; \
      __flop_port_type__(inout_name& __rhs__) : CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BIND_IMPL2(CH_INOUT_BIND_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using port_type = __flop_port_type__; \
  }

#define CH_INOUT_IMPL3(inout_name, parent, ...) \
  class inout_name : public virtual ch::internal::iobase, public parent { \
  private: \
    class __flop_port_type__; \
    class __flip_type__ : public virtual ch::internal::iobase, public parent::flip_type { \
    private: \
      __flip_type__& operator=(const __flip_type__&) = delete; \
    public: \
      static constexpr unsigned bitcount = parent::bitcount + CH_STRUCT_SIZE(__VA_ARGS__); \
      using base = ch::internal::iobase; \
      using flip_type = inout_name; \
      CH_INOUT_BODY_IMPL3(__flip_type__, parent::flip_type, CH_INOUT_FLIP_FIELD, __VA_ARGS__) \
    private: \
      class __port_type__ : public parent::flip_type::port_type { \
      public: \
        using __self_type__ = __flip_type__; \
        using __flip_port_type__ = __flop_port_type__; \
        __port_type__(__flip_type__& __rhs__) \
          : parent::flip_type::port_type(__rhs__) \
          , CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
        CH_INOUT_BIND_IMPL3(parent::flip_type::port_type, CH_INOUT_FLIP_BIND_FIELD, __VA_ARGS__) \
      }; \
    public: \
      using port_type = __port_type__; \
    }; \
    inout_name& operator=(const inout_name&) = delete; \
  public: \
    static constexpr unsigned bitcount = parent::bitcount + CH_STRUCT_SIZE(__VA_ARGS__); \
    using base = ch::internal::iobase; \
    using flip_type = __flip_type__; \
    using self_type = inout_name; \
    CH_INOUT_BODY_IMPL3(inout_name, parent, CH_INOUT_FIELD, __VA_ARGS__) \
  private: \
    class __flop_port_type__ : public parent::port_type { \
    public: \
      using __port_type__ = __flop_port_type__; \
      using __self_type__ = inout_name; \
      using __flip_port_type__ = typename __flip_type__::port_type; \
      __flop_port_type__(inout_name& __rhs__) \
        : parent::port_type(__rhs__) \
        , CH_FOR_EACH(CH_STRUCT_COPY_CTOR_APPLY, CH_SEP_COMMA, __VA_ARGS__) {} \
      CH_INOUT_BIND_IMPL3(parent::port_type, CH_INOUT_BIND_FIELD, __VA_ARGS__) \
    }; \
  public: \
    using port_type = __flop_port_type__; \
  }

#define CH_INOUT2(name, body) \
  CH_INOUT_IMPL2(name, CH_REM body)

#define CH_INOUT3(name, parent, body) \
  CH_INOUT_IMPL3(name, parent, CH_REM body)

#define GET_INOUT(_1, _2, _3, NAME, ...) NAME
#define CH_INOUT(...) GET_INOUT(__VA_ARGS__, CH_INOUT3, CH_INOUT2)(__VA_ARGS__)

#define CH_IO(...) \
  CH_INOUT_IMPL2(io_type, __VA_ARGS__); \
  io_type io

#define CH_FLIP(x) (ch_flip_t<x>)
