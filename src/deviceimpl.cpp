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
  , sloc_ctx_(nullptr)
  , is_opened_(false) {
  auto ret = ctx_create(signature, is_pod, name);
  ctx_ = ret.first;
  is_new_ctx_ = ret.second;
  ctx_->acquire();
}

deviceimpl::~deviceimpl() {
  if (is_opened_) {
    this->end();
  }
  ctx_->release();  
}

bool deviceimpl::begin() {
  is_opened_ = true;
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
  } else {

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
  is_opened_ = false;
}

///////////////////////////////////////////////////////////////////////////////

device_base::device_base() : impl_(nullptr) {}

device_base::device_base(const std::type_index& signature,
                         bool is_pod,
                         const std::string& name) {
  impl_ = new deviceimpl(signature, is_pod, name);
  impl_->acquire();
}

device_base::device_base(const device_base& other)
  : impl_(other.impl_) {
  if (impl_) {
    impl_->acquire();
  }
}

device_base::device_base(device_base&& other)
  : impl_(std::move(other.impl_)) {
  other.impl_ = nullptr;
}

device_base::~device_base() {
  if (impl_) {
    impl_->release();
  }
}

device_base& device_base::operator=(const device_base& device) {
  if (device.impl_) {
    device.impl_->acquire();
  }
  if (impl_) {
    impl_->release();
  }
  impl_ = device.impl_;
  return *this;
}

device_base& device_base::operator=(device_base&& other) {
  impl_ = std::move(other.impl_);
  other.impl_ = nullptr;
  return *this;
}

bool device_base::begin() {
  return impl_->begin();
}

void device_base::build() {
  impl_->build();
}

void device_base::end() {
  impl_->end();
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_stats(std::ostream& out, const device_base& device) {
  device.impl()->ctx()->dump_stats(out);
}
