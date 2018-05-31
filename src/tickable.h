#pragma once

#include "common.h"

namespace ch {
namespace internal {

class tickable {
public:

  tickable() {}
  virtual ~tickable() {}

  virtual void tick() = 0;
};

}
}
