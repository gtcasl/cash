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
  return make_type<ch_bit<1>>(createReadyNode(get_lnode(x)));
}

template <unsigned N>
const auto ch_valid(const ch_bitbase<N>& x) {
  return make_type<ch_bit<1>>(createValidNode(get_lnode(x)));
}

template <typename T, typename I,
          CH_REQUIRES(deduce_type_t<T, I>::bitsize != 0),
          CH_REQUIRES(is_ch_bit_convertible<T, deduce_type_t<T, I>::bitsize>::value),
          CH_REQUIRES(is_ch_bit_convertible<I, deduce_type_t<T, I>::bitsize>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_type<deduce_first_type_t<T, I>>(
    createRegNode(get_lnode<T, deduce_type_t<T, I>::bitsize>(next),
                  get_lnode<I, deduce_type_t<T, I>::bitsize>(init)));
}

template <typename R, typename T, typename I,
          CH_REQUIRES(is_cast_convertible<T, R>::value),
          CH_REQUIRES(is_cast_convertible<I, R>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_type<R>(
    createRegNode(get_lnode<T, R::bitsize>(next),
                  get_lnode<I, R::bitsize>(init)));
}

template <typename T,
          CH_REQUIRES(is_ch_bit_convertible<T>::value)>
const auto ch_reg(const T& next) {
  return make_type<T>(
    createRegNode(get_lnode(next), get_lnode<int, T::bitsize>(0)));
}

template <typename R, typename T,
          CH_REQUIRES(is_cast_convertible<T, R>::value)>
const auto ch_reg(const T& next) {
  return make_type<R>(
    createRegNode(get_lnode<T, R::bitsize>(next), get_lnode<int, R::bitsize>(0)));
}

template <typename T, typename I,
          CH_REQUIRES(deduce_type_t<T, I>::bitsize != 0),
          CH_REQUIRES(is_ch_bit_convertible<T, deduce_type_t<T, I>::bitsize>::value),
          CH_REQUIRES(is_ch_bit_convertible<I, deduce_type_t<T, I>::bitsize>::value)>
const auto ch_latch(const T& next, const ch_bitbase<1>& enable, const I& init, const ch_bitbase<1>& reset) {
  return make_type<deduce_first_type_t<T, I>>(
    createLatchNode(get_lnode<T, deduce_type_t<T, I>::bitsize>(next),
                    get_lnode<I, deduce_type_t<T, I>::bitsize>(init),
                    get_lnode(enable),
                    get_lnode(reset)));
}

template <typename R, typename T, typename I,
          CH_REQUIRES(is_cast_convertible<T, R>::value),
          CH_REQUIRES(is_cast_convertible<I, R>::value)>
const auto ch_latch(const T& next, const ch_bitbase<1>& enable, const I& init, const ch_bitbase<1>& reset) {
  return make_type<R>(
    createLatchNode(get_lnode<T, R::bitsize>(next),
                    get_lnode<I, R::bitsize>(init),
                    get_lnode(enable),
                    get_lnode(reset)));
}

template <typename T, typename I,
          CH_REQUIRES(deduce_type_t<T, I>::bitsize != 0),
          CH_REQUIRES(is_ch_bit_convertible<T, deduce_type_t<T, I>::bitsize>::value),
          CH_REQUIRES(is_ch_bit_convertible<I, deduce_type_t<T, I>::bitsize>::value)>
const auto ch_latch(const T& next, const ch_bitbase<1>& enable, const I& init) {
  return make_type<deduce_first_type_t<T, I>>(
    createLatchNode(get_lnode<T, deduce_type_t<T, I>::bitsize>(next),
                    get_lnode<I, deduce_type_t<T, I>::bitsize>(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename R, typename T, typename I,
          CH_REQUIRES(is_cast_convertible<T, R>::value),
          CH_REQUIRES(is_cast_convertible<I, R>::value)>
const auto ch_latch(const T& next, const ch_bitbase<1>& enable, const I& init) {
  return make_type<R>(
    createLatchNode(get_lnode<T, R::bitsize>(next),
                    get_lnode<I, R::bitsize>(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename T,
          CH_REQUIRES(is_ch_bit_convertible<T>::value)>
const auto ch_latch(const T& next, const ch_bitbase<1>& enable) {
  return make_type<T>(
    createLatchNode(get_lnode(next),
                    get_lnode<int, T::bitsize>(0),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename R, typename T,
          CH_REQUIRES(is_cast_convertible<T, R>::value)>
const auto ch_latch(const T& next, const ch_bitbase<1>& enable) {
  return make_type<R>(
    createLatchNode(get_lnode<T, R::bitsize>(next),
                    get_lnode<int, R::bitsize>(0),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

}
}
