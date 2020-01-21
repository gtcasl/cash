#pragma once

#include "bit.h"
#include "if.h"

namespace ch {
namespace internal {

lnodeimpl* createRegNode(unsigned size, 
                         const std::string& name, 
                         const source_info& sloc);

lnodeimpl* createRegNode(const lnode& init, 
                         const std::string& name, 
                         const source_info& sloc);

lnodeimpl* copyRegNode(const lnode& node, 
                       const std::string& name, 
                       const source_info& sloc);

lnodeimpl* getRegNextNode(const lnode& node);

lnodeimpl* createRegNext(const lnode& next,
                         unsigned length,
                         const std::string& name,
                         const source_info& sloc);

lnodeimpl* createRegNext(const lnode& next,
                         unsigned length,
                         const lnode& enable,
                         const std::string& name,
                         const source_info& sloc);

lnodeimpl* createRegNext(const lnode& next,
                         const lnode& init,
                         unsigned length,
                         const std::string& name,
                         const source_info& sloc);

lnodeimpl* createRegNext(const lnode& next,
                         const lnode& init,
                         unsigned length,
                         const lnode& enable,
                         const std::string& name,
                         const source_info& sloc);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg_impl final : public T {
public:  
  using traits = logic_traits<ch_width_v<T>, is_signed_v<T>, T, ch_system_t<T>>;
  using base = T;

  ch_reg_impl(CH_SLOC)
    : base(make_logic_buffer(createRegNode(ch_width_v<T>, idname<T>(), sloc))) {
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this)));
  }

#define CH_REG_GEN_TMPL(a, i, x) typename Arg##i
#define CH_REG_GEN_TYPE(a, i, x) Arg##i
#define CH_REG_GEN_DECL(a, i, x) Arg##i&& arg##i
#define CH_REG_GEN_ARG(a, i, x)  std::forward<Arg##i>(arg##i)
#define CH_REG_GEN(...) \
  template <CH_FOR_EACH(CH_REG_GEN_TMPL, , CH_SEP_COMMA, __VA_ARGS__), \
            CH_REQUIRE(std::is_constructible_v<T, CH_FOR_EACH(CH_REG_GEN_TYPE, , CH_SEP_COMMA, __VA_ARGS__)>)> \
  ch_reg_impl(CH_FOR_EACH(CH_REG_GEN_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) \
    : base(make_logic_buffer(createRegNode( \
        get_lnode(T(CH_FOR_EACH(CH_REG_GEN_ARG, , CH_SEP_COMMA, __VA_ARGS__), sloc)), idname<T>(), sloc))) { \
    __next__ = std::make_unique<next_t>(getRegNextNode(get_lnode(*this))); \
  }
CH_VA_ARGS_MAP(CH_REG_GEN)
#undef CH_REG_GEN_TMPL
#undef CH_REG_GEN_TYPE
#undef CH_REG_GEN_DECL
#undef CH_REG_GEN_ARG
#undef CH_REG_GEN

  ch_reg_impl(const ch_reg_impl& other, CH_SLOC)
    : base(make_logic_buffer(copyRegNode(get_lnode(other), idname<T>(), sloc))) {
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
auto ch_next(const T& in, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc), 
                                          1, 
                                          idname<R>(), 
                                          sloc));
}

template <typename T>
auto ch_next(const T& in, CH_SLOC) {
  static_assert(is_data_type_v<T>, "invalid type");
  return ch_next<ch_logic_t<T>, T>(in, sloc);
}

template <typename R, typename T, typename I>
auto ch_next(const T& in, const I& init, CH_SLOC) {
  static_assert(is_logic_type_v<R>, "invalid type");
  static_assert(std::is_constructible_v<R, T>, "invalid type");
  static_assert(std::is_constructible_v<R, I>, "invalid type");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc),
                                          to_lnode<R>(init, sloc),
                                          1,
                                          idname<R>(), 
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc),
                                          1,
                                          get_lnode(enable),
                                          idname<R>(), 
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc),
                                          to_lnode<R>(init, sloc),
                                          1,
                                          get_lnode(enable),
                                          idname<R>(), 
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
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc), delay, idname<R>(), sloc));
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
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc),
                                          to_lnode<R>(init, sloc),
                                          delay,
                                          idname<R>(), 
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  if (0 == delay) {
    return R(in, sloc);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc),
                                          delay,
                                          get_lnode(enable),
                                          idname<R>(),
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
  static_assert(is_bitbase_v<E>, "invalid type");
  static_assert(ch_width_v<E> == 1, "invalid size");
  if (0 == delay) {
    return R(in, sloc);
  }
  return make_logic_type<R>(createRegNext(to_lnode<R>(in, sloc),
                                          to_lnode<R>(init, sloc),
                                          delay,
                                          get_lnode(enable),
                                          idname<R>(), 
                                          sloc));
}

template <typename T, typename I, typename E>
auto ch_delayEn(const T& in, const E& enable, uint32_t delay, const I& init, CH_SLOC) {
  return ch_delayEn<ch_logic_t<T>, T, I, E>(in, enable, delay, init, sloc);
}

}
}
