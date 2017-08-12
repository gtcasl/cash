#pragma once

#include "bit.h"
#include "select.h"

namespace cash {
namespace detail {

lnodeimpl* createRegNode(lnodeimpl* next, lnodeimpl* init);
lnodeimpl* createLatchNode(lnodeimpl* next, lnodeimpl* init, lnodeimpl* enable, lnodeimpl* reset);

lnodeimpl* createReadyNode(lnodeimpl* node);
lnodeimpl* createValidNode(lnodeimpl* node);

ch_bit<1> ch_clock();
void ch_pushclock(const ch_bitbase<1>& clk);
void ch_popclock();

ch_bit<1> ch_reset();
void ch_pushreset(const ch_bitbase<1>& reset);
void ch_popreset();

template <unsigned N>
ch_bit<1> ch_ready(const ch_bitbase<N>& x) {
  return ch_bit<1>(createReadyNode(get_node(x).get_impl()));
}

template <unsigned N>
ch_bit<1> ch_valid(const ch_bitbase<N>& x) {
  return ch_bit<1>(createValidNode(get_node(x).get_impl()));
}

template <unsigned N>
ch_bit<N> ch_reg(const ch_bitbase<N>& next, const ch_bitbase<N>& init) {
  return ch_bit<N>(createRegNode(get_node(next).get_impl(), get_node(init).get_impl()));
}

template <unsigned N>
ch_bit<N> ch_reg(const ch_bitbase<N>& next, const ch_bit<N>& init = 0) {
  return ch_reg<N>(next, reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_reg(const ch_bit<N>& next, const ch_bitbase<N>& init) {
  return ch_reg<N>(reinterpret_cast<const ch_bitbase<N>&>(next), init);
}

template <unsigned N>
ch_bit<N> ch_reg(const ch_bit<N>& next, const ch_bit<N>& init) {
  return ch_reg<N>(reinterpret_cast<const ch_bitbase<N>&>(next), 
                reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bitbase<N>& next, 
                   const ch_bitbase<1>& enable,
                   const ch_bitbase<N>& init) {
  return ch_bit<N>(createLatchNode(get_node(next).get_impl(),
                                   get_node(init).get_impl(),
                                   get_node(enable).get_impl(),
                                   get_node(ch_reset()).get_impl()));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bitbase<N>& next, const ch_bitbase<1>& enable, const ch_bit<N>& init = 0) {
  return ch_latch<N>(next, enable, reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bitbase<N>& next, const ch_bit<1>& enable, const ch_bitbase<N>& init) {
  return ch_latch<N>(next, reinterpret_cast<const ch_bitbase<1>&>(enable), init);
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bitbase<N>& next, const ch_bit<1>& enable = 1, const ch_bit<N>& init = 0) {
  return ch_latch<N>(next, reinterpret_cast<const ch_bitbase<1>&>(enable),
                           reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_bitbase<1>& enable, const ch_bitbase<N>& init) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), enable, init);
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_bitbase<1>& enable, const ch_bit<N>& init = 0) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), 
                     enable, 
                     reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_bit<1>& enable, const ch_bitbase<N>& init) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), 
                     reinterpret_cast<const ch_bitbase<1>&>(enable), init);
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_bit<1>& enable = 1, const ch_bit<N>& init = 0) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), 
                     reinterpret_cast<const ch_bitbase<1>&>(enable),
                     reinterpret_cast<const ch_bitbase<N>&>(init));
}

}
}
