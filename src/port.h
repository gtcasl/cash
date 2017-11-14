#pragma once

#include "struct.h"
#include "seq.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const std::string& name, uint32_t size);

lnodeimpl* createOutputNode(const std::string& name, const lnode& src);

void bindInput(const lnode& src, const lnode& input);

void bindOutput(const lnode& dst, const lnode& output);

///////////////////////////////////////////////////////////////////////////////

template <typename T> class ch_in;

template <typename T> class ch_out;

template <typename T> class in_buffer;

template <typename T> class out_buffer;

inline constexpr auto operator|(ch_direction lsh, ch_direction rhs) {
  return ch_direction((int)lsh | (int)rhs);
}

template <typename IoType,
          ch_direction Direction,
          typename FlipType,
          typename BufferType,
          typename LogicType,
          typename Next = void>
struct io_traits {
  static constexpr traits_type type = traits_io;
  static constexpr unsigned bitwidth = bitwidth_v<LogicType>;
  static constexpr ch_direction direction = Direction;
  using io_type     = IoType;
  using flip_type   = FlipType;
  using buffer_type = BufferType;
  using logic_type  = LogicType;
  using value_type  = value_type_t<LogicType>;
  using const_type  = const_type_t<LogicType>;
  using scalar_type = scalar_type_t<LogicType>;
  using next        = Next;
};

template <typename T>
using io_type_t = typename std::decay_t<T>::traits::io_type;

template <typename T>
using flip_type_t = typename std::decay_t<T>::traits::flip_type;

template <typename T>
using buffer_type_t = typename std::decay_t<T>::traits::buffer_type;

template <typename T>
inline constexpr ch_direction direction_v = std::decay_t<T>::traits::direction;

template <typename T>
struct is_io_traits : std::false_type {};

template <typename IoType,
          ch_direction Direction,
          typename FlipType,
          typename BufferType,
          typename LogicType,
          typename Next>
struct is_io_traits<io_traits<IoType,
                              Direction,
                              FlipType,
                              BufferType,
                              LogicType,
                              Next>> : std::true_type {};

CH_DEF_SFINAE_CHECK(is_io_type, is_io_traits<typename std::decay_t<T>::traits>::value);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in final : public const_type_t<T> {
public:
  static_assert(is_logic_type<T>::value, "invalid type");
  using base = const_type_t<T>;
  using traits = io_traits<ch_in<T>, ch_direction::in, ch_out<T>, in_buffer<T>,
                           T, typename base::traits>;

  ch_in(const std::string& name = "io") {
    input_ = createInputNode(name, bitwidth_v<T>);
    bit_accessor::set_data(*this, input_);
  }

  ch_in(const ch_out<T>& out) {
    input_ = bit_accessor::get_data(*this);
    bindOutput(input_, out.output_);
  }

  ch_in(const ch_in& in) : base(in) {}

  ch_in(ch_in&& in) : base(std::move(in)) {}

  void operator()(ch_out<T>& out) const {
    out = *this;
  }

private:

  ch_in& operator=(const ch_in&) = delete;
  ch_in& operator=(ch_in&&) = delete;

  lnode input_;

  template <typename U> friend class ch_out;
  template <typename U> friend class in_buffer;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out final : public T {
public:
  static_assert(is_logic_type<T>::value, "invalid type");
  using base = T;
  using traits = io_traits<ch_out, ch_direction::out, ch_in<T>, out_buffer<T>,
                           T, typename base::traits>;
  using base::operator=;

  ch_out(const std::string& name = "io") {
    output_ = createOutputNode(name, bit_accessor::get_data(*this));
  }

  ch_out(const ch_in<T>& in) {
    output_ = bit_accessor::get_data(*this);
    bindInput(output_, in.input_);
  }

  ch_out(const ch_out& out) : base(out) {}

  ch_out(ch_out&& out) : base(std::move(out)) {}

  ch_out& operator=(const ch_out& rhs) {
    base::operator=(rhs);
    return *this;
  }

  void operator()(const ch_in<T>& in) {
    (*this) = in;
  }

private:

  ch_out& operator=(ch_out&&) = delete;

  lnode output_;

  template <typename U> friend class ch_in;
  template <typename U> friend class out_buffer;
};

///////////////////////////////////////////////////////////////////////////////

class scalar_buffer_io : public scalar_buffer_impl {
public:
  using base = scalar_buffer_impl;
  using base::size_;
  using base::value_;

  scalar_buffer_io(unsigned size) : scalar_buffer_impl(size) {}

  const bitvector& get_data() const override {
    this->read(0, value_.get_words(), value_.get_cbsize(), 0, value_.get_size());
    return value_;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class in_buffer : public scalar_buffer_io {
public:
  using base = scalar_buffer_io;
  in_buffer(ch_in<T>& in) : base(bitwidth_v<T>), in_(in) {}

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset,
            uint32_t length) const override {
    in_.input_.get_data().read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset,
             uint32_t length) override {
    in_.input_.get_data().write(dst_offset, in, in_cbsize, src_offset, length);
  }

protected:
  ch_in<T>& in_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class out_buffer : public scalar_buffer_io {
public:
  using base = scalar_buffer_io;
  out_buffer(const ch_out<T>& out) : base(bitwidth_v<T>), out_(out) {}

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset,
            uint32_t length) const override {
    out_.output_.get_data().read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write(uint32_t, const void*, uint32_t, uint32_t, uint32_t) override {
    CH_ABORT("trying to write to a read-only port: %s", out_.output_.get_name().c_str());
  }

protected:
  const ch_out<T>& out_;
};

}
}
