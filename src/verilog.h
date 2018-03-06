#pragma once

#include "device.h"

namespace ch {
namespace internal {

void toVerilog(std::ostream& out, context* ctx);

inline void ch_toVerilog(std::ostream& out, const device& device) {
  toVerilog(out, get_ctx(device));
}

inline void ch_toVerilog(const std::string& file, const device& device) {
  std::ofstream out(file);
  toVerilog(out, get_ctx(device));
}

}
}
