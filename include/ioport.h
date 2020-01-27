#pragma once

#include "logic.h"
#include "system.h"

namespace ch {
namespace internal {

class system_io_buffer;

template <typename T> class ch_logic_in;
template <typename T> class ch_logic_out;

template <typename T> class ch_system_in;
template <typename T> class ch_system_out;

template <typename T>
using ch_in = std::add_const_t<
                std::conditional_t<is_logic_type_v<T>,
                                   ch_logic_in<T>, ch_system_in<T>>>;

template <typename T>
using ch_out = std::conditional_t<is_logic_type_v<T>,
                                  ch_logic_out<T>, ch_system_out<T>>;

using io_value_t = smart_ptr<sdata_type>;

lnodeimpl* createInputNode(const std::string& name, 
                           uint32_t size,
                           const source_info& srcinfo);

lnodeimpl* createOutputNode(const std::string& name, 
                            uint32_t size,
                            const source_info& srcinfo);

lnodeimpl* bindInputNode(const lnode& input, const source_info& srcinfo);

lnodeimpl* bindOutputNode(const lnode& ouptut, const source_info& srcinfo);

lnodeimpl* bindInputNode(system_io_buffer* input, const source_info& srcinfo);

lnodeimpl* bindOutputNode(system_io_buffer* output, const source_info& srcinfo);

lnodeimpl* getOutputNode(const std::string& name);

///////////////////////////////////////////////////////////////////////////////

class system_io_buffer : public system_buffer_impl {
public:
  using base = system_buffer_impl;

  explicit system_io_buffer(uint32_t size, const std::string& name);

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

  void bind(const io_value_t& io);

  const auto& io() const {
    return io_;
  }

protected:

