#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"

using namespace cash::internal;

deviceimpl::deviceimpl() {
  ctx_ = ctx_create();
}

deviceimpl::~deviceimpl() {
  ctx_->release();
}

void deviceimpl::begin_context() {
  old_ctx_ = ctx_swap(ctx_);
}

void deviceimpl::end_context() {
  ctx_swap(old_ctx_);
}

void deviceimpl::compile() {
  ch_compiler compiler(ctx_);
  compiler.run();
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

void ch_device::compile() {
  impl_->compile();
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
