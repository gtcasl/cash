#pragma once

#include "uint.h"

namespace ch {
namespace internal {

lnodeimpl* getCurrentClockNode();

lnodeimpl* getCurrentResetNode();

void pushClockDomain(const lnode& clock, const lnode& reset, bool pos_edge);

///////////////////////////////////////////////////////////////////////////////

inline auto ch_clock() {
  CH_API_ENTRY(1);
  return make_logic_type<ch_bool>(getCurrentClockNode());
}

inline auto ch_reset() {
  CH_API_ENTRY(1);
  return make_logic_type<ch_bool>(getCurrentResetNode());
}

template <typename C, typename R = ch_bool>
void ch_pushcd(const C& clk, const R& reset = ch_reset(), bool pos_edge = true) {
  CH_API_ENTRY(1);
  static_assert(is_bitbase_v<C>, "invalid type");
  static_assert(ch_width_v<C> == 1, "invalid size");
  static_assert(is_bitbase_v<R>, "invalid type");
  static_assert(ch_width_v<R> == 1, "invalid size");
  pushClockDomain(get_lnode(clk), get_lnode(reset), pos_edge);
}

void ch_popcd();

template <typename Func, typename C, typename R = ch_bool>
void ch_cd(Func&& func,
           const C& clk,
           const R& reset = ch_reset(),
           bool pos_edge = true) {
  CH_API_ENTRY(1);
  ch_pushcd(clk, reset, pos_edge);
  func;
  ch_popcd();
}

}
}
