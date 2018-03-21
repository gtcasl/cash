#pragma once

#include "bit.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const std::string& name, uint32_t size);

lnodeimpl* createOutputNode(const std::string& name, const lnode& src);

void bindInput(const lnode& src, const lnode& input);

void bindOutput(const lnode& dst, const lnode& output);

///////////////////////////////////////////////////////////////////////////////

template <typename T> class ch_in;

template <typename T> class ch_out;

template <typename T> class scalar_in;

template <typename T> class scalar_out;

enum class ch_direction {
  none  = 0x0,
  in    = 0x1,
  out   = 0x2,
  inout = 0x3,
};

inline constexpr auto operator|(ch_direction lsh, ch_direction rhs) {
  return ch_direction((int)lsh | (int)rhs);
}

template <unsigned Bitwidth,
          typename IoType,
          ch_direction Direction,
          typename FlipType,
          typename DeviceType>
struct io_traits {
  static constexpr traits_type type = traits_io;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using device_type = DeviceType;
};

template <typename IoType,
          ch_direction Direction,
          typename FlipType,
          typename DeviceType,
          typename LogicType>
struct io_logic_traits {
  static constexpr traits_type type = traits_logic_io;
  static constexpr unsigned bitwidth = width_v<LogicType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using device_type = DeviceType;
  using logic_type  = LogicType;
  using const_type  = const_type_t<LogicType>;
  using value_type  = value_type_t<LogicType>;
  using scalar_type = scalar_type_t<LogicType>;
};

template <typename IoType,
          ch_direction Direction,
          typename FlipType,
          typename DeviceType,
          typename ScalarType>
struct io_scalar_traits {
  static constexpr traits_type type = traits_scalar_io;
  static constexpr unsigned bitwidth = width_v<ScalarType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using device_type = DeviceType;
  using scalar_type = ScalarType;
  using const_type  = const_type_t<ScalarType>;
  using value_type  = value_type_t<ScalarType>;
  using logic_type  = logic_type_t<ScalarType>;
};

template <typename T>
using io_type_t = typename std::decay_t<T>::traits::io_type;

template <typename T>
using flip_type_t = typename std::decay_t<T>::traits::flip_type;

template <typename T>
using device_type_t = typename std::decay_t<T>::traits::device_type;

template <typename T>
inline constexpr ch_direction direction_v = std::decay_t<T>::traits::direction;

template <typename T>
using is_io_traits = is_true<(T::type & traits_io)>;

CH_DEF_SFINAE_CHECK(is_io_type, is_io_traits<typename std::decay_t<T>::traits>::value);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in final : public const_type_t<T> {
public:
  static_assert(is_logic_only<T>::value && is_value_type<T>::value, "invalid type");
  using base = const_type_t<T>;
  using traits = io_logic_traits<ch_in<T>, ch_direction::in, ch_out<T>, scalar_in<scalar_type_t<T>>, T>;

  ch_in(const std::string& name = "io", const source_location& sloc = CH_SRC_LOCATION)
    : base(bit_buffer(width_v<T>, sloc, name)) {
    input_ = createInputNode(name, width_v<T>);
    bit_accessor::set_data(*this, input_);
  }

  explicit ch_in(const ch_out<T>& out, const source_location& sloc = CH_SRC_LOCATION)
    : base(bit_buffer(width_v<T>, sloc)) {
    input_ = bit_accessor::get_data(*this);
    bindOutput(input_, out.output_);
  }

  ch_in(const ch_in& in, const source_location& sloc = CH_SRC_LOCATION) : base(in, sloc) {}

  ch_in(ch_in&& in) : base(std::move(in)) {}

  void operator()(ch_out<T>& out) const {
    out = *this;
  }

private:

  ch_in& operator=(const ch_in&) = delete;
  ch_in& operator=(ch_in&&) = delete;

  lnode input_;

  template <typename U> friend class ch_out;
  template <typename U> friend class scalar_in;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out final : public T {
public:
  static_assert(is_logic_only<T>::value && is_value_type<T>::value, "invalid type");
  using base = T;
  using traits = io_logic_traits<ch_out, ch_direction::out, ch_in<T>, scalar_out<scalar_type_t<T>>, T>;
  using base::operator=;

  ch_out(const std::string& name = "io", const source_location& sloc = CH_SRC_LOCATION)
    : base(bit_buffer(width_v<T>, sloc, name)) {
    output_ = createOutputNode(name, bit_accessor::get_data(*this));
  }

  explicit ch_out(const ch_in<T>& in, const source_location& sloc = CH_SRC_LOCATION)
    : base(bit_buffer(width_v<T>, sloc)) {
    output_ = bit_accessor::get_data(*this);
    bindInput(output_, in.input_);
  }

  ch_out(const ch_out& out, const source_location& sloc = CH_SRC_LOCATION) : base(out, sloc) {}

  ch_out(ch_out&& out) : base(std::move(out)) {}

  ch_out& operator=(const ch_out& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_out& operator=(ch_out&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  void operator()(const ch_in<T>& in) {
    *this = in;
  }

private:

  lnode output_;

  template <typename U> friend class ch_in;
  template <typename U> friend class scalar_out;
};

///////////////////////////////////////////////////////////////////////////////

class scalar_buffer_io : public scalar_buffer_impl {
public:
  using base = scalar_buffer_impl;

  scalar_buffer_io(const lnode& io)
    : base(bitvector(), nullptr, 0, io.get_size()), io_(io)
  {}

  const bitvector& get_data() const override {
    return io_.get_data();
  }

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset,
            uint32_t length) const override {
    io_.get_data().read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset,
             uint32_t length) override {
    io_.get_data().write(dst_offset, in, in_cbsize, src_offset, length);
  }

  lnode io_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class scalar_in : public T {
public:
  static_assert(is_scalar_only<T>::value && is_value_type<T>::value, "invalid type");
  using base = T;
  using traits = io_scalar_traits<scalar_in, ch_direction::out, scalar_out<T>, ch_in<logic_type_t<T>>, base>;
  using base::operator=;

  explicit scalar_in(const ch_in<logic_type_t<T>>& in)
    : base(ch::internal::scalar_buffer_ptr(new scalar_buffer_io(in.input_)))
  {}

protected:

  scalar_in(const scalar_in& out) = delete;
  scalar_in(scalar_in&& out) = delete;

  scalar_in& operator=(const scalar_in&) = delete;
  scalar_in& operator=(scalar_in&&) = delete;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class scalar_out : public const_type_t<T> {
public:
  static_assert(is_scalar_only<T>::value && is_value_type<T>::value, "invalid type");
  using base = const_type_t<T>;
  using traits = io_scalar_traits<scalar_out, ch_direction::out, scalar_in<T>, ch_out<logic_type_t<T>>, T>;

  explicit scalar_out(const ch_out<logic_type_t<T>>& out)
    : base(ch::internal::scalar_buffer_ptr(new scalar_buffer_io(out.output_)))
  {}

protected:

  scalar_out(const scalar_out& out) = delete;
  scalar_out(scalar_out&& out) = delete;

  scalar_out& operator=(const scalar_out&) = delete;
  scalar_out& operator=(scalar_out&&) = delete;
};

}
}
