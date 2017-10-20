#pragma once

#include "bit.h"

namespace ch {
namespace internal {

void createAssertNode(const lnode& pred, const std::string& msg);

template <typename P, CH_REQUIRES(is_bit_convertible<P>::value)>
inline void ch_assert(const P& pred, const std::string& msg) {
  static_assert(P::bitsize == 1, "invalid predicate size");
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
