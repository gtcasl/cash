#pragma once

#include "bit.h"
#include "if.h"

namespace ch {
namespace internal {

logic_buffer createRegNode(unsigned size, const source_location& sloc);

logic_buffer createRegNode(const lnode& init, const source_location& sloc);

logic_buffer copyRegNode(const lnode& node, const source_location& sloc);

logic_buffer getRegNextNode(const lnode& node);

logic_buffer createRegNext(const lnode& next, unsigned length,
                           const source_location& sloc);

logic_buffer createRegNext(const lnode& next, unsigned length,
                           const lnode& enable, const source_location& sloc);

logic_buffer createRegNext(const lnode& next, const lnode& init, unsigned length,
                           const source_location& sloc);

logic_buffer createRegNext(const lnode& next, const lnode& init, unsigned length,
                           const lnode& enable, const source_location& sloc);

void pushClockDomain(const lnode& clock, const lnode& reset, bool pos_edge,
                     const source_location& sloc);

void beginPipe(const std::vector<int>& latencies);

void endPipe();

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg_impl final : public T {
public:  
  using traits = logic_traits<ch_width_v<T>, ch_signed_v<T>, T, ch_system_t<T>>;
  using base = T;

  ch_reg_impl(CH_SLOC)
    : base(createRegNode(ch_width_v<T>, sloc)) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0,
            CH_REQUIRE_0(std::is_convertible_v<U0, T>)>
  explicit ch_reg_impl(const U0& init0, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0)), sloc)) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0,
            CH_REQUIRE_0(!std::is_convertible_v<U0, T> && std::is_constructible_v<T, U0>)>
  explicit ch_reg_impl(const U0& init0, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0)), sloc)) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0, init1)), sloc)) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1, typename U2,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, const U2& init2, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0, init1, init2)), sloc)) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1, typename U2, typename U3,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2, U3>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, const U2& init2, const U3& init3, CH_SLOC)
    : base(createRegNode(logic_accessor::data(T(init0, init1, init2, init3)), sloc)) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  template <typename U0, typename U1, typename U2, typename U3, typename... Us,
            CH_REQUIRE_0(std::is_constructible_v<T, U0, U1, U2, U3, Us...>)>
  explicit ch_reg_impl(const U0& init0, const U1& init1, const U2& init2, const U3& init3, const Us&... inits)
    : base(createRegNode(logic_accessor::data(T(init0, init1, init2, init3, inits...)), source_location())) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  ch_reg_impl(const ch_reg_impl& other, CH_SLOC)
    : base(copyRegNode(logic_accessor::data(other), sloc)) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  ch_reg_impl(ch_reg_impl&& other)
    : base(std::move(logic_accessor::buffer(other))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(logic_accessor::data(*this)));
  }

  auto& operator->() const {
    return __next__;
  }  

private:

  ch_reg_impl& operator=(ch_reg_impl&&) = delete;

  struct next_t {
    next_t(const logic_buffer& buffer) : next(buffer) {}
    T next;
  };

  std::unique_ptr<next_t> __next__;
};

///////////////////////////////////////////////////////////////////////////////

ch_bit<1> ch_clock(CH_SLOC);

ch_bit<1> ch_reset(CH_SLOC);

template <typename C, typename R = ch_bit<1>>
void ch_pushcd(const C& clk,
               const R& reset = ch_reset(),
               bool pos_edge = true,
               CH_SLOC) {
  static_assert(is_bit_base_v<C>, "invalid type");
  static_assert(ch_width_v<C> == 1, "invalid size");
  static_assert(is_bit_base_v<R>, "invalid type");
  static_assert(ch_width_v<R> == 1, "invalid size");
  pushClockDomain(get_lnode(clk), get_lnode(reset), pos_edge, sloc);
}

void ch_popcd();

template <typename Func, typename C, typename R = ch_bit<1>>
void ch_cd(Func&& func,
           const C& clk,
           const R& reset = ch_reset(),
           bool pos_edge = true) {
  ch_pushcd(clk, reset, pos_edge);
  func;
  ch_popcd();
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_next(const T& in, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  return R(createRegNext(logic_accessor::data(R(in, sloc)),
                         1,
                         sloc));
}

template <typename T>
auto ch_next(const T& in, CH_SLOC) {
  static_assert(is_object_type_v<T>, "invalid type");
  return ch_next<ch_logic_t<T>, T>(in, sloc);
}

template <typename R, typename T, typename I>
auto ch_next(const T& in, const I& init, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  return R(createRegNext(logic_accessor::data(R(in, sloc)),
                         logic_accessor::data(R(init, sloc)),
                         1,
                         sloc));
}

template <typename T, typename I>
auto ch_next(const T& in, const I& init, CH_SLOC) {
  return ch_next<ch_logic_t<T>, T, I>(in, init, sloc);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_nextEn(const T& in, const E& enable, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return R(createRegNext(logic_accessor::data(R(in, sloc)),
                         1,
                         logic_accessor::data(enable),
                         sloc));
}

template <typename T, typename E>
auto ch_nextEn(const T& in, const E& enable, CH_SLOC) {
  return ch_nextEn<ch_logic_t<T>, T, E>(in, enable, sloc);
}

template <typename R, typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");  
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return R(createRegNext(logic_accessor::data(R(in, sloc)),
                         logic_accessor::data(R(init, sloc)),
                         1,
                         logic_accessor::data(enable),
                         sloc));
}

template <typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init, CH_SLOC) {
  return ch_nextEn<ch_logic_t<T>, T, I, E>(in, enable, init, sloc);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_delay(const T& in, uint32_t delay = 1, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  if (0 == delay) {
    return R(in, sloc);
  }
  return R(createRegNext(logic_accessor::data(R(in, sloc)), delay, sloc));
}

template <typename T>
auto ch_delay(const T& in, uint32_t delay = 1, CH_SLOC) {
  return ch_delay<ch_logic_t<T>, T>(in, delay, sloc);
}

template <typename R, typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  if (0 == delay) {
    return R(in, sloc);
  }
  return R(createRegNext(logic_accessor::data(R(in, sloc)),
                         logic_accessor::data(R(init, sloc)),
                         delay,
                         sloc));
}

template <typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init, CH_SLOC) {
  return ch_delay<ch_logic_t<T>, T>(in, delay, init, sloc);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay = 1, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  if (0 == delay) {
    return R(in, sloc);
  }
  return R(createRegNext(logic_accessor::data(R(in, sloc)),
                         delay,
                         logic_accessor::data(enable),
                         sloc));
}

template <typename T, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay = 1, CH_SLOC) {
  return ch_delayEn<ch_logic_t<T>, T, E>(in, enable, delay, sloc);
}

template <typename R, typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  if (0 == delay) {
    return R(in, sloc);
  }
  return R(createRegNext(logic_accessor::data(R(in, sloc)),
                         logic_accessor::data(R(init, sloc)),
                         delay,
                         logic_accessor::data(enable),                         
                         sloc));
}

template <typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init, CH_SLOC) {
  return ch_delayEn<ch_logic_t<T>, T, I, E>(in, enable, delay, init, sloc);
}

///////////////////////////////////////////////////////////////////////////////

template <typename Func, typename... Ls>
auto ch_pipe(Func&& func, Ls&&... latencies) {
  beginPipe({std::forward<Ls>(latencies)...});
  func;
  endPipe();
}

}
}
