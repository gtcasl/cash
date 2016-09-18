#pragma once

namespace chdl_internal {

template <unsigned N>
ch_bitv<N> ch_reg(const ch_bitbase<N>& next) {
  TODO();
}

template <unsigned N>
ch_bitv<N> ch_reg(const ch_bitbase<N>& next, const ch_bitbase<N>& init) {
  TODO();
}

template <unsigned N>
ch_bitv<N> ch_latch(const ch_bitbase<N>& next, const ch_bitbase<N>& enable, const ch_bitbase<N>& init) {
  TODO();
}

ch_logic ch_clock();
void ch_pushclock(const ch_logic& clk);
void ch_popclock();

ch_logic ch_reset();
void ch_pushreset(const ch_logic& reset);
void ch_popreset();

template <unsigned N>
ch_logic ch_ready(const ch_bitv<N>& x);

template <unsigned N>
ch_logic ch_valid(const ch_bitv<N>& x);

}
