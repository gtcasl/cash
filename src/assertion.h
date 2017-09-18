#pragma once

#include "bit.h"

namespace cash {
namespace internal {

void createAssertNode(const lnode& pred, const std::string& msg);

template <typename P,
          CH_REQUIRES(traits<P>::bitcount == 1)>
void ch_assert(const ch_bitbase<P>& pred, const std::string& msg) {
  createAssertNode(get_node(pred), msg);
}

}
}

#ifndef NDEBUG
  #define CH_ASSERT(x) \
      ch_assert(x, fstring("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CH_ASSERT(x)
#endif
