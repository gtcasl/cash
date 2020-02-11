#pragma once

#include "bit.h"
#include "if.h"

namespace ch {
namespace internal {

lnodeimpl* createRegNode(unsigned size, 
                         const std::string& name, 
                         const source_location& sloc);

lnodeimpl* createRegNode(const lnode& init, 
                         const std::string& name, 
                         const source_location& sloc);

lnodeimpl* copyRegNode(const lnode& node, 
                       const std::string& name, 
                       const source_location& sloc);

lnodeimpl* getRegNextNode(const lnode& node);

lnodeimpl* createRegNext(const lnode& next, 
                         unsigned length, 
                         const std::string& name, 
                         const source_location& sloc);

lnodeimpl* createRegNext(const lnode& next,
                         unsigned length,
                         const lnode& enable,
                         const std::string& name, 
                         const source_location& sloc);

lnodeimpl* createRegNext(const lnode& next,
                         const lnode& init,
                         unsigned length,
                         const std::string& name, 
                         const source_location& sloc);

lnodeimpl* createRegNext(const lnode& next,
                         const lnode& init,
                         unsigned length,
                         const lnode& enable,
                         const std::string& name, 
                         const source_location& sloc);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg_impl final : public T {
public:  
  static_assert(is_logic_only_v<T>, "invalid type");
  using traits = reg_traits<ch_width_v<T>, is_signed_v<T>, T, ch_system_t<T>>;
  using base = T;

  explicit ch_reg_impl(CH_SRC_INFO)
    : base(make_logic_buffer(createRegNode(ch_width_v<T>, srcinfo.name(), srcinfo.sloc()))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

#define CH_REG_GEN_TMPL(a, i, x) typename Arg##i
#define CH_REG_GEN_TYPE(a, i, x) Arg##i
#define CH_REG_GEN_DECL(a, i, x) Arg##i&& arg##i
#define CH_REG_GEN_ARG(a, i, x)  std::forward<Arg##i>(arg##i)
#define CH_REG_GEN_SINFO(a, i, x) !std::is_same_v<std::decay_t<Arg##i>, source_info>
#define CH_REG_GEN(...) \
  template <CH_FOR_EACH(CH_REG_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRES(CH_FOR_EACH(CH_REG_GEN_SINFO, , CH_SEP_ANDL, __VA_ARGS__) \
                     && std::is_constructible_v<T, CH_FOR_EACH(CH_REG_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)>)> \
  ch_reg_impl(CH_FOR_EACH(CH_REG_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SRC_INFO) \
    : base(make_logic_buffer(createRegNode( \
        get_lnode(T(CH_FOR_EACH(CH_REG_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__), srcinfo)), srcinfo.name(), srcinfo.sloc()))) { \
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this))); \
  }
CH_VA_ARGS_MAP(CH_REG_GEN)
#undef CH_REG_GEN_TMPL
#undef CH_REG_GEN_TYPE
#undef CH_REG_GEN_DECL
#undef CH_REG_GEN_ARG
#undef CH_REG_GEN_SINFO
#undef CH_REG_GEN

  ch_reg_impl(const ch_reg_impl& other, CH_SRC_INFO)
    : base(make_logic_buffer(copyRegNode(get_lnode(other), srcinfo.name(), srcinfo.sloc()))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

  ch_reg_impl(ch_reg_impl&& other)
    : base(std::move(other)) {
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
auto ch_next(const T& in, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo), 
                                          1, 
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T>
auto ch_next(const T& in, CH_SRC_INFO) {
  static_assert(is_data_type_v<T>, "invalid type");
  return ch_next<ch_logic_t<T>, T>(in, srcinfo);
}

template <typename R, typename T, typename I>
auto ch_next(const T& in, const I& init, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo),
                                          to_lnode<R>(init, srcinfo),
                                          1,
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T, typename I>
auto ch_next(const T& in, const I& init, CH_SRC_INFO) {
  return ch_next<ch_logic_t<T>, T, I>(in, init, srcinfo);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_nextEn(const T& in, const E& enable, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo),
                                          1,
                                          get_lnode(enable),
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T, typename E>
auto ch_nextEn(const T& in, const E& enable, CH_SRC_INFO) {
  return ch_nextEn<ch_logic_t<T>, T, E>(in, enable, srcinfo);
}

template <typename R, typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");  
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo),
                                          to_lnode<R>(init, srcinfo),
                                          1,
                                          get_lnode(enable),
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T, typename I, typename E>
auto ch_nextEn(const T& in, const E& enable, const I& init, CH_SRC_INFO) {
  return ch_nextEn<ch_logic_t<T>, T, I, E>(in, enable, init, srcinfo);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_delay(const T& in, uint32_t delay = 1, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  if (0 == delay) {
    return R(in, srcinfo);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo), 
                                          delay, 
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T>
auto ch_delay(const T& in, uint32_t delay = 1, CH_SRC_INFO) {
  return ch_delay<ch_logic_t<T>, T>(in, delay, srcinfo);
}

template <typename R, typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  if (0 == delay) {
    return R(in, srcinfo);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo),
                                          to_lnode<R>(init, srcinfo),
                                          delay, 
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T, typename I>
auto ch_delay(const T& in, uint32_t delay, const I& init, CH_SRC_INFO) {
  return ch_delay<ch_logic_t<T>, T>(in, delay, init, srcinfo);
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay = 1, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  if (0 == delay) {
    return R(in, srcinfo);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo),
                                          delay,
                                          get_lnode(enable),
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay = 1, CH_SRC_INFO) {
  return ch_delayEn<ch_logic_t<T>, T, E>(in, enable, delay, srcinfo);
}

template <typename R, typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init, CH_SRC_INFO) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  if (0 == delay) {
    return R(in, srcinfo);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, srcinfo),
                                          to_lnode<R>(init, srcinfo),
                                          delay,
                                          get_lnode(enable),
                                          srcinfo.name(), 
                                          srcinfo.sloc()));
}

template <typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init, CH_SRC_INFO) {
  return ch_delayEn<ch_logic_t<T>, T, I, E>(in, enable, delay, init, srcinfo);
}

}
}
