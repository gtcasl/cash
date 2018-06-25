#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_firrtl(std::ostream& out, const device& device);

inline void ch_firrtl(const std::string& file, const device& device) {
  std::ofstream out(file);
  ch_firrtl(out, device);
}

}
}
