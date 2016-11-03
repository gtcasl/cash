#pragma once

#include "bitv.h"
#include "select.h"

namespace chdl_internal {

lnodeimpl* createRegNode(lnodeimpl* next);
lnodeimpl* createLatchNode(lnodeimpl* next, lnodeimpl* init, lnodeimpl* enable, lnodeimpl* reset);

lnodeimpl* createReadyNode(lnodeimpl* node);
lnodeimpl* createValidNode(lnodeimpl* node);

ch_logic ch_clock();
void ch_pushclock(const ch_logicbase& clk);
void ch_popclock();

ch_logic ch_reset();
void ch_pushreset(const ch_logicbase& reset);
void ch_popreset();

template <unsigned N>
ch_logic ch_ready(const ch_bitbase<N>& x) {
  return ch_logic(createReadyNode(x.get_node().get_impl()));
}

template <unsigned N>
ch_logic ch_valid(const ch_bitbase<N>& x) {
  return ch_logic(createValidNode(x.get_node().get_impl()));
}

template <unsigned N>
ch_bit<N> ch_reg(const ch_bitbase<N>& next, const ch_bitbase<N>& init) {
  ch_bit<N> d(ch_select(ch_reset(), init, next));
  return ch_bit<N>(createRegNode(d.get_node().get_impl()));
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
ch_bit<N> ch_latch(const ch_bitbase<N>& next, const ch_logicbase& enable, const ch_bitbase<N>& init) {
  return ch_bit<N>(createLatchNode(next.get_node().get_impl(), init.get_node().get_impl(), enable.get_node().get_impl(), ch_reset().get_node().get_impl()));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bitbase<N>& next, const ch_logicbase& enable, const ch_bit<N>& init = 0) {
  return ch_latch<N>(next, enable, reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bitbase<N>& next, const ch_logic& enable, const ch_bitbase<N>& init) {
  return ch_latch<N>(next, reinterpret_cast<const ch_logicbase&>(enable), init);
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bitbase<N>& next, const ch_logic& enable = 1, const ch_bit<N>& init = 0) {
  return ch_latch<N>(next, reinterpret_cast<const ch_logicbase&>(enable), 
                           reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_logicbase& enable, const ch_bitbase<N>& init) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), enable, init);
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_logicbase& enable, const ch_bit<N>& init = 0) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), 
                     enable, 
                     reinterpret_cast<const ch_bitbase<N>&>(init));
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_logic& enable, const ch_bitbase<N>& init) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), 
                     reinterpret_cast<const ch_logicbase&>(enable), init);
}

template <unsigned N>
ch_bit<N> ch_latch(const ch_bit<N>& next, const ch_logic& enable = 1, const ch_bit<N>& init = 0) {
  return ch_latch<N>(reinterpret_cast<const ch_bitbase<N>&>(next), 
                     reinterpret_cast<const ch_logicbase&>(enable), 
                     reinterpret_cast<const ch_bitbase<N>&>(init));
}

}
