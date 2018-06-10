#pragma once

#include "tracer.h"

namespace ch {
namespace internal {

class ch_vcdtracer: public ch_tracer {
public:

  template <typename... Devices>
  ch_vcdtracer(std::ostream& out, const device& device, const Devices&... more)
    : ch_vcdtracer(out, {get_ctx(device), get_ctx(more)...})
  {}

  template <typename... Devices>
  ch_vcdtracer(const std::string& file, const device& device, const Devices&... more) :
    ch_vcdtracer(file, {get_ctx(device), get_ctx(more)...})
  {}

  ch_vcdtracer(std::ostream& out) : ch_vcdtracer(out, {}) {}

  ch_vcdtracer(const std::string& file) : ch_vcdtracer(file, {}) {}

  ~ch_vcdtracer();

protected:

  ch_vcdtracer(std::ostream& out, const std::initializer_list<context*>& contexts);

  ch_vcdtracer(const std::string& file, const std::initializer_list<context*>& contexts);
};

}
}
