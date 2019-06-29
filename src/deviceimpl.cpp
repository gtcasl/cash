#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "bit.h"

using namespace ch::internal;

deviceimpl::deviceimpl(const std::type_index& signature,
                       bool is_pod,
                       const std::string& name)
  : old_ctx_(nullptr)
  , sloc_ctx_(nullptr) {
  auto ret = ctx_create(signature, is_pod, name);
  ctx_ = ret.first;
  is_new_ctx_ = ret.second;
  ctx_->acquire();
}

deviceimpl::~deviceimpl() {
  ctx_->release();  
}

bool deviceimpl::begin() {
  old_ctx_ = ctx_swap(ctx_);
  if (is_new_ctx_) {
    sloc_ctx_ = sloc_begin_module();
  }
  return is_new_ctx_;
}

void deviceimpl::build() {
  if (is_new_ctx_) {
    compiler compiler(ctx_);
    compiler.optimize();
  }
}

void deviceimpl::end() {
  if (is_new_ctx_) {
    sloc_end_module(sloc_ctx_);
  }
  ctx_swap(old_ctx_);
  if (old_ctx_) {
    auto sloc = get_source_location();
    old_ctx_->create_binding(ctx_, sloc);
  }
}

///////////////////////////////////////////////////////////////////////////////

device::device() : impl_(nullptr) {}

device::device(const std::type_index& signature,
               bool is_pod,
               const std::string& name) {
  impl_ = new deviceimpl(signature, is_pod, name);
  impl_->acquire();
}

device::device(const device& other)
  : impl_(other.impl_) {
  if (impl_) {
    impl_->acquire();
  }
}

device::device(device&& other)
  : impl_(std::move(other.impl_)) {
  other.impl_ = nullptr;
}

device::~device() {
  if (impl_) {
    impl_->release();
  }
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

device& device::operator=(device&& other) {
  impl_ = std::move(other.impl_);
  other.impl_ = nullptr;
  return *this;
}

bool device::begin() {
  return impl_->begin();
}

void device::build() {
  impl_->build();
}

void device::end() {
  impl_->end();
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_stats(std::ostream& out, const device& device) {
  device.impl()->ctx()->dump_stats(out);
}
