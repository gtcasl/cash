#pragma once

#include "sim.h"

namespace chdl_internal {

class ch_vcdtracer: public ch_tracer {
public:
  template<typename ...Devices>
  ch_vcdtracer(const std::string& filename, const Devices&... devices) : ch_vcdtracer(filename, {&devices...}) {}
  ch_vcdtracer(const std::string& filename, const std::initializer_list<const ch_device*>& devices);
  
  void tick(ch_cycle t);
  
protected:  

  void ensureInitialize() override;

  std::ofstream m_file;

};

}
