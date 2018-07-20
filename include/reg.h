#pragma once

#include "bit.h"
#include "if.h"

namespace ch {
namespace internal {

logic_buffer createRegNode(unsigned size, const source_location& sloc);

logic_buffer createRegNode(const lnode& init, const source_location& sloc);

logic_buffer copyRegNode(const lnode& node, const source_location& sloc);

logic_buffer createRegNextNode(const lnode& node);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg_impl final : public T {
public:  
  using traits = logic_traits<ch_width_v<T>, ch_signed_v<T>, ch_reg<T>, ch_scalar_t<T>>;
  using base = T;
  
  struct next_t {
    next_t(const logic_buffer& buffer) : next(buffer) {}
    T next;
  };  

  std::unique_ptr<next_t> __next__;

  ch_reg_impl(CH_SLOC)
    : base(createRegNode(ch_width_v<T>, sloc)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0,
            CH_REQUIRE_0(std::is_convertible_v<U0, T>)>
  ch_reg_impl(const U0& init0, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0)), sloc)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0,
            CH_REQUIRE_0(!std::is_convertible_v<U0, T> && std::is_constructible_v<T, U0>)>
  explicit ch_reg_impl(const U0& init0, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0)), sloc)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0, init1)), sloc)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1, typename U2,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, const U2& init2, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0, init1, init2)), sloc)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1, typename U2, typename U3,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2, U3>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, const U2& init2, const U3& init3, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0, init1, init2, init3)), sloc)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1, typename U2, typename U3, typename... Us,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2, U3, Us...>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, const U2& init2, const U3& init3, const Us&... inits)
    : base(createRegNode(logic_accessor::data(T(init0, init1, init2, init3, inits...)), source_location())) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  ch_reg_impl(const ch_reg_impl& other, CH_SLOC)
    : base(copyRegNode(logic_accessor::data(other), sloc)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  ch_reg_impl(ch_reg_impl&& other)
    : base(std::move(other.buffer_)) {
    __next__ = std::make_unique<next_t>(createRegNextNode(logic_accessor::data(*this)));
  }

  auto& operator->() const {
    return __next__;
  }  

private:

  ch_reg_impl& operator=(ch_reg_impl&&) = delete;

};

///////////////////////////////////////////////////////////////////////////////

ch_bit<1> ch_clock(CH_SLOC);

ch_bit<1> ch_reset(CH_SLOC);

void ch_pushcd(const ch_bit<1>& clk,
               const ch_bit<1>& reset = ch_reset(),
               bool posedge = true,
               CH_SLOC);

void ch_popcd();

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_delay(const T& in, uint32_t delay = 1, CH_SLOC) {
  CH_CHECK(delay > 0, "invalid value");
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  R ret(in, sloc);
  for (unsigned i = 0; i < delay; ++i) {
    ch_reg<R> reg(sloc);
    reg->next = ch_clone(ret, sloc);
    ret = reg;
  }
  return ret;
}

template <typename R, typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init, CH_SLOC) {
  CH_CHECK(delay > 0, "invalid value");
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  R ret(in, sloc);
  for (unsigned i = 0; i < delay; ++i) {
    ch_reg<R> reg(init, sloc);
    reg->next = ch_clone(ret, sloc);
    ret = reg;
  }
  return ret;
}

template <typename R, typename T>
auto ch_delayEn(const T& in, const ch_bit<1>& enable, uint32_t delay = 1, CH_SLOC) {
  CH_CHECK(delay > 0, "invalid value");
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  R ret(in, sloc);
  for (unsigned i = 0; i < delay; ++i) {
    ch_reg<R> reg(sloc);
    reg->next = ch_sel(enable, ch_clone(ret, sloc), reg, sloc);
    ret = reg;
  }
  return ret;
}

template <typename R, typename T, typename I>
auto ch_delayEn(const T& in, const ch_bit<1>& enable, uint32_t delay, const I& init, CH_SLOC) {
  CH_CHECK(delay > 0, "invalid value");
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  R ret(in, sloc);
  for (unsigned i = 0; i < delay; ++i) {
    ch_reg<R> reg(init, sloc);
    reg->next = ch_sel(enable, ch_clone(ret, sloc), reg, sloc);
    ret = reg;
  }
  return ret;
}

template <typename T>
auto ch_delay(const T& in, uint32_t delay = 1, CH_SLOC) {
  static_assert(is_object_type_v<T>, "invalid type");
  return ch_delay<ch_logic_t<T>, T>(in, delay, sloc);
}

template <typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init, CH_SLOC) {
  static_assert(is_object_type_v<T>, "invalid type");
  return ch_delay<ch_logic_t<T>, T>(in, delay, init, sloc);
}

template <typename T>
auto ch_delayEn(const T& in, const ch_bit<1>& enable, uint32_t delay = 1, CH_SLOC) {
  static_assert(is_object_type_v<T>, "invalid type");
  return ch_delayEn<ch_logic_t<T>, T>(in, enable, delay, sloc);
}

template <typename T, typename I>
auto ch_delayEn(const T& in, const ch_bit<1>& enable, uint32_t delay, const I& init, CH_SLOC) {
  static_assert(is_object_type_v<T>, "invalid type");
  return ch_delayEn<ch_logic_t<T>, T>(in, enable, delay, init, sloc);
}

}
}
