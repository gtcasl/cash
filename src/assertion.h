#pragma once

#include "bit.h"

namespace ch {
namespace internal {

void createAssertNode(const lnode& pred, const std::string& msg);

inline void ch_assert(const bitbase<1>& pred, const std::string& msg) {
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
