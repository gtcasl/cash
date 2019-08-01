#pragma once

#include "bit.h"
#include "if.h"

namespace ch {
namespace internal {

lnodeimpl* createRegNode(unsigned size, const std::string& name);

lnodeimpl* createRegNode(const lnode& init, const std::string& name);

lnodeimpl* copyRegNode(const lnode& node, const std::string& name);

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

  template <typename Arg0, typename... Args,
            CH_REQUIRE(std::is_constructible_v<T, Arg0, Args...>
                    && !std::is_same_v<remove_cv_ref_t<Arg0>, ch_reg_impl>)>
  ch_reg_impl(Arg0&& arg0, Args&&... args)
    : base(make_logic_buffer(createRegNode(
              get_lnode(T(std::forward<Arg0>(arg0), std::forward<Args>(args)...)), idname<T>()))) {
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
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in), 1, idname<R>()));
}

template <typename T>
auto ch_next(const T& in) {
  CH_API_ENTRY(1);
  static_assert(is_data_type_v<T>, "invalid type");
  return ch_next<ch_logic_t<T>, T>(in);
}

template <typename R, typename T, typename I>
auto ch_next(const T& in, const I& init) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
                                    to_lnode<R>(init),
                                    1,
                                    idname<R>()));
}

template <typename T, typename I>
auto ch_next(const T& in, const I& init) {
  CH_API_ENTRY(1);
  return ch_next<ch_logic_t<T>, T, I>(in, init);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_nextEn(const T& in, const E& enable) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
                                    1,
                                    get_lnode(enable),
                                    idname<R>()));
}

template <typename T, typename E>
auto ch_nextEn(const T& in, const E& enable) {
  CH_API_ENTRY(1);
  return ch_nextEn<ch_logic_t<T>, T, E>(in, enable);
}

template <typename R, typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");  
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in),
                                    to_lnode<R>(init),
                                    1,
                                    get_lnode(enable),
                                    idname<R>()));
}

template <typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init) {
  CH_API_ENTRY(1);
  return ch_nextEn<ch_logic_t<T>, T, I, E>(in, enable, init);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_delay(const T& in, uint32_t delay = 1) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  if (0 == delay) {
    return R(in);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in), delay, idname<R>()));
}

template <typename T>
auto ch_delay(const T& in, uint32_t delay = 1) {
  CH_API_ENTRY(1);
  return ch_delay<ch_logic_t<T>, T>(in, delay);
}

template <typename R, typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
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
  CH_API_ENTRY(1);
  return ch_delay<ch_logic_t<T>, T>(in, delay, init);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay = 1) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
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
  CH_API_ENTRY(1);
  return ch_delayEn<ch_logic_t<T>, T, E>(in, enable, delay);
}

template <typename R, typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
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
  CH_API_ENTRY(1);
  return ch_delayEn<ch_logic_t<T>, T, I, E>(in, enable, delay, init);
}

}
}
