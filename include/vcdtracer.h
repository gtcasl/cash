#pragma once

#include "tracer.h"

namespace ch {
namespace internal {

class ch_vcdtracer: public ch_tracer {
public:

  ch_vcdtracer() {}

  ch_vcdtracer(std::ostream& out, const ch_device_list& devices);

  ch_vcdtracer(const std::string& file, const ch_device_list& devices);

  template <typename... Devices>
  ch_vcdtracer(std::ostream& out, const device& first, const Devices&... more)
    : ch_vcdtracer(out, ch_device_list{first, (more)...})
  {}

  template <typename... Devices>
  ch_vcdtracer(const std::string& file, const device& first, const Devices&... more)
    : ch_vcdtracer(file, ch_device_list{first, (more)...})
  {}

  ch_vcdtracer(const ch_vcdtracer& tracer);

  ch_vcdtracer(ch_vcdtracer&& tracer);

  ~ch_vcdtracer();

  ch_vcdtracer& operator=(const ch_vcdtracer& tracer);

  ch_vcdtracer& operator=(ch_vcdtracer&& tracer);
};

}
}
