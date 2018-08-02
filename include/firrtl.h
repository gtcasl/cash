#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_toFIRRTL(std::ostream& out, const device& device);

inline void ch_toFIRRTL(const std::string& file, const device& device) {
  std::ofstream out(file);
  ch_toFIRRTL(out, device);
}

}
}
