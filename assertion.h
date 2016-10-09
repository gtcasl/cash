#pragma once

#include "bitv.h"

namespace chdl_internal {

void ch_assert(const ch_logicbase& l, const std::string& msg);

}

#ifdef CHDL_DEBUG
  #define CHDL_ASSERT(x) \
      ch_assert(x, fstring("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CHDL_ASSERT(x)
#endif
