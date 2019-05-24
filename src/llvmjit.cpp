#include "llvmjit.h"
#include "common.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#pragma GCC diagnostic pop

class _jit_type : public ch::internal::refcounted {
public:
  _jit_type()
    : kind_(JIT_TYPE_INVALID)
    , impl_(nullptr)
  {}

  _jit_type(const _jit_type& other)
   : kind_(other.kind_)
   , impl_(other.impl_)
  {}

  void init(int kind, llvm::Type* impl) {
    kind_ = kind;
    impl_ = impl;
  }

  auto kind() const {
    return kind_;
  }

  auto impl() const {
    return impl_;
  }

protected:
  int kind_;
  llvm::Type* impl_;
};

_jit_type jit_type_void_def;
_jit_type jit_type_int8_def;
_jit_type jit_type_int16_def;
_jit_type jit_type_int32_def;
_jit_type jit_type_int64_def;
_jit_type jit_type_ptr_def;

const jit_type_t jit_type_void  = &jit_type_void_def;
const jit_type_t jit_type_int8  = &jit_type_int8_def;
const jit_type_t jit_type_int16 = &jit_type_int16_def;
const jit_type_t jit_type_int32 = &jit_type_int32_def;
const jit_type_t jit_type_int64 = &jit_type_int64_def;
const jit_type_t jit_type_ptr   = &jit_type_ptr_def;

///////////////////////////////////////////////////////////////////////////////

class _jit_signature : public _jit_type {
public:
  _jit_signature(jit_type_t return_type,
                 jit_type_t* params,
                 unsigned int num_params)
    : _jit_type(*return_type)
    , params_(num_params) {
    for (unsigned int i = 0; i < num_params; ++i) {
      params_[i] = params[i];
    }
  }

  const auto& params() const {
    return params_;
  }

private:
  std::vector<jit_type_t> params_;
};

///////////////////////////////////////////////////////////////////////////////

class _jit_value {
public:
  _jit_value(llvm::Value* impl)
    : impl_(impl)
  {}

  auto impl() const {
    return impl_;
  }

private:
  llvm::Value* impl_;
};

///////////////////////////////////////////////////////////////////////////////

class _jit_block {
public:
  _jit_block(_jit_function* func, llvm::BasicBlock* impl)
    : func_(func)
    , impl_(impl)
  {}

  auto func() const {
    return func_;
  }

  auto impl() const {
    return impl_;
  }

private:
  _jit_function* func_;
  llvm::BasicBlock* impl_;
};

///////////////////////////////////////////////////////////////////////////////

class _jit_function {
public:
  _jit_function(_jit_context* ctx,
                llvm::Function* impl)
    : ctx_(ctx)
    , impl_(impl)
    , params_(impl->arg_size()) {
    int i = 0;
    for (auto& arg : impl->args()) {
      params_[i] = std::make_unique<_jit_value>(&arg);
      ++i;
    }
  }

  auto ctx() const {
    return ctx_;
  }

  auto impl() const {
    return impl_;
  }

  auto get_param(unsigned int param) const {
    return params_[param].get();
  }

  auto create_value(llvm::Value* value) {
    variables_.push_back(std::make_unique<_jit_value>(value));
    return variables_.back().get();
  }

private:
  _jit_context* ctx_;
  llvm::Function* impl_;
  std::vector<std::unique_ptr<_jit_value>> params_;
  std::vector<std::unique_ptr<_jit_value>> variables_;
};

///////////////////////////////////////////////////////////////////////////////

class _jit_context {
public:

  _jit_context(const llvm::orc::JITTargetMachineBuilder& JTMB,
               llvm::TargetMachine* TM,
               const llvm::DataLayout& DL)
    : thread_context_(llvm::make_unique<llvm::LLVMContext>())
    , context_(thread_context_.getContext())
    , builder_(*context_)
    , object_layer_(ex_session_, []() { return llvm::make_unique<llvm::SectionMemoryManager>(); })
    , compile_layer_(ex_session_, object_layer_, llvm::orc::ConcurrentIRCompiler(JTMB))
    , mangle_(ex_session_, DL)
    , target_(TM) {
    //--
    ex_session_.getMainJITDylib().setGenerator(
      llvm::cantFail(llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess(DL)));

    //--
    module_ = std::make_unique<llvm::Module>("llvmjit", *context_);
    module_->setDataLayout(DL);

    //--
    jit_type_void_def.init(JIT_TYPE_VOID, llvm::Type::getVoidTy(*context_));
    jit_type_int8_def.init(JIT_TYPE_INT8, llvm::Type::getInt8Ty(*context_));
    jit_type_int16_def.init(JIT_TYPE_INT16, llvm::Type::getInt16Ty(*context_));
    jit_type_int32_def.init(JIT_TYPE_INT32, llvm::Type::getInt32Ty(*context_));
    jit_type_int64_def.init(JIT_TYPE_INT64, llvm::Type::getInt64Ty(*context_));
    jit_type_ptr_def.init(JIT_TYPE_PTR, llvm::Type::getInt8PtrTy(*context_));
  }

