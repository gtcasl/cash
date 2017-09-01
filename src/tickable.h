#pragma once

#include "common.h"

namespace cash {
namespace internal {

class tickable {
public:
  tickable() {}
  ~tickable() {}

  virtual void tick(ch_cycle) = 0;
  virtual void tick_next(ch_cycle) = 0; 
};

}
}
