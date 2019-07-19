#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_toVerilog(std::ostream& out, const device& device);

void ch_toVerilog(std::ostream& out, const ch_device_list& devices);

inline void ch_toVerilog(const std::string& file, const device& device) {
  std::ofstream out(file);
  ch_toVerilog(out, device);
}

inline void ch_toVerilog(const std::string& file, const ch_device_list& devices) {
  std::ofstream out(file);
  ch_toVerilog(out, devices);
}

///////////////////////////////////////////////////////////////////////////////

void ch_toFIRRTL(std::ostream& out, const device& device);

void ch_toFIRRTL(std::ostream& out, const ch_device_list& devices);

inline void ch_toFIRRTL(const std::string& file, const device& device) {
  std::ofstream out(file);
  ch_toFIRRTL(out, device);
}

}
}
