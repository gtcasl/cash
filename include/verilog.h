#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_verilog(std::ostream& out, const ch_device_list& devices);

template <typename... Devices>
void ch_verilog(std::ostream& out, const device& first, const Devices&... more) {
  ch_verilog(out, ch_device_list{first, (more)...});
}

template <typename... Devices>
void ch_verilog(const std::string& file, const device& first, const Devices&... more) {
  std::ofstream out(file);
  ch_verilog(out, ch_device_list{first, (more)...});
}

}
}
