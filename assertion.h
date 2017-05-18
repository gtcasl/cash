#pragma once

#include "bit.h"

namespace cash {
namespace detail {

void ch_assert(const ch_logicbase& l, const std::string& msg);

}
}

#ifndef NDEBUG
  #define CH_ASSERT(x) \
      ch_assert(x, fstring("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CH_ASSERT(x)
#endif
