#pragma once

#include "bit.h"
#include "if.h"

namespace ch {
namespace internal {

logic_buffer createRegNode(unsigned size, const std::string& name,
                           const sloc_getter& slg = sloc_getter());

logic_buffer createRegNode(const lnode& init, const std::string& name,
                           const sloc_getter& slg = sloc_getter());

logic_buffer copyRegNode(const lnode& node, const std::string& name,
                         const sloc_getter& slg = sloc_getter());

logic_buffer getRegNextNode(const lnode& node);

logic_buffer createRegNext(const lnode& next,
                           unsigned length,
                           const std::string& name);

logic_buffer createRegNext(const lnode& next,
                           unsigned length,
                           const lnode& enable,
                           const std::string& name);

logic_buffer createRegNext(const lnode& next,
                           const lnode& init,
                           unsigned length,
                           const std::string& name);

logic_buffer createRegNext(const lnode& next,
                           const lnode& init,
                           unsigned length,
                           const lnode& enable,
                           const std::string& name);

void pushClockDomain(const lnode& clock, const lnode& reset, bool pos_edge);

void beginPipe(uint32_t length, const std::vector<int>& bounds);

void beginPipe(uint32_t length, const lnode& enable, const std::vector<int>& bounds);

void endPipe(const lnode& ret);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg final : public std::add_const_t<T> {
public:  
  using traits = logic_traits<ch_width_v<T>, ch_signed_v<T>, T, ch_system_t<T>>;
  using base = T;

  ch_reg()
    : base(createRegNode(ch_width_v<T>, idname<T>())) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  template <typename U0,
            CH_REQUIRE_0(std::is_convertible_v<U0, T>)>
  explicit ch_reg(const U0& init0)
    : base(createRegNode(to_lnode<T>(init0), idname<T>())) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  template <typename... Us,
            CH_REQUIRE_0(std::is_constructible_v<T, Us...>)>
  explicit ch_reg(const Us&... inits)
    : base(createRegNode(get_lnode(T(inits...)), idname<T>())) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  ch_reg(const ch_reg& other)
    : base(copyRegNode(get_lnode(other), idname<T>())) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  ch_reg(ch_reg&& other)
    : base(std::move(get_lnode(other))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  auto& operator->() const {
    return __next__;
  }  

private:

  ch_reg& operator=(ch_reg&&) = delete;

  struct next_t {
    next_t(const logic_buffer& buffer) : next(buffer) {}
    T next;
  };

  std::unique_ptr<next_t> __next__;
};

///////////////////////////////////////////////////////////////////////////////

ch_bit<1> ch_clock();

ch_bit<1> ch_reset();

template <typename C, typename R = ch_bit<1>>
void ch_pushcd(const C& clk, const R& reset = ch_reset(), bool pos_edge = true) {
  static_assert(is_bit_base_v<C>, "invalid type");
  static_assert(ch_width_v<C> == 1, "invalid size");
  static_assert(is_bit_base_v<R>, "invalid type");
  static_assert(ch_width_v<R> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  pushClockDomain(get_lnode(clk), get_lnode(reset), pos_edge);
}

void ch_popcd();

template <typename Func, typename C, typename R = ch_bit<1>>
void ch_cd(Func&& func,
           const C& clk,
           const R& reset = ch_reset(),
           bool pos_edge = true) {
  CH_SOURCE_LOCATION(1);
  ch_pushcd(clk, reset, pos_edge);
  func;
  ch_popcd();
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_next(const T& in) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return R(createRegNext(to_lnode<R>(in), 1, idname<R>()));
}

template <typename T>
auto ch_next(const T& in) {
  static_assert(is_object_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return ch_next<ch_logic_t<T>, T>(in);
}

template <typename R, typename T, typename I>
auto ch_next(const T& in, const I& init) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return R(createRegNext(to_lnode<R>(in),
                         to_lnode<R>(init),
                         1,
                         idname<R>()));
}

template <typename T, typename I>
auto ch_next(const T& in, const I& init) {
  CH_SOURCE_LOCATION(1);
  return ch_next<ch_logic_t<T>, T, I>(in, init);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_nextEn(const T& in, const E& enable) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  return R(createRegNext(to_lnode<R>(in),
                         1,
                         get_lnode(enable),
                         idname<R>()));
}

template <typename T, typename E>
auto ch_nextEn(const T& in, const E& enable) {
  CH_SOURCE_LOCATION(1);
  return ch_nextEn<ch_logic_t<T>, T, E>(in, enable);
}

template <typename R, typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");  
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  return R(createRegNext(to_lnode<R>(in),
                         to_lnode<R>(init),
                         1,
                         get_lnode(enable),
                         idname<R>()));
}

template <typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init) {
  CH_SOURCE_LOCATION(1);
  return ch_nextEn<ch_logic_t<T>, T, I, E>(in, enable, init);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_delay(const T& in, uint32_t delay = 1) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  if (0 == delay) {
    return R(in);
  }
  return R(createRegNext(to_lnode<R>(in),
                         delay,
                         idname<R>()));
}

template <typename T>
auto ch_delay(const T& in, uint32_t delay = 1) {
  CH_SOURCE_LOCATION(1);
  return ch_delay<ch_logic_t<T>, T>(in, delay);
}

template <typename R, typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  CH_SOURCE_LOCATION(1);
  if (0 == delay) {
    return R(in);
  }
  return R(createRegNext(to_lnode<R>(in),
                         to_lnode<R>(init),
                         delay,
                         idname<R>()));
}

template <typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init) {
  CH_SOURCE_LOCATION(1);
  return ch_delay<ch_logic_t<T>, T>(in, delay, init);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay = 1) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  if (0 == delay) {
    return R(in);
  }
  return R(createRegNext(to_lnode<R>(in),
                         delay,
                         get_lnode(enable),
                         idname<R>()));
}

template <typename T, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay = 1) {
  CH_SOURCE_LOCATION(1);
  return ch_delayEn<ch_logic_t<T>, T, E>(in, enable, delay);
}

template <typename R, typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  if (0 == delay) {
    return R(in);
  }
  return R(createRegNext(to_lnode<R>(in),
                         to_lnode<R>(init),
                         delay,
                         get_lnode(enable),
                         idname<R>()));
}

template <typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init) {
  CH_SOURCE_LOCATION(1);
  return ch_delayEn<ch_logic_t<T>, T, I, E>(in, enable, delay, init);
}

///////////////////////////////////////////////////////////////////////////////

template <typename Func, typename... Bs>
auto ch_pipe(Func&& func, uint32_t length, Bs&&... bounds) {
  CH_SOURCE_LOCATION(1);
  beginPipe(length, {std::forward<Bs>(bounds)...});
  auto ret = func;
  endPipe(get_lnode(ret));
  return ret;
}

template <typename Func, typename E, typename... Bs>
auto ch_pipeEn(Func&& func, const E& enable, uint32_t length, Bs&&... bounds) {
  static_assert(is_bit_base_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  beginPipe(length, get_lnode(enable), {std::forward<Bs>(bounds)...});
  auto ret = func;
  endPipe(get_lnode(ret));
  return ret;
}

}
}
