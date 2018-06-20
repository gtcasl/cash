#pragma once

#include "logic.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const std::string& name, uint32_t size,
                           const source_location& sloc);

lnodeimpl* createOutputNode(const std::string& name, const lnode& src,
                            const source_location& sloc);

void bindInput(const lnode& src,
               const lnode& input,
               const source_location& sloc);

void bindOutput(const lnode& dst,
                const lnode& output,
                const source_location& sloc);

///////////////////////////////////////////////////////////////////////////////

template <typename T> class ch_in;
template <typename T> class ch_out;

template <typename T> class ch_scalar_out_impl;
template <typename T> class ch_scin;
template <typename T> using ch_scout = std::add_const_t<ch_scalar_out_impl<T>>;

enum class ch_direction {
  in    = 1 << 0,
  out   = 1 << 1,
  inout = in | out,
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
  static constexpr unsigned is_signed = signed_v<LogicType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using device_type = DeviceType;
  using logic_type  = LogicType;
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
  static constexpr unsigned is_signed = signed_v<ScalarType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using device_type = DeviceType;
  using scalar_type = ScalarType;
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
inline constexpr bool is_io_traits_v = is_true_v<(T::type & traits_io)>;

CH_DEF_SFINAE_CHECK(is_io_type, is_io_traits_v<typename std::decay_t<T>::traits>);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in final {
public:
  static_assert(is_logic_only_v<T>, "invalid type");
  using self = ch_in;
  using traits = io_logic_traits<ch_in<T>,
                                 ch_direction::in,
                                 ch_out<T>,
                                 ch_scin<scalar_type_t<T>>,
                                 T>;

  ch_in(const std::string& name = "io", CH_SLOC) {
    input_ = createInputNode(name, width_v<T>, sloc);
    proxy_ = make_logic_buffer(input_, sloc, name);
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_only_v<U>),
            CH_REQUIRE_0(std::is_constructible_v<U, T>)>
  explicit ch_in(const ch_out<U>& out, CH_SLOC) {
    proxy_ = make_logic_buffer(width_v<T>, sloc);
    input_ = logic_accessor::data(*this);
    bindOutput(input_, out.output_, sloc);
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_only_v<U>),
            CH_REQUIRE_0(std::is_constructible_v<U, T>)>
  void operator()(ch_out<U>& out) const {
    out = *this;
  }

  operator T() const {
    return proxy_;
  }

private:

  ch_in(const ch_in&) = delete;

  ch_in(ch_in&&) = delete;

  ch_in& operator=(const ch_in&) = delete;

  ch_in& operator=(ch_in&&) = delete;

  const logic_buffer_ptr& buffer() const {
    return logic_accessor::buffer(proxy_);
  }

  lnode input_;
  T proxy_;

  friend class logic_accessor;

  template <typename U> friend class ch_out;
  template <typename U> friend class ch_scin;
};


///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out final {
public:
  static_assert(is_logic_only_v<T>, "invalid type");
  using self = ch_out;
  using traits = io_logic_traits<ch_out,
                                 ch_direction::out,
                                 ch_in<T>,
                                 ch_scout<scalar_type_t<T>>,
                                 T>;

  ch_out(const std::string& name = "io", CH_SLOC) {
    proxy_ = make_logic_buffer(width_v<T>, sloc, name);
    output_ = createOutputNode(name, logic_accessor::data(proxy_), sloc);
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_only_v<U>),
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  explicit ch_out(const ch_in<U>& in, CH_SLOC) {
    proxy_ = make_logic_buffer(width_v<T>, sloc);
    output_ = logic_accessor::data(proxy_);
    bindInput(output_, in.input_, sloc);
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_only_v<U>),
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  ch_out& operator=(const U& in) {
    proxy_ = in;
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_only_v<U>),
            CH_REQUIRE_0(std::is_constructible_v<T, U>)>
  void operator()(const ch_in<U>& in) {
    *this = in;
  }

  operator T() const {
    return proxy_;
  }

private:

  ch_out(const ch_out&) = delete;

  ch_out(ch_out&&) = delete;

  ch_out& operator=(const ch_out&) = delete;

  ch_out& operator=(ch_out&&) = delete;

  const logic_buffer_ptr& buffer() const {
    return logic_accessor::buffer(proxy_);
  }

  lnode output_;
  T proxy_;

  friend class logic_accessor;

  template <typename U> friend class ch_in;
  template <typename U> friend class ch_scalar_out_impl;
};

///////////////////////////////////////////////////////////////////////////////

class scalar_io_buffer : public scalar_buffer {
public:
  using base = scalar_buffer;

  explicit scalar_io_buffer(const lnode& io)
    : base(bitvector(), nullptr, 0, io.size()), io_(io)
  {}

  const bitvector& data() const override {
    return io_.data();
  }

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset,
            uint32_t length) const override {
    io_.data().read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset,
             uint32_t length) override {
    io_.data().write(dst_offset, in, in_cbsize, src_offset, length);
  }

  lnode io_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_scin final : public T {
public:
  static_assert(is_scalar_only_v<T>, "invalid type");
  using traits = io_scalar_traits<ch_scin,
                                  ch_direction::in,
                                  ch_scout<T>,
                                  ch_in<logic_type_t<T>>,
                                  T>;
  using base = T;
  using base::operator=;

  template <typename U,
            CH_REQUIRE_0(is_logic_only_v<U>),
            CH_REQUIRE_0(width_v<T> == width_v<U>)>
  explicit ch_scin(const ch_in<U>& in)
    : base(std::make_shared<scalar_io_buffer>(in.input_))
  {}

protected:

  ch_scin(const ch_scin& rhs) = delete;

  ch_scin(ch_scin&& rhs) = delete;

  ch_scin& operator=(const ch_scin&) = delete;

  ch_scin& operator=(ch_scin&&) = delete;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_scalar_out_impl final : public T {
public:
  static_assert(is_scalar_only_v<T>, "invalid type");
  using traits = io_scalar_traits<ch_scout<T>,
                                  ch_direction::out,
                                  ch_scin<T>,
                                  ch_out<logic_type_t<T>>,
                                  T>;
  using base = T;

  template <typename U,
            CH_REQUIRE_0(is_logic_only_v<U>),
            CH_REQUIRE_0(width_v<T> == width_v<U>)>
  explicit ch_scalar_out_impl(const ch_out<U>& out)
    : base(std::make_shared<scalar_io_buffer>(out.output_))
  {}

protected:

  ch_scalar_out_impl(const ch_scalar_out_impl& out) = delete;

  ch_scalar_out_impl(ch_scalar_out_impl&& out) = delete;

  ch_scalar_out_impl& operator=(const ch_scalar_out_impl&) = delete;

  ch_scalar_out_impl& operator=(ch_scalar_out_impl&&) = delete;
};

}
}
