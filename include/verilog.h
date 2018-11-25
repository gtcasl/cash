#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_toVerilog(std::ostream& out, const device& device, bool flatten = false);

inline void ch_toVerilog(const std::string& file,
                         const device& device,
                         bool flatten = false) {
  std::ofstream out(file);
  ch_toVerilog(out, device, flatten);
}

}
}