  ~_jit_context() {}

  auto impl() const {
    return context_;
  }

  auto target() const {
    return target_.get();
  }

  auto module() const {
    return module_.get();
  }

  auto builder() {
    return &builder_;
  }

  int compile(llvm::Function* func) {
    {
      static llvm::raw_os_ostream os(std::cerr);
      llvm::verifyFunction(*func, &os);
    }
    {
      llvm::PassManagerBuilder pmb;
      pmb.OptLevel = 3;
      pmb.SizeLevel = 0;
      pmb.LoopVectorize = true;
      pmb.SLPVectorize = true;

      llvm::legacy::FunctionPassManager fpm(module_.get());
      llvm::legacy::PassManager pm;
      pmb.populateFunctionPassManager(fpm);
      pmb.populateModulePassManager(pm);
      fpm.doInitialization();
      fpm.run(*func);
      pm.run(*module_);
    }
    return 0;
  }

  void* closure(const std::string& name) {
    auto err = compile_layer_.add(
          ex_session_.getMainJITDylib(),
          llvm::orc::ThreadSafeModule(std::move(module_), thread_context_));
    if (err)
      return nullptr;
    auto ret = ex_session_.lookup(
      {&ex_session_.getMainJITDylib()}, mangle_(name));
    if (!ret)
      return nullptr;
    return (void*)ret->getAddress();
  }

private:

  llvm::orc::ExecutionSession ex_session_;
  llvm::orc::ThreadSafeContext thread_context_;
  llvm::LLVMContext* context_;
  llvm::IRBuilder<> builder_;
  llvm::orc::RTDyldObjectLinkingLayer object_layer_;
  llvm::orc::IRCompileLayer compile_layer_;
  llvm::orc::MangleAndInterner mangle_;
  std::unique_ptr<llvm::TargetMachine> target_;
  std::unique_ptr<llvm::Module> module_;
};

///////////////////////////////////////////////////////////////////////////////

jit_context_t jit_context_create() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  auto JTMB = llvm::orc::JITTargetMachineBuilder::detectHost();
  if (!JTMB) {
    std::cerr << "JITTargetMachineBuilder::detectHost() failed" << std::endl;
    return nullptr;
  }

  auto TM = JTMB->createTargetMachine();
  if (!TM) {
    std::cerr << "JITTargetMachineBuilder::createTargetMachine() failed" << std::endl;
    return nullptr;
  }

  auto DL = (*TM)->createDataLayout();

  return new _jit_context(*JTMB, TM->release(), DL);
}

void jit_context_destroy(jit_context_t context) {
  delete context;
}

void jit_context_build_start(jit_context_t context) {
  CH_UNUSED(context);
}

void jit_context_build_end(jit_context_t context) {
  CH_UNUSED(context);
}

///////////////////////////////////////////////////////////////////////////////

jit_function_t jit_function_create(jit_context_t context, jit_type_t signature) {
  auto j_sig = reinterpret_cast<_jit_signature*>(signature);
  std::vector<llvm::Type*> args(j_sig->params().size());
  for (unsigned i = 0; i < j_sig->params().size(); ++i) {
    args[i] = j_sig->params()[i]->impl();
  }
  auto sig = llvm::FunctionType::get(j_sig->impl(), args, false);
  auto func = llvm::Function::Create(sig,
                                     llvm::Function::ExternalLinkage,
                                     "eval",
                                     context->module());
  auto bb = llvm::BasicBlock::Create(*context->impl(), "entry", func);
  context->builder()->SetInsertPoint(bb);
  return new _jit_function(context, func);
}

int jit_function_compile(jit_function_t func) {
  auto ctx = func->ctx();
  return ctx->compile(func->impl());
}

void *jit_function_to_closure(jit_function_t func) {
  auto ctx = func->ctx();
  return ctx->closure("eval");
}

