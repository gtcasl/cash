#include "device.h"
#include "deviceimpl.h"
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
  instance_ = ret.second;
  ctx_->acquire();
}

deviceimpl::~deviceimpl() {
  if (is_opened_) {
    this->end();
  }
  ctx_->release();  
}

std::string deviceimpl::name() const {
  if (ctx_)
    return ctx_->name();
  return "";
}

bool deviceimpl::begin() {
  is_opened_ = true;
  old_ctx_ = ctx_swap(ctx_);
  sloc_ctx_ = sloc_begin_module();
  return (instance_ != 0);
}

void deviceimpl::begin_build() {
  ctx_->set_initialized();
}

void deviceimpl::end_build() {
 compiler compiler(ctx_);
 compiler.optimize();
}

void deviceimpl::end() {
  sloc_end_module(sloc_ctx_);
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

std::string device_base::name() const {
  if (impl_) {
    return impl_->name();
  }
  return "";
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

void device_base::begin_build() {
  impl_->begin_build();
}

void device_base::end_build() {
  impl_->end_build();
}

void device_base::end() {
  impl_->end();
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_stats(std::ostream& out, const device_base& device) {
  device.impl()->ctx()->dump_stats(out);
}
