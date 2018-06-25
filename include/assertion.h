#pragma once

#include "bit.h"

namespace ch {
namespace internal {

void createAssertNode(const lnode& pred,
                      const std::string& msg,
                      const source_location& sloc);

inline void ch_assert(const ch_bit<1>& pred, const std::string& msg, CH_SLOC) {
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
