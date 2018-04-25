#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "verilogwriter.h"

using namespace ch::internal;

deviceimpl::deviceimpl(size_t signature, const std::string& name) {
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

device::device(size_t signature, const std::string& name) {
  impl_ = new deviceimpl(signature, name);
  impl_->acquire();
  impl_->begin_context();
}

device::~device() {
  impl_->release();
}

void device::compile() {
  impl_->compile();
  impl_->end_context();
}

///////////////////////////////////////////////////////////////////////////////

context* ch::internal::get_ctx(const device& device) {
  return device.impl_->ctx();
}
