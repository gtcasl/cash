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

const ch_bit<1> ch_getClock();

template <typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
inline void ch_pushClock(const T& clk) {
  static_assert(T::bitwidth == 1, "invalid predicate size");
  pushClock(get_lnode(clk));
}

void ch_popClock();

const ch_bit<1> ch_getReset();

template <typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
inline void ch_pushReset(const T& reset) {
  static_assert(T::bitwidth == 1, "invalid predicate size");
  pushReset(get_lnode(reset));
}

void ch_popReset();

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_ready(const T& x) {
  return make_type<ch_bit<1>>(createReadyNode(get_lnode(x)));
}

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_valid(const T& x) {
  return make_type<ch_bit<1>>(createValidNode(get_lnode(x)));
}

template <typename T, typename I,
          CH_REQUIRES(deduce_type_t<T, I>::bitwidth != 0),
          CH_REQUIRES(is_bit_convertible<T, deduce_type_t<T, I>::bitwidth>::value),
          CH_REQUIRES(is_bit_convertible<I, deduce_type_t<T, I>::bitwidth>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_type<value_type_t<deduce_first_type_t<T, I>>>(
    createRegNode(get_lnode<T, deduce_type_t<T, I>::bitwidth>(next),
                  get_lnode<I, deduce_type_t<T, I>::bitwidth>(init)));
}

template <typename R, typename T, typename I,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_cast_convertible<R, I>::value)>
const auto ch_reg(const T& next, const I& init) {
  return make_type<R>(
    createRegNode(get_lnode<T, R::bitwidth>(next),
                  get_lnode<I, R::bitwidth>(init)));
}

template <typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_reg(const T& next) {
  return make_type<value_type_t<T>>(
    createRegNode(get_lnode(next), get_lnode<int, T::bitwidth>(0)));
}

template <typename R, typename T,
          CH_REQUIRES(is_cast_convertible<R, T>::value)>
const auto ch_reg(const T& next) {
  return make_type<R>(
    createRegNode(get_lnode<T, R::bitwidth>(next), get_lnode<int, R::bitwidth>(0)));
}

template <typename T, typename E, typename I, typename Z,
          CH_REQUIRES(deduce_type_t<T, I>::bitwidth != 0),
          CH_REQUIRES(is_bit_convertible<T, deduce_type_t<T, I>::bitwidth>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_bit_convertible<I, deduce_type_t<T, I>::bitwidth>::value),
          CH_REQUIRES(is_bit_convertible<Z>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init, const Z& reset) {
  static_assert(E::bitwidth == 1, "invalid predicate size");
  static_assert(Z::bitwidth == 1, "invalid predicate size");
  return make_type<value_type_t<deduce_first_type_t<T, I>>>(
    createLatchNode(get_lnode<T, deduce_type_t<T, I>::bitwidth>(next),
                    get_lnode<I, deduce_type_t<T, I>::bitwidth>(init),
                    get_lnode(enable),
                    get_lnode(reset)));
}

template <typename R, typename T, typename E, typename I, typename Z,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_cast_convertible<R, I>::value),
          CH_REQUIRES(is_bit_convertible<Z>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init, const Z& reset) {
  static_assert(E::bitwidth == 1, "invalid predicate size");
  static_assert(Z::bitwidth == 1, "invalid predicate size");
  return make_type<R>(
    createLatchNode(get_lnode<T, R::bitwidth>(next),
                    get_lnode<I, R::bitwidth>(init),
                    get_lnode(enable),
                    get_lnode(reset)));
}

template <typename T, typename E, typename I,
          CH_REQUIRES(deduce_type_t<T, I>::bitwidth != 0),
          CH_REQUIRES(is_bit_convertible<T, deduce_type_t<T, I>::bitwidth>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_bit_convertible<I, deduce_type_t<T, I>::bitwidth>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init) {
  static_assert(E::bitwidth == 1, "invalid predicate size");
  return make_type<value_type_t<deduce_first_type_t<T, I>>>(
    createLatchNode(get_lnode<T, deduce_type_t<T, I>::bitwidth>(next),
                    get_lnode<I, deduce_type_t<T, I>::bitwidth>(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename R, typename T, typename E, typename I,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value),
          CH_REQUIRES(is_cast_convertible<R, I>::value)>
const auto ch_latch(const T& next, const E& enable, const I& init) {
  static_assert(E::bitwidth == 1, "invalid predicate size");
  return make_type<R>(
    createLatchNode(get_lnode<T, R::bitwidth>(next),
                    get_lnode<I, R::bitwidth>(init),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename T, typename E,
          CH_REQUIRES(is_bit_convertible<T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value)>
const auto ch_latch(const T& next, const E& enable) {
  static_assert(E::bitwidth == 1, "invalid predicate size");
  return make_type<value_type_t<T>>(
    createLatchNode(get_lnode(next),
                    get_lnode<int, T::bitwidth>(0),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

template <typename R, typename T, typename E,
          CH_REQUIRES(is_cast_convertible<R, T>::value),
          CH_REQUIRES(is_bit_convertible<E>::value)>
const auto ch_latch(const T& next, const E& enable) {
  static_assert(E::bitwidth == 1, "invalid predicate size");
  return make_type<R>(
        createLatchNode(get_lnode<T, R::bitwidth>(next),
                    get_lnode<int, R::bitwidth>(0),
                    get_lnode(enable),
                    get_lnode(ch_getReset())));
}

}
}
