#pragma once

#include "device.h"

namespace ch {
namespace internal {

void ch_toVerilog(std::ostream& out, const ch_device_list& devices);

template <typename... Devices>
void ch_toVerilog(std::ostream& out, const device& first, const Devices&... more) {
  ch_toVerilog(out, ch_device_list{first, (more)...});
}

template <typename... Devices>
void ch_toVerilog(const std::string& file, const device& first, const Devices&... more) {
  std::ofstream out(file);
  ch_toVerilog(out, ch_device_list{first, (more)...});
}

}
}
