#pragma once

#include "bool.h"

namespace ch {
namespace internal {

lnodeimpl* getCurrentClockNode(const source_info& sloc);

lnodeimpl* getCurrentResetNode(const source_info& sloc);

void pushClockDomain(const lnode& clock, 
                     const lnode& reset, 
                     bool pos_edge,
                     const source_info& sloc);

///////////////////////////////////////////////////////////////////////////////

inline auto ch_clock(CH_SLOC) {
  return make_logic_type<ch_bool>(getCurrentClockNode(sloc));
}

inline auto ch_reset(CH_SLOC) {
  return make_logic_type<ch_bool>(getCurrentResetNode(sloc));
}

template <typename C, typename R = ch_bool>
void ch_pushcd(const C& clk, const R& reset = ch_reset(), bool pos_edge = true, CH_SLOC) {
  static_assert(is_bitbase_v<C>, "invalid type");
  static_assert(ch_width_v<C> == 1, "invalid size");
  static_assert(is_bitbase_v<R>, "invalid type");
  static_assert(ch_width_v<R> == 1, "invalid size");
  pushClockDomain(get_lnode(clk), get_lnode(reset), pos_edge, sloc);
}

void ch_popcd();

template <typename Func, typename C, typename R = ch_bool>
void ch_cd(Func&& func,
           const C& clk,
           const R& reset = ch_reset(),
           bool pos_edge = true,
           CH_SLOC) {
  ch_pushcd(clk, reset, pos_edge, sloc);
  func;
  ch_popcd();
}

}
}
