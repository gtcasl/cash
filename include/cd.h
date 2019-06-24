#pragma once

#include "uint.h"

namespace ch {
namespace internal {

lnodeimpl* getCurrentClockNode();

lnodeimpl* getCurrentResetNode();

void pushClockDomain(const lnode& clock, const lnode& reset, bool pos_edge);

///////////////////////////////////////////////////////////////////////////////

inline auto ch_clock() {
  CH_SOURCE_LOCATION(1);
  return make_logic_type<ch_bool>(getCurrentClockNode());
}

inline auto ch_reset() {
  CH_SOURCE_LOCATION(1);
  return make_logic_type<ch_bool>(getCurrentResetNode());
}

template <typename C, typename R = ch_bool>
void ch_pushcd(const C& clk, const R& reset = ch_reset(), bool pos_edge = true) {
  static_assert(is_bit_base_v<C>, "invalid type");
  static_assert(ch_width_v<C> == 1, "invalid size");
  static_assert(is_bit_base_v<R>, "invalid type");
  static_assert(ch_width_v<R> == 1, "invalid size");
  CH_SOURCE_LOCATION(1);
  pushClockDomain(get_lnode(clk), get_lnode(reset), pos_edge);
}

void ch_popcd();

template <typename Func, typename C, typename R = ch_bool>
void ch_cd(Func&& func,
           const C& clk,
           const R& reset = ch_reset(),
           bool pos_edge = true) {
  CH_SOURCE_LOCATION(1);
  ch_pushcd(clk, reset, pos_edge);
  func;
  ch_popcd();
}

}
}
