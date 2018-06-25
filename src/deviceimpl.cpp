#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "verilogwriter.h"

using namespace ch::internal;

deviceimpl::deviceimpl(const std::type_index& signature, const std::string& name) {
  ctx_ = ctx_create(signature, name);
  ctx_->acquire();
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

device::device(const std::type_index& signature, const std::string& name) {
  impl_ = new deviceimpl(signature, name);
  impl_->acquire();
  impl_->begin_context();
}

device::device(const device& rhs) : impl_(rhs.impl_) {
  if (impl_) {
    impl_->acquire();
  }
}

device::device(device&& rhs) : impl_(std::move(rhs.impl_)) {}

device::~device() {
  if (impl_)
    impl_->release();
}

device& device::operator=(const device& device) {
  if (device.impl_) {
    device.impl_->acquire();
  }
  if (impl_) {
    impl_->release();
  }
  impl_ = device.impl_;
  return *this;
}

device& device::operator=(device&& rhs) {
  impl_ = std::move(rhs.impl_);
  return *this;
}

void device::compile() {
  impl_->compile();
  impl_->end_context();
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_stats(std::ostream& out, const device& device) {
  device.impl()->ctx()->dump_stats(out);
}
