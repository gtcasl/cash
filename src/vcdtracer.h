#pragma once

#include "tracer.h"

namespace cash {
namespace internal {

class ch_vcdtracer: public ch_tracer {
public:
  template <typename... Devices>
  ch_vcdtracer(std::ostream& out, const ch_device& device, const Devices&... more)
    : ch_vcdtracer(out, {&device, &more...})
  {}

  template <typename... Devices>
  ch_vcdtracer(const std::string& file, const ch_device& device, const Devices&... more) :
    ch_vcdtracer(file, {&device, &more...})
  {}

  ch_vcdtracer(std::ostream& out) : ch_vcdtracer(out, {}) {}

  ~ch_vcdtracer();

protected:
  ch_vcdtracer(std::ostream& out, const std::initializer_list<const ch_device*>& devices);
  ch_vcdtracer(const std::string& file, const std::initializer_list<const ch_device*>& devices);
};

}
}
