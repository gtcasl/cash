#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "verilogwriter.h"

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

snodeimpl* deviceimpl::get_tap(const std::string& name, uint32_t size) const {
  return ctx_->get_tap(name, size);
}

void deviceimpl::to_verilog(const std::string& module_name, std::ostream& out) {
  verilogwriter writer(out);
  writer.print(ctx_, module_name);
}

void deviceimpl::dump_stats(std::ostream& out) {
  ctx_->dump_stats(out);
}

///////////////////////////////////////////////////////////////////////////////

ch_device::ch_device() : impl_(nullptr) {}

ch_device::~ch_device() {
  if (impl_)
    impl_->release();
}

ch_device::ch_device(const ch_device& device) : impl_(device.impl_) {
  impl_->acquire();
}

ch_device& ch_device::operator=(const ch_device& device) {
  if (device.impl_)
    device.impl_->acquire();
  if (impl_)
    impl_->release();
  impl_ = device.impl_;
  return *this;
}

void ch_device::begin_context() {
  if (nullptr == impl_) {
    impl_ = new deviceimpl();
    impl_->acquire();
  }
  impl_->begin_context();
}

void ch_device::end_context() {
  CH_CHECK(impl_ != nullptr, "uninitialized device!");
  impl_->end_context();
}

void ch_device::compile() {
  CH_CHECK(impl_ != nullptr, "uninitialized device!");
  impl_->compile();
}

snodeimpl* ch_device::get_tap(const std::string& name, uint32_t size) const {
  CH_CHECK(impl_ != nullptr, "uninitialized device!");
  return impl_->get_tap(name, size);
}

void ch_device::to_verilog(const std::string& module_name, std::ostream& out) {
  CH_CHECK(impl_ != nullptr, "uninitialized device!");
  impl_->to_verilog(module_name, out);
}

void ch_device::dump_stats(std::ostream& out) {
  CH_CHECK(impl_ != nullptr, "uninitialized device!");
  impl_->dump_stats(out);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* cash::internal::createInputNode(const snode& in) {
  return new inputimpl(ctx_curr(), in);
}

snodeimpl* cash::internal::createOutputNode(const lnode& out) {
  outputimpl* impl = new outputimpl(out);
  return impl->get_bus().get_impl();
}
