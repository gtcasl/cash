#pragma once

#include "bit.h"

namespace ch {
namespace internal {

void ch_assert(const ch_bit<1>& cond, const std::string& msg);

}
}

#ifndef NDEBUG
  #define CH_ASSERT(x) \
      ch_assert(x, stringf("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CH_ASSERT(x)
#endif
