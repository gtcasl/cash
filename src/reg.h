#pragma once

#include "bit.h"
#include "select.h"

namespace cash {
namespace internal {

lnodeimpl* createRegNode(const lnode& next, const lnode& init);
lnodeimpl* createLatchNode(const lnode& next,
                           const lnode& init,
                           const lnode& enable,
                           const lnode& reset);

lnodeimpl* createReadyNode(const lnode& node);
lnodeimpl* createValidNode(const lnode& node);

const ch_bit<1> ch_getClock();
void ch_pushClock(const ch_bitbase<1>& clk);
void ch_popClock();

const ch_bit<1> ch_getReset();
void ch_pushReset(const ch_bitbase<1>& reset);
void ch_popReset();

template <unsigned N>
const auto ch_ready(const ch_bitbase<N>& x) {
  return make_bit<1>(createReadyNode(get_lnode(x)));
}

template <unsigned N>
const auto ch_valid(const ch_bitbase<N>& x) {
  return make_bit<1>(createValidNode(get_lnode(x)));
}

template <typename T, typename I,
          CH_REQUIRES(deduce_bitcount<T, I>::value != 0),
          CH_REQUIRES(is_cast_convertible<T, ch_bit<deduce_bitcount<T, I>::value>>::value),
          CH_REQUIRES(is_cast_convertible<I, ch_bit<deduce_bitcount<T, I>::value>>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_bit<deduce_bitcount<T, I>::value>(
    createRegNode(get_lnode<T, deduce_bitcount<T, I>::value>(next),
                  get_lnode<I, deduce_bitcount<T, I>::value>(init)));
}

template <unsigned N, typename T, typename I,
          CH_REQUIRES(is_cast_convertible<T, ch_bit<N>>::value),
          CH_REQUIRES(is_cast_convertible<I, ch_bit<N>>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_bit<N>(
    createRegNode(get_lnode<T, N>(next),
                  get_lnode<I, N>(init)));
}

template <typename T,
          CH_REQUIRES(is_cast_convertible<T, ch_bit<T::bitcount>>::value)>
const auto ch_reg(const T& next) {
  return make_bit<T::bitcount>(
    createRegNode(get_lnode(next), get_lnode(ch_bit<T::bitcount>(0))));
}

template <unsigned N, typename T,
          CH_REQUIRES(is_cast_convertible<T, ch_bit<N>>::value)>
const auto ch_reg(const T& next) {
  return make_bit<N>(
    createRegNode(get_lnode(next), get_lnode(ch_bit<N>(0))));
}

template <typename T, typename E, typename I, typename R,
          CH_REQUIRES(deduce_bitcount<T, I>::value != 0),
          CH_REQUIRES(is_cast_convertible<T, ch_bit<deduce_bitcount<T, I>::value>>::value),
          CH_REQUIRES(is_cast_convertible<E, ch_bit<1>>::value),
          CH_REQUIRES(is_cast_convertible<I, ch_bit<deduce_bitcount<T, I>::value>>::value),
          CH_REQUIRES(is_cast_convertible<R, ch_bit<1>>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init, const R& reset) {
  return make_bit<deduce_bitcount<T, I>::value>(
    createLatchNode(get_lnode<T, deduce_bitcount<T, I>::value>(next),
                    get_lnode<I, deduce_bitcount<T, I>::value>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode<R, 1>(reset)));
}

template <unsigned N, typename T, typename E, typename I, typename R,
          CH_REQUIRES(is_cast_convertible<T, ch_bit<N>>::value),
          CH_REQUIRES(is_cast_convertible<E, ch_bit<1>>::value),
          CH_REQUIRES(is_cast_convertible<I, ch_bit<N>>::value),
          CH_REQUIRES(is_cast_convertible<R, ch_bit<1>>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init, const R& reset) {
  return make_bit<N>(
    createLatchNode(get_lnode<T, N>(next),
                    get_lnode<I, N>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode<R, 1>(reset)));
}

template <typename T, typename E, typename I,
          CH_REQUIRES(deduce_bitcount<T, I>::value != 0),
          CH_REQUIRES(is_cast_convertible<T, ch_bit<deduce_bitcount<T, I>::value>>::value),
          CH_REQUIRES(is_cast_convertible<E, ch_bit<1>>::value),
          CH_REQUIRES(is_cast_convertible<I, ch_bit<deduce_bitcount<T, I>::value>>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init) {
  return make_bit<deduce_bitcount<T, I>::value>(
    createLatchNode(get_lnode<T, deduce_bitcount<T, I>::value>(next),
                    get_lnode<I, deduce_bitcount<T, I>::value>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

template <unsigned N, typename T, typename E, typename I,
          CH_REQUIRES(is_cast_convertible<T, ch_bit<N>>::value),
          CH_REQUIRES(is_cast_convertible<E, ch_bit<1>>::value),
          CH_REQUIRES(is_cast_convertible<I, ch_bit<N>>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init) {
  return make_bit<N>(
    createLatchNode(get_lnode<T, N>(next),
                    get_lnode<I, N>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

template <typename T, typename E,
          CH_REQUIRES(is_cast_convertible<T, ch_bit<T::bitcount>>::value),
          CH_REQUIRES(is_cast_convertible<E, ch_bit<1>>::value)>
const auto ch_latch(const T& next, const E& enable) {
  return make_bit<T::bitcount>(
    createLatchNode(get_lnode(next),
                    get_lnode(ch_bit<T::bitcount>(0)),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

template <unsigned N, typename T, typename E,
          CH_REQUIRES(is_cast_convertible<T, ch_bit<N>>::value),
          CH_REQUIRES(is_cast_convertible<E, ch_bit<1>>::value)>
const auto ch_latch(const T& next, const E& enable) {
  return make_bit<N>(
    createLatchNode(get_lnode(next),
                    get_lnode(ch_bit<N>(0)),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

}
}
