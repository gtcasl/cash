#pragma once

#include "bitv.h"
#include "select.h"

namespace chdl_internal {

lnode createRegNode(const lnode& next);
lnode createLatchNode(const lnode& next, const lnode& init, const lnode& enable, const lnode& reset);

lnode createReadyNode(const lnode& node);
lnode createValidNode(const lnode& node);

ch_logic ch_clock();
void ch_pushclock(const ch_logic& clk);
void ch_popclock();

ch_logic ch_reset();
void ch_pushreset(const ch_logic& reset);
void ch_popreset();

template <unsigned N>
ch_logic ch_ready(const ch_bitv<N>& x) {
  return ch_logic(createReadyNode(x));
}

template <unsigned N>
ch_logic ch_valid(const ch_bitv<N>& x) {
  return ch_logic(createValidNode(x));
}

template <unsigned N>
ch_bitv<N> ch_reg(const ch_bitv<N>& next, const ch_bitv<N>& init = ch_bitv<N>(0x0)) {
  ch_bitv<N> d(ch_select(ch_reset(), init, next));
  return ch_bitv<N>(createRegNode(d));
}

/*inline ch_logic ch_reg(const ch_logic& next, const ch_logic& init 0_b_b) {
  ch_logic d(ch_select(ch_reset(), init, next));
  return ch_logic(createRegNode(d));
}*/

template <unsigned N>
ch_bitv<N> ch_latch(const ch_bitbase<N>& next, const ch_logicbase& enable) {
  lnode init({0}, N);
  return ch_bitv<N>(createLatchNode(next, init, enable, ch_reset()));
}

template <unsigned N>
ch_bitv<N> ch_latch(const ch_bitbase<N>& next, const ch_logicbase& enable, const ch_bitbase<N>& init) {
  return ch_bitv<N>(createLatchNode(next, init, enable, ch_reset()));
}

}
