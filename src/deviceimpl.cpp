#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "verilogwriter.h"

using namespace ch::internal;

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
  compiler compiler(ctx_);
  compiler.run();
}

///////////////////////////////////////////////////////////////////////////////

device::device() : impl_(nullptr) {}

device::~device() {
  if (impl_)
    impl_->release();
}

device::device(const device& device) : impl_(device.impl_) {
  impl_->acquire();
}

device& device::operator=(const device& device) {
  if (device.impl_)
    device.impl_->acquire();
  if (impl_)
    impl_->release();
  impl_ = device.impl_;
  return *this;
}

void device::begin_context(const std::string& name) {
  if (nullptr == impl_) {
    impl_ = new deviceimpl(name);
    impl_->acquire();
  }
  impl_->begin_context();
}

void device::end_context() {
  CH_CHECK(impl_ != nullptr, "uninitialized device!");
  impl_->end_context();
}

void device::compile() {
  CH_CHECK(impl_ != nullptr, "uninitialized device!");
  impl_->compile();
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::registerIOMap(const nodelist& data) {
  ctx_curr()->register_io_map(data);
}

lnodeimpl* ch::internal::createInputNode(const std::string& name, uint32_t size) {
  return new inputimpl(ctx_curr(), size, name);
}

lnodeimpl* ch::internal::createOutputNode(const std::string& name, const lnode& src) {
  return new outputimpl(src, name);
}

void ch::internal::bindInput(const lnode& input, const lnode& src) {
  dynamic_cast<inputimpl*>(input.get_impl())->set_input(src);
}

context* ch::internal::get_ctx(const device& device) {
  return device.impl_->get_ctx();
}

void ch::internal::toVerilog(std::ostream& out, const std::initializer_list<const device*>& devices) {
  verilogwriter writer(out);
  for (auto device : devices) {
    writer.print(get_ctx(*device));
  }
}

void ch::internal::ch_dumpStats(std::ostream& out, const device& device) {
  get_ctx(device)->dump_stats(out);
}
