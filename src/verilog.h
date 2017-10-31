#pragma once

#include "device.h"

namespace ch {
namespace internal {

void toVerilog(std::ostream& out, const std::initializer_list<context*>& contexts);

template <typename... Devices>
void ch_toVerilog(std::ostream& out, const device& device, const Devices&... more) {
  toVerilog(out, {get_ctx(device), get_ctx(more)...});
}

template <typename... Devices>
void ch_toVerilog(const std::string& file, const device& device, const Devices&... more) {
  std::ofstream out(file);
  toVerilog(out, {get_ctx(device), get_ctx(more)...});
}

}
}
