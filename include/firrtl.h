#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_toFirrtl(std::ostream& out, const device& device);

inline void ch_toFirrtl(const std::string& file, const device& device) {
  std::ofstream out(file);
  ch_toFirrtl(out, device);
}

}
}