  io_value_t io_;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_logic_in final : public T {
public:
  static_assert(is_logic_type_v<T>, "invalid type");
  using traits = base_logic_io_traits<ch_direction::in,
                                      ch_in<T>,
                                      ch_out<T>,
                                      ch_in<ch_system_t<T>>,
                                      T>;
  using base = T;

  ch_logic_in(const std::string& name = "io", CH_SRC_INFO)
     : base(make_logic_buffer(createInputNode(name, ch_width_v<T>, srcinfo))) {
    input_ = get_lnode(*this);
  }

  template <typename U>
  explicit ch_logic_in(const ch_logic_out<U>& other, CH_SRC_INFO)
    : base(make_logic_buffer(bindOutputNode(other.output_, srcinfo))) {
    static_assert((ch_width_v<T>) == (ch_width_v<U>), "invalid size");
  }

  template <typename U>
  explicit ch_logic_in(const ch_system_out<U>& other, CH_SRC_INFO)
     : base(make_logic_buffer(bindOutputNode(
        reinterpret_cast<system_io_buffer*>(system_accessor::buffer(other).get()), srcinfo))) {
    static_assert((ch_width_v<T>) == (ch_width_v<U>), "invalid size");
  }

  ch_logic_in(const ch_logic_in& other) 
    : base(logic_accessor::buffer(other))
    , input_(other.input_) 
  {}

  ch_logic_in(const ch_logic_in&& other)
    : base(std::move(other))
    , input_(std::move(other.input_))
  {}

  template <typename U>
  void operator()(ch_logic_out<U>& out) const {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    out = *this;
  }

protected:

  ch_logic_in& operator=(const ch_logic_in&) = delete;

  ch_logic_in& operator=(ch_logic_in&&) = delete;

  lnode input_;

  template <typename U> friend class ch_logic_out;
  template <typename U> friend class ch_system_out;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_logic_out final : public T {
public:
  static_assert(is_logic_type_v<T>, "invalid type");
  using traits = base_logic_io_traits<ch_direction::out,
                                      ch_out<T>,
                                      ch_in<T>,
                                      ch_out<ch_system_t<T>>,
                                      T>;
  using base = T;
  using base::operator=;

  ch_logic_out(const std::string& name = "io", CH_SRC_INFO)
    : base(make_logic_buffer(createOutputNode(name, ch_width_v<T>, srcinfo))) {
    output_ = getOutputNode(name);
  }

  template <typename U>
  explicit ch_logic_out(const ch_logic_in<U>& other, CH_SRC_INFO)
    : base(make_logic_buffer(bindInputNode(other.input_, srcinfo))) {
    static_assert((ch_width_v<T>) == (ch_width_v<U>), "invalid size");
  }

  template <typename U>
  explicit ch_logic_out(const ch_system_in<U>& other, CH_SRC_INFO)
     : base(make_logic_buffer(bindInputNode(
        reinterpret_cast<system_io_buffer*>(system_accessor::buffer(other).get()), srcinfo))) {
    static_assert((ch_width_v<T>) == (ch_width_v<U>), "invalid size");
  }

  ch_logic_out(const ch_logic_out& other) 
    : base(logic_accessor::buffer(other))
    , output_(other.output_) 
  {}

  ch_logic_out(ch_logic_out&& other)
    : base(std::move(other))
    , output_(std::move(other.output_))
  {}

  ch_logic_out& operator=(const ch_logic_out& other) {
    base::operator=(other);
    return *this;
  }

  ch_logic_out& operator=(ch_logic_out&& other) {
    base::operator=(std::move(other));
    output_ = std::move(other.output_);
    return *this;
  }

  template <typename U>
  void operator()(const ch_logic_in<U>& in) {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    *this = in;
  }

protected:

  lnode output_;

  template <typename U> friend class ch_logic_in;
  template <typename U> friend class ch_system_in;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_system_in final : public T {
public:
  static_assert(is_system_type_v<T>, "invalid type");
  using traits = base_system_io_traits<ch_direction::out,
                                       ch_in<T>,
                                       ch_out<T>,
                                       ch_in<ch_logic_t<T>>,
                                       T>;
  using base = T;

  ch_system_in(const std::string& name = "io")
     : base(std::make_shared<system_io_buffer>(ch_width_v<T>, name))
  {}

  template <typename U>
  explicit ch_system_in(const ch_logic_out<U>& other)
    : base(std::make_shared<system_io_buffer>(other.output_)) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert((ch_width_v<T>) == (ch_width_v<U>), "invalid size");
  }

  ch_system_in(const ch_system_in& other)
    : base(system_accessor::buffer(other))
  {}

  ch_system_in(const ch_system_in&& other)
    : base(std::move(other))
  {}

  template <typename U>
  void operator()(ch_system_out<U>& out) const {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    auto this_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(*this).get());
    auto out_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(out).get());
    this_buf->bind(out_buf->io());
  }

protected:

  ch_system_in& operator=(const ch_system_in&) = delete;

  ch_system_in& operator=(ch_system_in&&) = delete;
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_system_out final : public T {
public:
  static_assert(is_system_type_v<T>, "invalid type");
  using traits = base_system_io_traits<ch_direction::in,
                                       ch_out<T>,
                                       ch_in<T>,
                                       ch_out<ch_logic_t<T>>,
                                       T>;
  using base = T;
  using base::operator=;

  ch_system_out(const std::string& name = "io")
     : base(std::make_shared<system_io_buffer>(ch_width_v<T>, name))
  {}

  template <typename U>
  explicit ch_system_out(const ch_logic_in<U>& other)
    : base(std::make_shared<system_io_buffer>(other.input_)) {
    static_assert(is_logic_only_v<U>, "invalid type");
    static_assert((ch_width_v<U>) == (ch_width_v<T>), "invalid size");
  }

  ch_system_out(const ch_system_out& other)
    : base(system_accessor::buffer(other))
  {}

  ch_system_out(ch_system_out&& other) : base(std::move(other)) {}

  ch_system_out& operator=(const ch_system_out& other) {
    base::operator=(other);
    return *this;
  }

  ch_system_out& operator=(ch_system_out&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  template <typename U>
  void operator()(const ch_system_in<U>& out) {
    static_assert(std::is_constructible_v<U, T>, "invalid type");
    auto this_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(*this).get());
    auto out_buf = reinterpret_cast<system_io_buffer*>(system_accessor::buffer(out).get());
    out_buf->bind(this_buf->io());
  }
};

}
}
