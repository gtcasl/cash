#pragma once

#include "tracerimpl.h"

namespace ch {
namespace internal {

class vcdtracerimpl : public tracerimpl {
public:
  vcdtracerimpl(std::ostream& out, const std::initializer_list<const device*>& devices)
    : tracerimpl(out, devices)
  {}

  vcdtracerimpl(const std::string& file, const std::initializer_list<const device*>& devices)
    : tracerimpl(file, devices)
  {}

  ~vcdtracerimpl() {}

  void ensureInitialize() override;

  void tick(ch_tick t) override;
};

}
}
