#pragma once

#include "struct.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const std::string& name, uint32_t size);

lnodeimpl* createOutputNode(const std::string& name, const lnode& src);

void bindInput(const lnode& src, const lnode& input);

void bindOutput(const lnode& dst, const lnode& output);

///////////////////////////////////////////////////////////////////////////////

enum class ch_direction {
  in    = 0x1,
  out   = 0x2,
  inout = 0x3,
};

template <typename IoType,
          ch_direction Direction,
          typename FlipType,
          typename PortType,
          typename LogicType>
struct io_traits {
  static constexpr unsigned bitwidth = bitwidth_v<LogicType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using port_type   = PortType;
  using logic_type  = LogicType;
  using const_type  = const_type_t<LogicType>;
  using value_type  = value_type_t<LogicType>;
  using scalar_type = scalar_type_t<LogicType>;
};

template <typename T>
using io_type_t = typename std::decay_t<T>::traits::io_type;

template <typename T>
using flip_type_t = typename std::decay_t<T>::traits::flip_type;

template <typename T>
using port_type_t = typename std::decay_t<T>::traits::port_type;

template <typename T>
inline constexpr ch_direction direction_v = std::decay_t<T>::traits::direction;

template <typename T>
struct is_io_traits : std::false_type {};

template <typename IoType, ch_direction Direction, typename FlipType, typename PortType, typename LogicType>
struct is_io_traits<io_traits<IoType, Direction, FlipType, PortType, LogicType>> : std::true_type {};

CH_DEF_SFINAE_CHECK(is_io_type, is_io_traits<typename std::decay_t<T>::traits>::value);

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
    bindInput(get_lnode(in), in_.input_);
  }

  void operator()(const input_port& in) const {
    bindInput(get_lnode(in.in_), in_.input_);
  }

  void operator()(const output_port<T>& out) const {
    bindInput(get_lnode(out.out_), in_.input_);
  }

  template <typename U, CH_REQUIRES(is_cast_convertible<T, U>::value)>
  void operator()(const U& value) const {
    bindInput(get_lnode<U, bitwidth_v<T>>(value), in_.input_);
  }

protected:

  lnode& get_input() const {
    return in_.input_;
  }

  ch_in<T>& in_;

  friend std::ostream& operator<<(std::ostream& out, const input_port& port) {
    return out << port.get_input();
  }

  template <typename U> friend class output_port;
  template <typename V, typename U> friend V ch_peek(const input_port<U>& port);
  template <typename V, typename U> friend void ch_poke(const input_port<U>& port,
                                                        const V& value);
  template <typename U> friend void ch_peek(const input_port<U>& port,
                                            uint32_t dst_offset,
                                            void* out,
                                            uint32_t out_cbsize,
                                            uint32_t src_offset,
                                            uint32_t length);
  template <typename U> friend void ch_poke(const input_port<U>& port,
                                            uint32_t dst_offset,
                                            const void* in,
                                            uint32_t in_cbsize,
                                            uint32_t src_offset,
                                            uint32_t length);
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

  template <typename U, CH_REQUIRES(is_cast_convertible<U, T>::value)>
  void operator()(U& value) const {
    bindOutput(get_lnode(value), out_.output_);
  }

protected:

  const lnode& get_output() const {
    return out_.output_;
  }

  const ch_out<T>& out_;

  friend std::ostream& operator<<(std::ostream& out, const output_port& port) {
    return out << port.get_output();
  }

  template <typename U> friend class input_port;
  template <typename V, typename U> friend V ch_peek(const output_port<U>& port);
  template <typename U> friend void ch_peek(const output_port<U>& port,
                                            uint32_t dst_offset,
                                            void* out,
                                            uint32_t out_cbsize,
                                            uint32_t src_offset,
                                            uint32_t length);
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in final : public const_type_t<T> {
public:
  static_assert(!is_io_type<T>::value, "invalid nested type");
  using traits = io_traits<ch_in, ch_direction::in, ch_out<T>, input_port<T>, T>;

  ch_in(const std::string& name = "io") {
    input_ = createInputNode(name, bitwidth_v<T>);
    bit_accessor::set_data(*this, input_);
  }

  ch_in(const ch_in& in) : const_type_t<T>(in) {}

  ch_in(ch_in&& in) : const_type_t<T>(std::move(in)) {}

private:

  ch_in& operator=(const ch_in&) = delete;
  ch_in& operator=(ch_in&&) = delete;

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

  ch_out& operator=(const ch_out& rhs) {
    T::operator=(rhs);
    return *this;
  }

private:

  ch_out& operator=(ch_out&&) = delete;

  lnode output_;

  template <typename U> friend class output_port;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
struct peek_impl {
  static const T read(const lnode& node) {
    T ret(0);
    node.get_data().read(0, &ret, sizeof(T), 0, N);
    return ret;
  }
};

template <unsigned N>
struct peek_impl<ch_scalar<N>, N> {
  static const ch_scalar<N> read(const lnode& node) {
    bitvector ret(N);
    node.get_data().read(0, ret.get_words(), ret.get_cbsize(), 0, N);
    return ch_scalar<N>(std::move(ret));
  }
};

template <typename T, unsigned N>
struct poke_impl {
  static void write(lnode& node, const T& value) {
    node.get_data().write(0, &value, sizeof(T), 0, N);
  }
};

template <unsigned N>
struct poke_impl<ch_scalar<N>, N> {
  static void write(lnode& node, const ch_scalar<N>& value) {
    auto& data = scalar_accessor::get_data(value);
    node.get_data().write(0, data.get_words(), data.get_cbsize(), 0, N);
  }
};

template <typename V, typename T>
V ch_peek(const output_port<T>& port) {
  return peek_impl<std::decay_t<V>, bitwidth_v<T>>::read(port.get_output());
}

template <typename T>
void ch_peek(const output_port<T>& port,
             uint32_t dst_offset,
             void* out,
             uint32_t out_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = bitwidth_v<T>) {
  port.get_output().get_data().read(dst_offset, out, out_cbsize, src_offset, length);
}

template <typename V, typename T>
V ch_peek(const input_port<T>& port) {
  return peek_impl<std::decay_t<V>, bitwidth_v<T>>::read(port.get_input());
}

template <typename T>
void ch_peek(const input_port<T>& port,
             uint32_t dst_offset,
             void* out,
             uint32_t out_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = bitwidth_v<T>) {
  port.get_input().get_data().read(dst_offset, out, out_cbsize, src_offset, length);
}

template <typename V, typename T>
void ch_poke(const input_port<T>& port, const V& value) {
  poke_impl<std::decay_t<V>, bitwidth_v<T>>::write(port.get_input(), value);
}

template <typename T>
void ch_poke(const input_port<T>& port,
             uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = bitwidth_v<T>) {
  port.get_input().get_data().write(dst_offset, in, in_cbsize, src_offset, length);
}

}
}
