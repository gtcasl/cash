#pragma once

#include "tracer.h"

namespace ch {
namespace internal {

class ch_vcdtracer: public ch_tracer {
public:
  template <typename... Modules>
  ch_vcdtracer(std::ostream& out, const module& module, const Modules&... more)
    : ch_vcdtracer(out, {get_ctx(module), get_ctx(more)...})
  {}

  template <typename... Modules>
  ch_vcdtracer(const char* file, const module& module, const Modules&... more) :
    ch_vcdtracer(file, {get_ctx(module), get_ctx(more)...})
  {}

  ch_vcdtracer(std::ostream& out) : ch_vcdtracer(out, {}) {}

  ~ch_vcdtracer();

protected:
  ch_vcdtracer(std::ostream& out, const std::initializer_list<context*>& contexts);
  ch_vcdtracer(const char* file, const std::initializer_list<context*>& contexts);
};

}
}
