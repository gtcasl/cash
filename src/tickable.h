#pragma once

#include "common.h"

namespace ch {
namespace internal {

class tickable {
public:

  tickable() {}

  virtual ~tickable() {}

  virtual void detach() = 0;

  virtual void tick(ch_tick t) = 0;

  virtual void tick_next(ch_tick t) = 0;
};

}
}
