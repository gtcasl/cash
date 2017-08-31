#pragma once

#include "sim.h"

namespace cash {
namespace internal {

class ch_vcdtracer: public ch_tracer {
public:
  template<typename ...Devices>
  ch_vcdtracer(std::ostream& out, const Devices&... devices)
    : ch_vcdtracer(out, {&devices...})
  {}

  ch_vcdtracer(std::ostream& out, const std::initializer_list<const ch_device*>& devices);
  
  void tick(ch_cycle t) override;
  
protected:  

  void ensureInitialize() override;
};

}
}
