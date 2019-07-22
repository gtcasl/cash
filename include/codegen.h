#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_toVerilog(std::ostream& out, const device_base& device);

inline void ch_toVerilog(const std::string& file, const device_base& device) {
  std::ofstream out(file);
  ch_toVerilog(out, device);
}

///////////////////////////////////////////////////////////////////////////////

void ch_toFIRRTL(std::ostream& out, const device_base& device);

inline void ch_toFIRRTL(const std::string& file, const device_base& device) {
  std::ofstream out(file);
  ch_toFIRRTL(out, device);
}

}
}
