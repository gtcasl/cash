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

template <typename T> class ch_in_impl;
template <typename T> using ch_in = std::add_const_t<ch_in_impl<T>>;
template <typename T> class ch_out;

template <typename T> class ch_scout_impl;
template <typename T> class ch_scin;
template <typename T> using ch_scout = std::add_const_t<ch_scout_impl<T>>;

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
  static constexpr unsigned bitwidth = ch_width_v<LogicType>;
  static constexpr unsigned is_signed = signed_v<LogicType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using device_type = DeviceType;
  using logic_type  = LogicType;
  using scalar_type = ch_scalar_t<LogicType>;
};

template <typename IoType,
          ch_direction Direction,
          typename FlipType,
          typename DeviceType,
          typename ScalarType>
struct io_scalar_traits {
  static constexpr traits_type type = traits_scalar_io;
  static constexpr unsigned bitwidth = ch_width_v<ScalarType>;
  static constexpr unsigned is_signed = signed_v<ScalarType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using device_type = DeviceType;
  using scalar_type = ScalarType;
  using logic_type  = ch_logic_t<ScalarType>;
};

template <typename T>
using ch_io_t = typename std::decay_t<T>::traits::io_type;

template <typename T>
using ch_flip_t = typename std::decay_t<T>::traits::flip_type;

template <typename T>
using device_type_t = typename std::decay_t<T>::traits::device_type;

template <typename T>
inline constexpr ch_direction ch_direction_v = std::decay_t<T>::traits::direction;

template <typename T>
inline constexpr bool is_io_traits_v = is_true_v<(T::type & traits_io)>;

CH_DEF_SFINAE_CHECK(is_io_type, is_io_traits_v<typename std::decay_t<T>::traits>);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in_impl final : public T {
public:
  static_assert(is_logic_only_v<T>, "invalid type");
  using traits = io_logic_traits<ch_in<T>,
                                 ch_direction::in,
                                 ch_out<T>,
                                 ch_scin<ch_scalar_t<T>>,
                                 T>;
  using base = T;

  ch_in_impl(const std::string& name = "io", CH_SLOC)
     : ch_in_impl(createInputNode(name, ch_width_v<T>, sloc), name, sloc)
  {}

  template <typename U>
  explicit ch_in_impl(const ch_out<U>& out, CH_SLOC)
    : base(make_logic_buffer(ch_width_v<T>, sloc)) {    
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    input_ = logic_accessor::data(*this);
    bindOutput(input_, out.output_, sloc);
  }

  ch_in_impl(const ch_in_impl&& other)
    : base(std::move(other))
    , input_(std::move(other.input_))
  {}

  const ch_in_impl& operator=(const ch_in_impl&& other) const {
    ((base*)this)->operator=(std::move(other));
    ((ch_in_impl*)this)->input_ = std::move(other.input_);
    return *this;
  }

  template <typename U>
  void operator()(ch_out<U>& out) const {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    out = *this;
  }

private:

  ch_in_impl(const lnode& src, const std::string& name,
             const source_location& sloc)
    : base(make_logic_buffer(src, sloc, name))
    , input_(src)
  {}

  ch_in_impl(const ch_in_impl&) = delete;

  ch_in_impl& operator=(const ch_in_impl&) = delete;

  lnode input_;

  template <typename U> friend class ch_out;
  template <typename U> friend class ch_scin;
};


///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out final : public T {
public:
  static_assert(is_logic_only_v<T>, "invalid type");
  using traits = io_logic_traits<ch_out,
                                 ch_direction::out,
                                 ch_in<T>,
                                 ch_scout<ch_scalar_t<T>>,
                                 T>;
  using base = T;
  using base::operator=;

  ch_out(const std::string& name = "io", CH_SLOC)
    : base(make_logic_buffer(ch_width_v<T>, sloc, name)) {
    output_ = createOutputNode(name, logic_accessor::data(*this), sloc);
  }

  template <typename U>
  explicit ch_out(const ch_in_impl<U>& in, CH_SLOC)
    : base(make_logic_buffer(ch_width_v<T>, sloc)) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    output_ = logic_accessor::data(*this);
    bindInput(output_, in.input_, sloc);
  }

  ch_out(const ch_out& other, CH_SLOC) : base(other, sloc) {}

  ch_out(ch_out&& other)
    : base(std::move(other))
    , output_(std::move(other.output_))
  {}

  ch_out& operator=(const ch_out& other) {
    base::operator=(other);
    return *this;
  }

  ch_out& operator=(ch_out&& other) {
    base::operator=(std::move(other));
    output_ = std::move(other.output_);
    return *this;
  }

  template <typename U>
  void operator()(const ch_in_impl<U>& in) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    *this = in;
  }

private:

  lnode output_;

  template <typename U> friend class ch_in_impl;
  template <typename U> friend class ch_scout_impl;
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
                                  ch_in<ch_logic_t<T>>,
                                  T>;
  using base = T;
  using base::operator=;

  template <typename U>
  explicit ch_scin(const ch_in_impl<U>& in)
    : base(std::make_shared<scalar_io_buffer>(in.input_)) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(ch_width_v<T> == ch_width_v<U>, "invalid size");
  }

  ch_scin(const ch_scin& other) : base(other)  {}

  ch_scin(ch_scin&& other) : base(std::move(other)) {}

  ch_scin& operator=(const ch_scin& other) {
    base::operator=(other);
    return *this;
  }

  ch_scin& operator=(ch_scin&& other) {
    base::operator=(std::move(other));
    return *this;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_scout_impl final : public T {
public:
  static_assert(is_scalar_only_v<T>, "invalid type");
  using traits = io_scalar_traits<ch_scout<T>,
                                  ch_direction::out,
                                  ch_scin<T>,
                                  ch_out<ch_logic_t<T>>,
                                  T>;
  using base = T;

  template <typename U>
  explicit ch_scout_impl(const ch_out<U>& out)
    : base(std::make_shared<scalar_io_buffer>(out.output_)) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(ch_width_v<T> == ch_width_v<U>, "invalid size");
  }

  ch_scout_impl(const ch_scout_impl&& other) : base(std::move(other)) {}

  const ch_scout_impl& operator=(const ch_scout_impl&& other) const {
    ((base*)this)->operator=(std::move(other));
    return *this;
  }

protected:

  ch_scout_impl(const ch_scout_impl& out) = delete;

  ch_scout_impl& operator=(const ch_scout_impl&) = delete;
};

}
}
