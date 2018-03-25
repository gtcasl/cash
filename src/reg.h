#pragma once

#include "logic.h"
#include "select.h"

namespace ch {
namespace internal {

lnodeimpl* createRegNode(const lnode& next, const lnode& init);

void pushClock(const lnode& node);

void pushReset(const lnode& node);

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class ch_reg final : public const_type_t<T> {
public:
  using base = const_type_t<T>;
  using traits = logic_traits<width_v<T>, ch_reg, const_type_t<T>, T, scalar_type_t<T>>;

  T next;

  ch_reg(const source_location& sloc = CH_SRC_LOCATION)
    : base(logic_buffer(width_v<T>, sloc)) {
    auto reg = createRegNode(get_lnode(next), get_lnode<int, width_v<T>>(0));
    logic_accessor::set_data(*this, reg);
    next = *this;
  }

  template <typename U, CH_REQUIRE_0(is_cast_convertible<T, U>::value)>
  explicit ch_reg(const U& init,
                  const source_location& sloc = CH_SRC_LOCATION)
    : base(logic_buffer(width_v<T>, sloc)) {
    auto reg = createRegNode(get_lnode(next), get_lnode<U, T>(init));
    logic_accessor::set_data(*this, reg);
    next = *this;
  }

  ch_reg(ch_reg&& rhs) : base(std::move(rhs)) {}

  ch_reg& operator=(ch_reg&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

protected:

  ch_reg(ch_reg&) = delete;

  ch_reg& operator=(const ch_reg&) = delete;
};

///////////////////////////////////////////////////////////////////////////////

const ch_bit<1> ch_getClock();

template <typename T,
          CH_REQUIRE_0(is_bit_compatible<T>::value)>
inline void ch_pushClock(const T& clk) {
  static_assert(1 == width_v<T>, "invalid predicate size");
  pushClock(get_lnode(clk));
}

void ch_popClock();

///////////////////////////////////////////////////////////////////////////////

const ch_bit<1> ch_getReset();

template <typename T,
          CH_REQUIRE_0(is_bit_compatible<T>::value)>
inline void ch_pushReset(const T& reset) {
  static_assert(1 == width_v<T>, "invalid predicate size");
  pushReset(get_lnode(reset));
}

void ch_popReset();

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename I,
          CH_REQUIRE_0(width_v<deduce_type_t<false, T, I>> != 0),
          CH_REQUIRE_0(is_bit_convertible<T, width_v<deduce_type_t<false, T, I>>>::value),
          CH_REQUIRE_0(is_bit_convertible<I, width_v<deduce_type_t<false, T, I>>>::value)>
auto ch_regNext(const T& next, const I& init) {
  return make_type<logic_value_t<deduce_first_type_t<T, I>>>(
    createRegNode(get_lnode<T, width_v<deduce_type_t<false, T, I>>>(next),
                  get_lnode<I, width_v<deduce_type_t<false, T, I>>>(init)));
}

template <typename R, typename T, typename I,
          CH_REQUIRE_0(is_cast_convertible<R, T>::value),
          CH_REQUIRE_0(is_cast_convertible<R, I>::value)>
auto ch_regNext(const T& next, const I& init) {
  return make_type<R>(createRegNode(get_lnode<T, R>(next),
                                    get_lnode<I, R>(init)));
}

template <typename T,
          CH_REQUIRE_0(is_bit_convertible<T>::value)>
auto ch_regNext(const T& next) {
  ch_bit<width_v<T>> init(0);
  return make_type<logic_value_t<T>>(
    createRegNode(get_lnode(next), get_lnode(init)));
}

template <typename R, typename T,
          CH_REQUIRE_0(is_cast_convertible<R, T>::value)>
auto ch_regNext(const T& next) {
  ch_bit<width_v<R>> init(0);
  return make_type<R>(
    createRegNode(get_lnode<T, R>(next), get_lnode(init)));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned Delay, typename T,
          CH_REQUIRE_0(is_bit_convertible<T>::value)>
auto ch_delay(const T& rhs) {
  value_type_t<T> ret(rhs);
  for (unsigned i = 0; i < Delay; ++i) {
    ret = ch_regNext(ch_clone(ret));
  }
  return ret;
}

template <typename R, unsigned Delay, typename T,
          CH_REQUIRE_0(is_cast_convertible<R, T>::value)>
auto ch_delay(const T& rhs) {
  R ret(rhs);
  for (unsigned i = 0; i < Delay; ++i) {
    ret = ch_regNext(ch_clone(ret));
  }
  return ret;
}

}
}
