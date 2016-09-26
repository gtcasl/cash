#pragma once

#include "bitv.h"

namespace chdl_internal {

ch_node createRegNode(const ch_node& next);
ch_node createLatchNode(const ch_node& next, const ch_node& init, const ch_node& enable, const ch_node& reset);

ch_node createReadyNode(const ch_node& node);
ch_node createValidNode(const ch_node& node);

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
ch_bitv<N> ch_reg(const ch_bitbase<N>& next, const ch_bitbase<N>& init = ch_lit<N>(0x0)) {
  ch_bitv<N> d(ch_select(ch_reset(), init, next));
  return ch_bitv<N>(createRegNode(d));
}

template <unsigned N>
ch_bitv<N> ch_latch(const ch_bitbase<N>& next, const ch_bitbase<1>& enable) {
  ch_node init({0}, N);
  return ch_bitv<N>(createLatchNode(ch_bitv<N>(next), init, ch_bitv<1>(enable), ch_reset()));
}

template <unsigned N>
ch_bitv<N> ch_latch(const ch_bitbase<N>& next, const ch_bitbase<1>& enable, const ch_bitbase<N>& init) {
  return ch_bitv<N>(createLatchNode(ch_bitv<N>(next), ch_bitv<N>(init), ch_bitv<1>(enable), ch_reset()));
}

}
