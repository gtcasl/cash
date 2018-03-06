#pragma once

#include "bit.h"
#include "select.h"

namespace ch {
namespace internal {

lnodeimpl* createRegNode(const lnode& next, const lnode& init);
lnodeimpl* createLatchNode(const lnode& next,
                           const lnode& init,
                           const lnode& enable,
                           const lnode& reset);

void pushClock(const lnode& node);
void pushReset(const lnode& node);

///////////////////////////////////////////////////////////////////////////////

const ch_bit<1> ch_getClock();

template <typename T,
          CH_REQUIRES(is_bit_compatible<T>::value)>
inline void ch_pushClock(const T& clk) {
  static_assert(1 == width_v<T>, "invalid predicate size");
  pushClock(get_lnode(clk));
}

void ch_popClock();

///////////////////////////////////////////////////////////////////////////////

const ch_bit<1> ch_getReset();

template <typename T,
          CH_REQUIRES(is_bit_compatible<T>::value)>
inline void ch_pushReset(const T& reset) {
  static_assert(1 == width_v<T>, "invalid predicate size");
  pushReset(get_lnode(reset));
}

void ch_popReset();

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename I,
          CH_REQUIRES(width_v<deduce_type_t<false, T, I>> != 0),
          CH_REQUIRES(is_bit_convertible<T, width_v<deduce_type_t<false, T, I>>>::value),
          CH_REQUIRES(is_bit_convertible<I, width_v<deduce_type_t<false, T, I>>>::value)>
auto ch_reg(const T& next, const I& init) {
  return make_type<bit_value_t<deduce_first_type_t<T, I>>>(
    createRegNode(get_lnode<T, width_v<deduce_type_t<false, T, I>>>(next),
                  get_lnode<I, width_v<deduce_type_t<false, T, I>>>(init)));
}

template <typename R, typename T, typename I,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_cast_convertible<R, I>::value)>
auto ch_reg(const T& next, const I& init) {
  return make_type<R>(
    createRegNode(get_lnode<T, R>(next),
                  get_lnode<I, R>(init)));
}

template <typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
auto ch_reg(const T& next) {
  ch_bit<width_v<T>> init(0);
  return make_type<bit_value_t<T>>(
    createRegNode(get_lnode(next), get_lnode(init)));
}

template <typename R, typename T,
          CH_REQUIRES(is_cast_convertible<R, T>::value)>
auto ch_reg(const T& next) {
  ch_bit<width_v<R>> init(0);
  return make_type<R>(
    createRegNode(get_lnode<T, R>(next), get_lnode(init)));
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename E, typename I, typename Z,
          CH_REQUIRES(width_v<deduce_type_t<false, T, I>> != 0),
          CH_REQUIRES(is_bit_convertible<T, width_v<deduce_type_t<false, T, I>>>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_bit_convertible<I, width_v<deduce_type_t<false, T, I>>>::value),
          CH_REQUIRES(is_bit_convertible<Z>::value)>
auto ch_latch(const T& next, const E& enable, const I& init, const Z& reset) {
  static_assert(1 == width_v<E>, "invalid predicate size");
  static_assert(1 == width_v<Z>, "invalid predicate size");
  return make_type<bit_value_t<deduce_first_type_t<T, I>>>(
    createLatchNode(get_lnode<T, width_v<deduce_type_t<false, T, I>>>(next),
                    get_lnode<I, width_v<deduce_type_t<false, T, I>>>(init),
                    get_lnode(enable),
                    get_lnode(reset)));
}

template <typename R, typename T, typename E, typename I, typename Z,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_cast_convertible<R, I>::value),
          CH_REQUIRES(is_bit_convertible<Z>::value)>
auto ch_latch(const T& next, const E& enable, const I& init, const Z& reset) {
  static_assert(1 == width_v<E>, "invalid predicate size");
  static_assert(1 == width_v<Z>, "invalid predicate size");
  return make_type<R>(
    createLatchNode(get_lnode<T, R>(next),
                    get_lnode<I, R>(init),
                    get_lnode(enable),
                    get_lnode(reset)));
}

template <typename T, typename E, typename I,
          CH_REQUIRES(width_v<deduce_type_t<false, T, I>> != 0),
          CH_REQUIRES(is_bit_convertible<T, width_v<deduce_type_t<false, T, I>>>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_bit_convertible<I, width_v<deduce_type_t<false, T, I>>>::value)>
auto ch_latch(const T& next, const E& enable, const I& init) {
  static_assert(1 == width_v<E>, "invalid predicate size");
  return make_type<bit_value_t<deduce_first_type_t<T, I>>>(
    createLatchNode(get_lnode<T, width_v<deduce_type_t<false, T, I>>>(next),
                    get_lnode<I, width_v<deduce_type_t<false, T, I>>>(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename R, typename T, typename E, typename I,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_cast_convertible<R, I>::value)>
auto ch_latch(const T& next, const E& enable, const I& init) {
  static_assert(1 == width_v<E>, "invalid predicate size");
  return make_type<R>(
    createLatchNode(get_lnode<T, R>(next),
                    get_lnode<I, R>(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename T, typename E,
          CH_REQUIRES(is_bit_convertible<T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value)>
auto ch_latch(const T& next, const E& enable) {
  static_assert(1 == width_v<E>, "invalid predicate size");
  ch_bit<width_v<T>> init(0);
  return make_type<bit_value_t<T>>(
    createLatchNode(get_lnode(next),
                    get_lnode(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename R, typename T, typename E,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value)>
auto ch_latch(const T& next, const E& enable) {
  static_assert(1 == width_v<E>, "invalid predicate size");
  ch_bit<width_v<R>> init(0);
  return make_type<R>(
        createLatchNode(get_lnode<T, R>(next),
                    get_lnode(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned Delay, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
auto ch_delay(const T& rhs) {
  value_type_t<T> ret(rhs);
  for (unsigned i = 0; i < Delay; ++i) {
    ret = ch_reg(ch_clone(ret));
  }
  return ret;
}

template <typename R, unsigned Delay, typename T,
          CH_REQUIRES(is_cast_convertible<R, T>::value)>
auto ch_delay(const T& rhs) {
  R ret(rhs);
  for (unsigned i = 0; i < Delay; ++i) {
    ret = ch_reg(ch_clone(ret));
  }
  return ret;
}

}
}
