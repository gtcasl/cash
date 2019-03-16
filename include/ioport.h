#pragma once

#include "logic.h"

namespace ch {
namespace internal {

lnodeimpl* createInputNode(const std::string& name, uint32_t size,
                           const sloc_getter& slg = sloc_getter());

lnodeimpl* createOutputNode(const std::string& name, uint32_t size,
                            const sloc_getter& slg = sloc_getter());

lnodeimpl* getOutputNode(const lnode& src);

void bindInput(const lnode& src, const lnode& input);

void bindOutput(const lnode& dst, const lnode& output);

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename Enable = void>
class ch_in {};

template <typename T, typename Enable = void>
class ch_out {};

using io_value_t = smart_ptr<sdata_type>;

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in<T, std::enable_if_t<is_logic_only_v<T>>> : public std::add_const_t<T> {
public:
  using traits = base_logic_io_traits<ch_direction::in,
                                      ch_in<T>,
                                      ch_out<T>,
                                      ch_in<ch_system_t<T>>,
                                      T>;
  using base = T;

  ch_in(const std::string& name = "ch_in")
     : base(createInputNode(name, ch_width_v<T>)) {
    input_ = get_lnode(*this);
  }

  template <typename U>
  explicit ch_in(const ch_out<U>& out)
    : base(logic_buffer(ch_width_v<T>, out.output_.name())) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    CH_SOURCE_LOCATION(1);
    bindOutput(get_lnode(*this), out.output_);
  }

  ch_in(const ch_in& other) : base(other) {}

  ch_in(const ch_in&& other)
    : base(std::move(other))
    , input_(std::move(other.input_))
  {}

  template <typename U>
  void operator()(ch_out<U>& out) const {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    CH_SOURCE_LOCATION(1);
    out = *this;
  }

protected:

  ch_in& operator=(const ch_in&) = delete;

  ch_in& operator=(ch_in&&) = delete;

  lnode input_;

  template <typename U, typename E> friend class ch_out;
  template <typename U, typename E> friend class ch_in;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out<T, std::enable_if_t<is_logic_only_v<T>>> : public T {
public:
  using traits = base_logic_io_traits<ch_direction::out,
                                      ch_out<T>,
                                      ch_in<T>,
                                      ch_out<ch_system_t<T>>,
                                      T>;
  using base = T;
  using base::operator=;

  ch_out(const std::string& name = "ch_out")
    : base(createOutputNode(name, ch_width_v<T>)) {
    output_ = getOutputNode(get_lnode(*this));
  }

  template <typename U>
  explicit ch_out(const ch_in<U>& in)
    : base(logic_buffer(ch_width_v<T>, in.input_.name())) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    CH_SOURCE_LOCATION(1);
    bindInput(get_lnode(*this), in.input_);
  }

  ch_out(const ch_out& other) : base(other) {}

  ch_out(ch_out&& other)
    : base(std::move(other))
    , output_(std::move(other.output_))
  {}

  ch_out& operator=(const ch_out& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  ch_out& operator=(ch_out&& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(std::move(other));
    output_ = std::move(other.output_);    
    return *this;
  }

  template <typename U>
  void operator()(const ch_in<U>& in) {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    CH_SOURCE_LOCATION(1);
    *this = in;
  }

protected:

  lnode output_;

  template <typename U, typename E> friend class ch_in;
  template <typename U, typename E> friend class ch_out;
};

///////////////////////////////////////////////////////////////////////////////

class system_io_buffer : public system_buffer {
public:
  using base = system_buffer;

  explicit system_io_buffer(const lnode& io);

  const sdata_type& data() const override;

  void read(uint32_t src_offset,
            sdata_type& dst,
            uint32_t dst_offset,
            uint32_t length) const override;

  void write(uint32_t dst_offset,
             const sdata_type& src,
             uint32_t src_offset,
             uint32_t length) override;

  void read(uint32_t src_offset,
            void* out,
            uint32_t byte_alignment,
            uint32_t dst_offset,
            uint32_t length) const override;

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t byte_alignment,
             uint32_t src_offset,
             uint32_t length) override;

  void bind(system_io_buffer* out);

protected:

  io_value_t io_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_in<T, std::enable_if_t<is_system_only_v<T>>> : public T {
public:
  using traits = base_system_io_traits<ch_direction::in,
                                       ch_in<T>,
                                       ch_out<T>,
                                       ch_in<ch_logic_t<T>>,
                                       T>;
  using base = T;
  using base::operator=;

  template <typename U>
  explicit ch_in(const ch_in<U>& in)
    : base(std::make_shared<system_io_buffer>(in.input_)) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(ch_width_v<U> == ch_width_v<T>, "invalid size");
  }

  ch_in(const ch_in& other)
    : base(system_accessor::buffer(other))
  {}

  ch_in(ch_in&& other) : base(std::move(other)) {}

  ch_in& operator=(const ch_in& other) {
    base::operator=(other);
    return *this;
  }

  ch_in& operator=(ch_in&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  template <typename U>
  void operator()(const ch_out<U>& out) {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    auto this_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(*this).get());
    auto out_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(out).get());
    this_buf->bind(out_buf);
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_out<T, std::enable_if_t<is_system_only_v<T>>> : public std::add_const_t<T> {
public:
  using traits = base_system_io_traits<ch_direction::out,
                                       ch_out<T>,
                                       ch_in<T>,
                                       ch_out<ch_logic_t<T>>,
                                       T>;
  using base = T;

  template <typename U>
  explicit ch_out(const ch_out<U>& out)
    : base(std::make_shared<system_io_buffer>(out.output_)) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert(ch_width_v<T> == ch_width_v<U>, "invalid size");
  }

  ch_out(const ch_out& other)
    : base(system_accessor::buffer(other))
  {}

  ch_out(const ch_out&& other)
    : base(std::move(other))
  {}

  template <typename U>
  void operator()(ch_in<U>& out) const {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    auto this_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(*this).get());
    auto out_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(out).get());
    out_buf->bind(this_buf);
  }

protected:

  ch_out& operator=(const ch_out&) = delete;

  ch_out& operator=(ch_out&&) = delete;
};

}
}
