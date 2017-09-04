#pragma once

#include "tracerimpl.h"

namespace cash {
namespace internal {

class vcdtracerimpl : public tracerimpl {
public:
  vcdtracerimpl(std::ostream& out, const std::initializer_list<const ch_device*>& devices)
    : tracerimpl(out, devices)
  {}

  ~vcdtracerimpl() {}

  void ensureInitialize() override;

  void tick(ch_cycle t) override;
};

}
}
