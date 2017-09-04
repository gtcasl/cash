#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"

using namespace cash::internal;

void deviceimpl::end_context() {
  {
    ch_compiler compiler(ctx_);
    compiler.run();
  }
  ctx_set(nullptr);
}

///////////////////////////////////////////////////////////////////////////////

ch_device::ch_device() {
  impl_ = new deviceimpl();
}

ch_device::~ch_device() {
  delete impl_;
  impl_ = nullptr;
}

void ch_device::begin_context() {
  impl_->begin_context();
}

void ch_device::end_context() {
  impl_->end_context();
}

lnodeimpl* ch_device::bind_input(const snode& bus) const {
  return impl_->bind_input(bus);
}

snodeimpl* ch_device::bind_output(const lnode& output) const {
  return impl_->bind_output(output);
}

snodeimpl* ch_device::get_tap(const std::string& name, uint32_t size) const {
  return impl_->get_tap(name, size);
}

void ch_device::to_verilog(const std::string& module_name, std::ostream& out) {
  impl_->to_verilog(module_name, out);
}

void ch_device::dump_stats(std::ostream& out) {
  impl_->dump_stats(out);
}
