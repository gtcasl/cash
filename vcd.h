#pragma once

#include <fstream>
#include "sim.h"

namespace chdl_internal {

class ch_vcdtracer: public ch_simulator {
public:
  ch_vcdtracer(const std::string& filename);
  ~ch_vcdtracer();
  
  void tick(ch_cycle t);
  
  void close();
  
protected:  

  virtual void ensureInitialize();

  std::ofstream m_file;

};

}
