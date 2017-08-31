#include "device.h"
#include "context.h"
#include "compile.h"

using namespace cash::internal;

ch_device::~ch_device() {
  ctx_->release();
}

lnodeimpl* ch_device::bind_input_(const snode& bus) const {
  return ctx_->bind_input(bus);
}

snodeimpl* ch_device::bind_output_(const lnode& output) const {
  return ctx_->bind_output(output);
}

snodeimpl* ch_device::get_tap(const std::string& name, uint32_t size) const {
  return ctx_->get_tap(name, size);
}

void ch_device::compile() {
  ch_compiler compiler(ctx_);
  compiler.run();
}

void ch_device::to_verilog(const std::string& module_name, std::ostream& out) {
  ctx_->to_verilog(module_name, out);
}

void ch_device::dump_stats(std::ostream& out) {
  ctx_->dump_stats(out);
}
