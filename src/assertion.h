#pragma once

#include "logic.h"

namespace ch {
namespace internal {

void createAssertNode(const lnode& pred, const std::string& msg);

template <typename P,
          CH_REQUIRE_0(is_logic_compatible<P>::value)>
inline void ch_assert(const P& pred, const std::string& msg) {
  static_assert(1 == width_v<P>, "invalid predicate size");
  createAssertNode(get_lnode(pred), msg);
}

}
}

#ifndef NDEBUG
  #define CH_ASSERT(x) \
      ch_assert(x, fstring("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CH_ASSERT(x)
#endif
