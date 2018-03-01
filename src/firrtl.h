#pragma once

#include "device.h"

namespace ch {
namespace internal {

void toFIRRTL(std::ostream& out, context* ctx);

inline void ch_toFIRRTL(std::ostream& out, const device& device) {
  toFIRRTL(out, get_ctx(device));
}

inline void ch_toFIRRTL(const std::string& file, const device& device) {
  std::ofstream out(file);
  toFIRRTL(out, get_ctx(device));
}

}
}
