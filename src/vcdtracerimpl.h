#pragma once

#include "tracerimpl.h"

namespace ch {
namespace internal {

class vcdtracerimpl : public tracerimpl {
public:

  vcdtracerimpl(std::ostream& out, const ch_device_list& devices)
    : tracerimpl(out, devices)
  {}

  vcdtracerimpl(const std::string& file, const ch_device_list& devices)
    : tracerimpl(file, devices)
  {}

  ~vcdtracerimpl() {}

protected:

  void initialize() override;

  void eval(ch_tick t) override;
};

}
}
