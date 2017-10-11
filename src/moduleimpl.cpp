#include "moduleimpl.h"
#include "module.h"
#include "context.h"
#include "compile.h"
#include "ioimpl.h"
#include "verilogwriter.h"

using namespace ch::internal;

moduleimpl::moduleimpl(size_t signature, const char* name) {
  ctx_ = ctx_create(signature, name);
  ctx_->acquire();
}

moduleimpl::~moduleimpl() {
  ctx_->release();
}

void moduleimpl::begin_context() {
  old_ctx_ = ctx_swap(ctx_);
}

void moduleimpl::end_context() {
  ctx_swap(old_ctx_);
}

void moduleimpl::compile() {
  compiler compiler(ctx_);
  compiler.run();
}

///////////////////////////////////////////////////////////////////////////////

module::module(size_t signature, const char* name) {
  impl_ = new moduleimpl(signature, name);
  impl_->acquire();
  impl_->begin_context();
}

module::~module() {
  impl_->release();
}

void module::end_context() {
  impl_->compile();
  impl_->end_context();
}

///////////////////////////////////////////////////////////////////////////////

context* ch::internal::get_ctx(const module& module) {
  return module.impl_->get_ctx();
}
