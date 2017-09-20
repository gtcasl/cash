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

void pushClock(const lnode& node);
void pushReset(const lnode& node);

const ch_bit<1> ch_getClock();

inline void ch_pushClock(const ch_bitbase<1>& clk) {
  pushClock(get_lnode(clk));
}

void ch_popClock();

const ch_bit<1> ch_getReset();

inline void ch_pushReset(const ch_bitbase<1>& reset) {
  pushReset(get_lnode(reset));
}

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
          CH_REQUIRES(deduce_type<T, I>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<T, deduce_type<T, I>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<I, deduce_type<T, I>::bitcount>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_type<typename deduce_first_type<T, I>::type>(
    createRegNode(get_lnode<T, deduce_type<T, I>::bitcount>(next),
                  get_lnode<I, deduce_type<T, I>::bitcount>(init)));
}

template <unsigned N, typename T, typename I,
          CH_REQUIRES(is_bit_convertible<T, N>::value),
          CH_REQUIRES(is_bit_convertible<I, N>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_bit<N>(
    createRegNode(get_lnode<T, N>(next),
                  get_lnode<I, N>(init)));
}

template <typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_reg(const T& next) {
  return make_type<T>(
    createRegNode(get_lnode(next), get_lnode(ch_bit<T::bitcount>(0))));
}

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T, N>::value)>
const auto ch_reg(const T& next) {
  return make_bit<N>(
    createRegNode(get_lnode(next), get_lnode(ch_bit<N>(0))));
}

template <typename T, typename E, typename I, typename R,
          CH_REQUIRES(deduce_type<T, I>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<T, deduce_type<T, I>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<E, 1>::value),
          CH_REQUIRES(is_bit_convertible<I, deduce_type<T, I>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<R, 1>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init, const R& reset) {
  return make_type<typename deduce_first_type<T, I>::type>(
    createLatchNode(get_lnode<T, deduce_type<T, I>::bitcount>(next),
                    get_lnode<I, deduce_type<T, I>::bitcount>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode<R, 1>(reset)));
}

template <unsigned N, typename T, typename E, typename I, typename R,
          CH_REQUIRES(is_bit_convertible<T, N>::value),
          CH_REQUIRES(is_bit_convertible<E, 1>::value),
          CH_REQUIRES(is_bit_convertible<I, N>::value),
          CH_REQUIRES(is_bit_convertible<R, 1>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init, const R& reset) {
  return make_bit<N>(
    createLatchNode(get_lnode<T, N>(next),
                    get_lnode<I, N>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode<R, 1>(reset)));
}

template <typename T, typename E, typename I,
          CH_REQUIRES(deduce_type<T, I>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<T, deduce_type<T, I>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<E, 1>::value),
          CH_REQUIRES(is_bit_convertible<I, deduce_type<T, I>::bitcount>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init) {
  return make_type<typename deduce_first_type<T, I>::type>(
    createLatchNode(get_lnode<T, deduce_type<T, I>::bitcount>(next),
                    get_lnode<I, deduce_type<T, I>::bitcount>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

template <unsigned N, typename T, typename E, typename I,
          CH_REQUIRES(is_bit_convertible<T, N>::value),
          CH_REQUIRES(is_bit_convertible<E, 1>::value),
          CH_REQUIRES(is_bit_convertible<I, N>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init) {
  return make_bit<N>(
    createLatchNode(get_lnode<T, N>(next),
                    get_lnode<I, N>(init),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

template <typename T, typename E,
          CH_REQUIRES(is_bit_convertible<T>::value),
          CH_REQUIRES(is_bit_convertible<E, 1>::value)>
const auto ch_latch(const T& next, const E& enable) {
  return make_type<T>(
    createLatchNode(get_lnode(next),
                    get_lnode(ch_bit<T::bitcount>(0)),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

template <unsigned N, typename T, typename E,
          CH_REQUIRES(is_bit_convertible<T, N>::value),
          CH_REQUIRES(is_bit_convertible<E, 1>::value)>
const auto ch_latch(const T& next, const E& enable) {
  return make_bit<N>(
    createLatchNode(get_lnode(next),
                    get_lnode(ch_bit<N>(0)),
                    get_lnode<E, 1>(enable),
                    get_lnode(ch_getReset())));
}

}
}
