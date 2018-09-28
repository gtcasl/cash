#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_toVerilog(std::ostream& out, const device& device);

inline void ch_toVerilog(const std::string& file, const device& device) {
  std::ofstream out(file);
  ch_toVerilog(out, device);
}

}
}
