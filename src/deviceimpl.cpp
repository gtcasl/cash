#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "verilogwriter.h"

using namespace cash::internal;

deviceimpl::deviceimpl(const std::string& name) {
  ctx_ = ctx_create(name);
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

void ch_device::begin_context(const std::string& name) {
  if (nullptr == impl_) {
    impl_ = new deviceimpl(name);
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

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* cash::internal::createInputNode(const std::string& name, uint32_t size) {
  return new inputimpl(ctx_curr(), size, name);
}

lnodeimpl* cash::internal::createOutputNode(const std::string& name, const lnode& src) {
  return new outputimpl(src, name);
}

void cash::internal::bindInput(const lnode& input, const lnode& src) {
  dynamic_cast<inputimpl*>(input.get_impl())->set_input(src);
}

context* cash::internal::get_ctx(const ch_device& device) {
  return device.impl_->get_ctx();
}

void cash::internal::toVerilog(std::ostream& out, const std::initializer_list<const ch_device*>& devices) {
  verilogwriter writer(out);
  for (auto device : devices) {
    writer.print(get_ctx(*device));
  }
}

void cash::internal::ch_dumpStats(std::ostream& out, const ch_device& device) {
  get_ctx(device)->dump_stats(out);
}
