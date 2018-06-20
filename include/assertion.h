#pragma once

#include "logic.h"

namespace ch {
namespace internal {

void createAssertNode(const lnode& pred,
                      const std::string& msg,
                      const source_location& sloc);

template <typename P>
inline void ch_assert(const ch_logic_base<P>& pred, const std::string& msg, CH_SLOC) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  createAssertNode(get_lnode(pred), msg, sloc);
}

}
}

#ifndef NDEBUG
  #define CH_ASSERT(x) \
      ch_assert(x, stringf("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CH_ASSERT(x)
#endif