jit_block_t jit_function_get_current(jit_function_t func) {
  CH_UNUSED(func);
  CH_TODO();
  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

jit_type_t jit_type_create_signature(jit_abi_t abi,
                                     jit_type_t return_type,
                                     jit_type_t *params,
                                     unsigned int num_params,
                                     int incref) {
  CH_UNUSED(abi, incref);
  auto sig = new _jit_signature(return_type, params, num_params);
  sig->acquire();
  return sig;
}

void jit_type_free(jit_type_t type) {
  type->release();
}

int jit_type_get_kind(jit_type_t type) {
  return type->kind();
}

jit_nuint jit_type_get_size(jit_type_t type) {
  switch (type->kind()) {
  case JIT_TYPE_VOID:
    return 0;
  case JIT_TYPE_INT8:
    return 1;
  case JIT_TYPE_INT16:
    return 2;
  case JIT_TYPE_INT32:
    return 4;
  case JIT_TYPE_INT64:
    return 8;
  case JIT_TYPE_PTR:
    return 8;
  default:
    assert(false);
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////

jit_value_t jit_value_create(jit_function_t func, jit_type_t type) {
  CH_UNUSED(func, type);
  CH_TODO();
  return nullptr;
}

jit_type_t jit_value_get_type(jit_value_t value) {
  auto type = value->impl()->getType();
  switch (type->getTypeID()) {
  case llvm::Type::VoidTyID:
    return jit_type_void;
  case llvm::Type::PointerTyID:
    return jit_type_ptr;
  case llvm::Type::IntegerTyID:
    switch (llvm::cast<llvm::IntegerType>(type)->getBitWidth()) {
    case 8:
      return jit_type_int8;
    case 16:
      return jit_type_int16;
    case 32:
      return jit_type_int32;
    case 64:
      return jit_type_int64;
    default:
      assert(false);
      return nullptr;
    }
  default:
    assert(false);
    return nullptr;
  }
}

jit_value_t jit_value_get_param(jit_function_t func, unsigned int param) {
  return func->get_param(param);
}

jit_value_t jit_value_create_int_constant(jit_function_t func,
                                      jit_type_t type,
                                      jit_long const_value) {
  auto builder = func->ctx()->builder();
  switch (type->kind()) {
  case JIT_TYPE_INT8:
    return func->create_value(builder->getInt8(const_value));
  case JIT_TYPE_INT16:
    return func->create_value(builder->getInt16(const_value));
  case JIT_TYPE_INT32:
    return func->create_value(builder->getInt32(const_value));
  case JIT_TYPE_INT64:
    return func->create_value(builder->getInt64(const_value));
  case JIT_TYPE_PTR:
    return func->create_value(builder->getInt64(const_value));
  default:
    assert(false);
  }
  return nullptr;
}

jit_long jit_value_get_int_constant(jit_value_t value) {
  auto const_value = llvm::dyn_cast<llvm::ConstantInt>(value->impl());
  return const_value->getSExtValue();
}

int jit_value_is_constant(jit_value_t value) {
  return (llvm::dyn_cast<llvm::ConstantInt>(value->impl()) != nullptr);
}

///////////////////////////////////////////////////////////////////////////////

jit_value_t jit_insn_add(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateAdd(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_sub(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateSub(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_mul(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateMul(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_sdiv(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateSDiv(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_udiv(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateUDiv(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_srem(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateSRem(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_urem(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateURem(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_neg(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateNeg(value->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_and(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateAnd(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_or(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateOr(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_xor(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateXor(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_not(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateNot(value->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_shl(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateShl(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_shr(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateAShr(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_ushr(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto res = builder->CreateLShr(value1->impl(), value2->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_eq(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_ne(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_lt(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_le(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_gt(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_ge(jit_function_t func, jit_value_t value1, jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_to_bool(jit_function_t func, jit_value_t value1) {
  CH_UNUSED(func, value1);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_to_not_bool(jit_function_t func, jit_value_t value1) {
  CH_UNUSED(func, value1);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_abs(jit_function_t func, jit_value_t value1) {
  CH_UNUSED(func, value1);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_min(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

jit_value_t jit_insn_max(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  CH_UNUSED(func, value1, value2);
  CH_TODO();
  return nullptr;
}

int jit_insn_store(jit_function_t func, jit_value_t dest, jit_value_t value) {
  CH_UNUSED(func, dest, value);
  CH_TODO();
  return 0;
}

jit_value_t jit_insn_load_relative(jit_function_t func,
                                   jit_value_t base_addr,
                                   jit_nint offset,
                                   jit_type_t type) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto addr  = base_addr->impl();
  if (offset) {
    addr = builder->CreateInBoundsGEP(jit_type_int8->impl(),
                                      addr,
                                      builder->getInt32(offset));
  }
  auto value = builder->CreateLoad(type->impl(), addr);
  return func->create_value(value);
}

int jit_insn_store_relative(jit_function_t func,
                            jit_value_t base_addr,
                            jit_nint offset,
                            jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto addr = base_addr->impl();
  if (offset) {
    addr = builder->CreateInBoundsGEP(jit_type_int8->impl(),
                                      addr,
                                      builder->getInt32(offset));
  }
  auto inst = builder->CreateStore(value->impl(), addr);
  return (inst != nullptr);
}

jit_value_t jit_insn_add_relative(jit_function_t func,
                                  jit_value_t base_addr,
                                  jit_nint offset) {
  assert(jit_type_ptr == jit_value_get_type(base_addr));
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto addr = builder->CreateInBoundsGEP(jit_type_int8->impl(),
                                         base_addr->impl(),
                                         builder->getInt32(offset));
  return func->create_value(addr);
}

jit_value_t jit_insn_load_elem(jit_function_t func,
                               jit_value_t base_addr,
                               jit_value_t index,
                               jit_type_t elem_type) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto addr = builder->CreateInBoundsGEP(elem_type->impl(),
                                         base_addr->impl(),
                                         index->impl());
  auto value = builder->CreateLoad(elem_type->impl(), addr);
  return func->create_value(value);
}

jit_value_t jit_insn_load_elem_address(jit_function_t func,
                                       jit_value_t base_addr,
                                       jit_value_t index,
                                       jit_type_t elem_type) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto value = builder->CreateInBoundsGEP(elem_type->impl(),
                                          base_addr->impl(),
                                          index->impl());
  return func->create_value(value);
}

int jit_insn_store_elem(jit_function_t func,
                        jit_value_t base_addr,
                        jit_value_t index,
                        jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto elem_type = jit_value_get_type(value);
  auto addr = builder->CreateInBoundsGEP(elem_type->impl(),
                                         base_addr->impl(),
                                         index->impl());
  auto inst = builder->CreateStore(value->impl(), addr);
  return (inst != nullptr);
}

jit_value_t jit_insn_address_of(jit_function_t func, jit_value_t value) {
  CH_UNUSED(func, value);
  CH_TODO();
  return nullptr;
}

void jit_insn_set_marker(jit_function_t func, const char* name) {
  CH_UNUSED(func, name);
}

int jit_insn_branch(jit_function_t func, jit_label_t *label) {
  CH_UNUSED(func, label);
  CH_TODO();
  return 0;
}

int jit_insn_branch_if(jit_function_t func,
                       jit_value_t value,
                       jit_label_t *label) {
  CH_UNUSED(func, value, label);
  CH_TODO();
  return 0;
}

int jit_insn_branch_if_not(jit_function_t func,
                           jit_value_t value,
                           jit_label_t *label) {
  CH_UNUSED(func, value, label);
  CH_TODO();
  return 0;
}

int jit_insn_label(jit_function_t func, jit_label_t *label) {
  CH_UNUSED(func, label);
  CH_TODO();
  return 0;
}

int jit_insn_label_tight(jit_function_t func, jit_label_t *label) {
  CH_UNUSED(func, label);
  CH_TODO();
  return 0;
}

int jit_insn_new_block(jit_function_t func) {
  CH_UNUSED(func);
  CH_TODO();
  return 0;
}

int jit_insn_return(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  builder->CreateRet(value->impl());
  return 1;
}

int jit_insn_move_blocks_to_end(jit_function_t func,
                                jit_label_t from_label,
                                jit_label_t to_label) {
  CH_UNUSED(func, from_label, to_label);
  CH_TODO();
  return 0;
}

int jit_insn_memcpy(jit_function_t func,
                    jit_value_t dest,
                    jit_value_t src,
                    jit_value_t size) {
  CH_UNUSED(func, dest, src, size);
  CH_TODO();
  return 0;
}

int jit_insn_jump_table(jit_function_t func,
                        jit_value_t value,
                        jit_label_t *labels,
                        unsigned int num_labels) {
  CH_UNUSED(func, value, labels, num_labels);
  CH_TODO();
  return 0;
}

jit_value_t jit_insn_call_native(jit_function_t func,
                                 const char *name,
                                 void *native_func,
                                 jit_type_t signature,
                                 jit_value_t *args,
                                 unsigned int num_args,
                                 int flags) {
  CH_UNUSED(func, name, native_func, signature, args, num_args, flags);
  CH_TODO();
  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

int jit_dump_ast(FILE *stream, jit_function_t func, const char *name) {
  CH_UNUSED(name);
  std::stringstream ss;
  {
    llvm::raw_os_ostream os(ss);
    auto module = func->ctx()->module();
    module->print(os, nullptr);
  }
  fprintf(stream, "%s", ss.str().c_str());
  return 1;
}

int jit_dump_asm(FILE *stream, jit_function_t func, const char *name) {
  CH_UNUSED(name);
  llvm::SmallVector<char, 0> sv;
  {
    auto ctx = func->ctx();
    auto module = ctx->module();
    auto target = ctx->target();;
    llvm::legacy::PassManager pass;
    llvm::raw_svector_ostream os(sv);
    if (target->addPassesToEmitFile(pass, os, nullptr, llvm::TargetMachine::CGFT_AssemblyFile))
      return 0;
    pass.run(*module);
  }
  fprintf(stream, "%s", sv.data());
  return 1;
}
