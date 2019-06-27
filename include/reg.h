#pragma once

#include "bit.h"
#include "if.h"

namespace ch {
namespace internal {

lnodeimpl* createRegNode(unsigned size,
                         const std::string& name,
                         const sloc_getter& slg = sloc_getter());

lnodeimpl* createRegNode(const lnode& init,
                         const std::string& name,
                         const sloc_getter& slg = sloc_getter());

lnodeimpl* copyRegNode(const lnode& node,
                       const std::string& name,
                       const sloc_getter& slg = sloc_getter());

lnodeimpl* getRegNextNode(const lnode& node);

lnodeimpl* createRegNext(const lnode& next,
                         unsigned length,
                         const std::string& name);

lnodeimpl* createRegNext(const lnode& next,
                         unsigned length,
                         const lnode& enable,
                         const std::string& name);

lnodeimpl* createRegNext(const lnode& next,
                         const lnode& init,
                         unsigned length,
                         const std::string& name);

lnodeimpl* createRegNext(const lnode& next,
                         const lnode& init,
                         unsigned length,
                         const lnode& enable,
                         const std::string& name);

void beginPipe(uint32_t length, const std::vector<int>& bounds);

void beginPipe(uint32_t length, const lnode& enable, const std::vector<int>& bounds);

void endPipe(const lnode& ret);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg_impl final : public T {
public:  
  using traits = logic_traits<ch_width_v<T>, is_signed_v<T>, T, ch_system_t<T>>;
  using base = T;

  ch_reg_impl()
    : base(make_logic_buffer(createRegNode(ch_width_v<T>, idname<T>()))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  template <typename U0,
            CH_REQUIRE(std::is_convertible_v<U0, T>)>
  explicit ch_reg_impl(const U0& init0)
    : base(make_logic_buffer(createRegNode(to_lnode<T>(init0), idname<T>()))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  template <typename... Us,
            CH_REQUIRE(std::is_constructible_v<T, Us...>)>
  explicit ch_reg_impl(const Us&... inits)
    : base(make_logic_buffer(createRegNode(get_lnode(T(inits...)), idname<T>()))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  ch_reg_impl(const ch_reg_impl& other)
    : base(make_logic_buffer(copyRegNode(get_lnode(other), idname<T>()))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  ch_reg_impl(ch_reg_impl&& other)
    : base(std::move(logic_accessor::move(other))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  auto& operator->() const {
    return __next__;
  }  

private:

  ch_reg_impl& operator=(ch_reg_impl&&) = delete;

  struct next_t {
    next_t(lnodeimpl* impl) : next(make_logic_buffer(impl)) {}
    T next;
  };

  std::unique_ptr<next_t> __next__;
};

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_next(const T& in) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return make_logic_type<R>(createRegNext(to_lnode<R>(in), 1, idname<R>()));
}

template <typename T>
auto ch_next(const T& in) {
  static_assert(is_data_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return ch_next<ch_logic_t<T>, T>(in);
}

template <typename R, typename T, typename I>
auto ch_next(const T& in, const I& init) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
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
  return make_logic_type<R>(createRegNext(to_lnode<R>(in), delay, idname<R>()));
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
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  if (0 == delay) {
    return R(in);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  if (0 == delay) {
    return R(in);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  beginPipe(length, get_lnode(enable), {std::forward<Bs>(bounds)...});
  auto ret = func;
  endPipe(get_lnode(ret));
  return ret;
}

}
}
