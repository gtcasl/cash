#include "deviceimpl.h"
#include "device.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "bit.h"

using namespace ch::internal;

deviceimpl::deviceimpl(const std::type_index& signature,
                       bool has_args,
                       const std::string& name) {
  ctx_ = ctx_create(signature, has_args, name);
  ctx_->acquire();
  is_new_ctx_ = (0 == ctx_->nodes().size());
}

deviceimpl::~deviceimpl() {
  ctx_->release();  
}

void deviceimpl::begin_context() {
  old_ctx_ = ctx_swap(ctx_);
}

void deviceimpl::end_context() {
  ctx_swap(old_ctx_);
  if (old_ctx_) {
    auto sloc = get_source_location();
    old_ctx_->create_binding(ctx_, sloc);
  }
}

bool deviceimpl::begin_build() const {
  return is_new_ctx_;
}

void deviceimpl::end_build() {
  if (is_new_ctx_) {
    compiler compiler(ctx_);
    if (0 == (platform::self().cflags() & cflags::no_smod_opt)) {
      compiler.optimize();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

device::device() : impl_(nullptr) {}

device::device(const std::type_index& signature,
               bool has_args,
               const std::string& name) {
  impl_ = new deviceimpl(signature, has_args, name);
  impl_->acquire();
  impl_->begin_context();
}

device::device(const device& other) : impl_(other.impl_) {
  if (impl_) {
    impl_->acquire();
  }
}

device::device(device&& other) : impl_(std::move(other.impl_)) {
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

bool device::begin_build() const {
  return impl_->begin_build();
}

void device::end_build() {
  impl_->end_build();
  impl_->end_context();
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_stats(std::ostream& out, const device& device) {
  device.impl()->ctx()->dump_stats(out);
}
