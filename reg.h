#pragma once

#include "bitv.h"
#include "select.h"

namespace chdl_internal {

lnode createRegNode(const lnode& next);
lnode createLatchNode(const lnode& next, const lnode& init, const lnode& enable, const lnode& reset);

lnode createReadyNode(const lnode& node);
lnode createValidNode(const lnode& node);

ch_logic ch_clock();
void ch_pushclock(const ch_logicbase& clk);
void ch_popclock();

ch_logic ch_reset();
void ch_pushreset(const ch_logicbase& reset);
void ch_popreset();

template <unsigned N>
ch_logic ch_ready(const ch_bitbase<N>& x) {
  return ch_logic(createReadyNode(x));
}

template <unsigned N>
ch_logic ch_valid(const ch_bitbase<N>& x) {
  return ch_logic(createValidNode(x));
}

template <unsigned N>
ch_bitv<N> ch_reg(const ch_bitbase<N>& next, const ch_bitbase<N>& init = ch_bitv<N>(0x0)) {
  ch_bitv<N> d(ch_select(ch_reset(), init, next));
  return ch_bitv<N>(createRegNode(d));
}

#define CHDL_REG_GEN(type) \
  template <unsigned N> ch_bitv<N> ch_reg(type next, const ch_bitbase<N>& init) { return ch_reg(ch_bitv<N>(next), init); } \
  template <unsigned N> ch_bitv<N> ch_reg(const ch_bitbase<N>& next, type init) { return ch_reg(next, ch_bitv<N>(init)); } \
  template <unsigned N> ch_bitv<N> ch_reg(type next, type init = 0) { return ch_reg(ch_bitv<N>(next), ch_bitv<N>(init)); }
CHDL_REG_GEN(char)
CHDL_REG_GEN(int8_t)
CHDL_REG_GEN(uint8_t)
CHDL_REG_GEN(int16_t)
CHDL_REG_GEN(uint16_t)
CHDL_REG_GEN(int32_t)
CHDL_REG_GEN(uint32_t)
CHDL_REG_GEN(int64_t)
CHDL_REG_GEN(uint64_t)
#undef CHDL_REG_GEN

template <unsigned N>
ch_bitv<N> ch_latch(const ch_bitbase<N>& next, const ch_logicbase& enable = '1', const ch_bitbase<N>& init = ch_bitv<N>(0x0)) {
  return ch_bitv<N>(createLatchNode(next, init, enable, ch_reset()));
}

#define CHDL_LATCH_GEN(type) \
  template <unsigned N> ch_bitv<N> ch_latch(type next, const ch_logicbase& enable, const ch_bitbase<N>& init) { return ch_latch(ch_bitv<N>(next), enable, init); } \
  template <unsigned N> ch_bitv<N> ch_latch(const ch_bitbase<N>& next, type enable, const ch_bitbase<N>& init) { return ch_latch(next, ch_logic(enable), init); } \
  template <unsigned N> ch_bitv<N> ch_latch(type next, type enable, const ch_bitbase<N>& init) { return ch_latch(ch_bitv<N>(next), ch_logic(enable), init); } \
  template <unsigned N> ch_bitv<N> ch_latch(type next, const ch_logicbase& enable, type init = 0) { return ch_latch(ch_bitv<N>(next), enable, ch_bitv<N>(init)); } \
  template <unsigned N> ch_bitv<N> ch_latch(const ch_bitbase<N>& next, type enable, type init = 0) { return ch_latch(next, ch_logic(enable), ch_bitv<N>(init)); } \
  template <unsigned N> ch_bitv<N> ch_latch(type next, type enable = 0, type init = 0) { return ch_latch(ch_bitv<N>(next), ch_logic(enable), ch_bitv<N>(init)); }  
CHDL_LATCH_GEN(char)
CHDL_LATCH_GEN(int8_t)
CHDL_LATCH_GEN(uint8_t)
CHDL_LATCH_GEN(int16_t)
CHDL_LATCH_GEN(uint16_t)
CHDL_LATCH_GEN(int32_t)
CHDL_LATCH_GEN(uint32_t)
CHDL_LATCH_GEN(int64_t)
CHDL_LATCH_GEN(uint64_t)
#undef CHDL_LATCH_GEN

}
