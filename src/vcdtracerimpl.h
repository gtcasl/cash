#pragma once

#include "tracerimpl.h"

namespace ch {
namespace internal {

class vcdtracerimpl : public tracerimpl {
public:
  vcdtracerimpl(std::ostream& out, const std::initializer_list<context*>& contexts)
    : tracerimpl(out, contexts)
  {}

  vcdtracerimpl(const char* file, const std::initializer_list<context*>& contexts)
    : tracerimpl(file, contexts)
  {}

  ~vcdtracerimpl() {}

  void ensureInitialize() override;

  void tick(ch_tick t) override;
};

}
}
