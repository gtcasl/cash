#pragma once

#include "module.h"

namespace ch {
namespace internal {

void toVerilog(std::ostream& out, const std::initializer_list<context*>& contexts);

template <typename... Modules>
void ch_toVerilog(std::ostream& out, const module& module, const Modules&... more) {
  toVerilog(out, {get_ctx(module), get_ctx(more)...});
}

template <typename... Modules>
void ch_toVerilog(const std::string& file, const module& module, const Modules&... more) {
  std::ofstream out(file);
  toVerilog(out, {get_ctx(module), get_ctx(more)...});
}

}
}
