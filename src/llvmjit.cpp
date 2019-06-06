#include "llvmjit.h"
#include "common.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <llvm/ExecutionEngine/MCJIT.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>

#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_os_ostream.h>

#pragma GCC diagnostic pop

#define	JIT_TYPE_BOOL   6
extern const jit_type_t jit_type_bool;

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

  static jit_type_t from_llvm_type(llvm::Type* type) {
    switch (type->getTypeID()) {
    case llvm::Type::VoidTyID:
      return jit_type_void;
    case llvm::Type::PointerTyID: {
      assert(type == jit_type_ptr->impl());
      return jit_type_ptr;
    }
    case llvm::Type::IntegerTyID: {
      auto size = llvm::cast<llvm::IntegerType>(type)->getBitWidth();
      switch (size) {
      case 1:
        return jit_type_bool;
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
    }
    default:
      assert(false);
      return nullptr;
    }
  }

protected:
  int kind_;
  llvm::Type* impl_;
};

_jit_type jit_type_void_def;
_jit_type jit_type_bool_def;
_jit_type jit_type_int8_def;
_jit_type jit_type_int16_def;
_jit_type jit_type_int32_def;
_jit_type jit_type_int64_def;
_jit_type jit_type_ptr_def;

const jit_type_t jit_type_void  = &jit_type_void_def;
const jit_type_t jit_type_bool  = &jit_type_bool_def;
const jit_type_t jit_type_int8  = &jit_type_int8_def;
const jit_type_t jit_type_int16 = &jit_type_int16_def;
const jit_type_t jit_type_int32 = &jit_type_int32_def;
const jit_type_t jit_type_int64 = &jit_type_int64_def;
const jit_type_t jit_type_ptr   = &jit_type_ptr_def;

///////////////////////////////////////////////////////////////////////////////

class _jit_signature : public _jit_type {
public:
  _jit_signature(jit_type_t return_type,
                 jit_type_t* arg_types,
                 unsigned int num_args)
    : _jit_type(*return_type)
    , return_type_(return_type)
    , arg_types_(num_args) {
    for (unsigned int i = 0; i < num_args; ++i) {
      arg_types_[i] = arg_types[i];
    }
  }

  auto return_type() const {
    return return_type_;
  }

  auto& arg_types() const {
    return arg_types_;
  }

  auto arg_type(unsigned i) const {
    return arg_types_.at(i);
  }

private:
  jit_type_t return_type_;
  std::vector<jit_type_t> arg_types_;
};

///////////////////////////////////////////////////////////////////////////////

class _jit_value {
public:
  _jit_value(llvm::Value* impl, jit_type_t type)
    : impl_(impl)
    , alloc_(nullptr)
    , type_(type)
  {}

  _jit_value(llvm::AllocaInst* alloc, jit_type_t type)
    : impl_(nullptr)
    , alloc_(alloc)
    , type_(type)
  {}

  auto impl() const {
    assert(impl_);
    return impl_;
  }

  auto alloc() const {
    assert(alloc_);
    return alloc_;
  }

  auto is_mutable() const {
    return (alloc_ != nullptr);
  }

  auto type() const {
    return type_;
  }

private:
  llvm::Value* impl_;
  llvm::AllocaInst* alloc_;
  jit_type_t type_;
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

class _jit_context {
public:

  _jit_context() : builder_(context_) {
    //--
    jit_type_void_def.init(JIT_TYPE_VOID, llvm::Type::getVoidTy(context_));
    jit_type_bool_def.init(JIT_TYPE_BOOL, llvm::Type::getInt1Ty(context_));
    jit_type_int8_def.init(JIT_TYPE_INT8, llvm::Type::getInt8Ty(context_));
    jit_type_int16_def.init(JIT_TYPE_INT16, llvm::Type::getInt16Ty(context_));
    jit_type_int32_def.init(JIT_TYPE_INT32, llvm::Type::getInt32Ty(context_));
    jit_type_int64_def.init(JIT_TYPE_INT64, llvm::Type::getInt64Ty(context_));
    jit_type_ptr_def.init(JIT_TYPE_PTR, llvm::Type::getInt8PtrTy(context_));
  }

  ~_jit_context() {}

  bool init() {
    auto module = std::make_unique<llvm::Module>("llvmjit", context_);    
    module_ = module.get();

    std::string error;
    engine_ = llvm::EngineBuilder(std::move(module))
                .setErrorStr(&error)
                .setOptLevel(llvm::CodeGenOpt::Aggressive)
                .setEngineKind(llvm::EngineKind::JIT)
                .create();
    if (!engine_) {
      std::cerr << "Error: failed to create llvm::EngineBuilder; " << error << std::endl;
      return false;
    }
    target_ = engine_->getTargetMachine();
    module_->setDataLayout(target_->createDataLayout());
    return true;
  }

  auto impl() {
    return &context_;
  }

  auto target() const {
    return target_;
  }

  auto module() const {
    return module_;
  }

  auto engine() const {
    return engine_;
  }

  auto builder() {
    return &builder_;
  }

  int compile(llvm::Function* func) {
    {
      static llvm::raw_os_ostream os(std::cerr);
      if (llvm::verifyFunction(*func, &os)) {
        assert(false);
        return 0;
      }
    }
    {
      llvm::legacy::FunctionPassManager fpm(module_);

      fpm.add(llvm::createAggressiveDCEPass());
      fpm.add(llvm::createPromoteMemoryToRegisterPass());
      fpm.add(llvm::createConstantPropagationPass());

      fpm.add(llvm::createInstructionCombiningPass());
      fpm.add(llvm::createReassociatePass());
      fpm.add(llvm::createNewGVNPass());
      fpm.add(llvm::createCFGSimplificationPass());

      fpm.add(llvm::createLoopSimplifyCFGPass());
      fpm.add(llvm::createSROAPass());
      fpm.add(llvm::createFlattenCFGPass());

      fpm.add(llvm::createIndVarSimplifyPass());
      fpm.add(llvm::createLICMPass());
      fpm.add(llvm::createLowerSwitchPass());

      fpm.doInitialization();
      fpm.run(*func);
    }
    return 1;
  }

  void* closure(const std::string& name) {
    return (void*)engine_->getFunctionAddress(name);
  }

  _jit_function* create_function(jit_type_t signature,
                                 const char* name,
                                 void* address = nullptr);

private:

  llvm::LLVMContext context_;
  llvm::IRBuilder<> builder_;
  llvm::Module* module_;
  llvm::ExecutionEngine* engine_;
  llvm::TargetMachine* target_;
  std::unordered_map<std::string, std::unique_ptr<_jit_function>> functions_;
};

///////////////////////////////////////////////////////////////////////////////

class _jit_function {
public:
  _jit_function(_jit_context* ctx, llvm::Function* impl, void* address)
    : ctx_(ctx)
    , impl_(impl)
    , args_(impl->arg_size())
    , cur_label_(jit_label_undefined) {
    int i = 0;
    for (auto& arg : impl->args()) {
      auto type = _jit_type::from_llvm_type(arg.getType());
      args_[i] = std::make_unique<_jit_value>(&arg, type);
      ++i;
    }
    if (address) {
      ctx->engine()->addGlobalMapping(impl, address);
    } else {
      auto bb = this->create_block(&cur_label_);
      ctx->builder()->SetInsertPoint(bb);
    }
  }

  auto ctx() const {
    return ctx_;
  }

  auto impl() const {
    return impl_;
  }

  auto arg(unsigned int index) const {
    return args_[index].get();
  }

  auto resolve_address(jit_value_t value, jit_type_t type) {
    llvm::Value* ret;
    if (value->is_mutable()) {
      ret = ctx_->builder()->CreateLoad(value->alloc());
    } else {
      ret = value->impl();
    }
    auto ptype = type->impl()->getPointerTo();
    if (ret->getType() != ptype) {
      ret = ctx_->builder()->CreatePointerCast(ret, ptype);
    }
    return ret;
  }

  auto resolve_value(jit_value_t value, jit_type_t type = nullptr) {
    llvm::Value* ret;
    if (value->is_mutable()) {
      ret = ctx_->builder()->CreateLoad(value->alloc());
    } else {
      ret = value->impl();
    }
    if (type
     && value->type()->kind() != type->kind()) {
      assert(type->impl()->getTypeID() == llvm::Type::IntegerTyID);
      ret = ctx_->builder()->CreateIntCast(ret, type->impl(), false);
    }
    return ret;
  }

  auto create_value(jit_type_t type) {
    llvm::IRBuilder<> builder(&impl_->getEntryBlock(),
                              impl_->getEntryBlock().begin());
    auto alloc = builder.CreateAlloca(type->impl());
    variables_.emplace_back(std::make_unique<_jit_value>(alloc, type));
    return variables_.back().get();
  }

  auto create_value(llvm::Value* value) {
    auto type = _jit_type::from_llvm_type(value->getType());
    variables_.emplace_back(std::make_unique<_jit_value>(value, type));
    return variables_.back().get();
  }

  llvm::BasicBlock* create_block(jit_label_t* label, bool reuse = false) {
    if (!label)
      return nullptr;
    auto l = *label;
    if (l != jit_label_undefined) {
      auto it = basicblocks_.find(l);
      if (it == basicblocks_.end())
        return nullptr;
      return it->second;
    }
    if (reuse) {
      assert(!basicblocks_.empty());
      auto bb = basicblocks_[cur_label_];
      if (0 == bb->size()) {
        *label = cur_label_;
        return bb;
      }
    }
    llvm::BasicBlock* bb;
    if (basicblocks_.empty()) {
      bb = llvm::BasicBlock::Create(*ctx_->impl(), "entry", impl_);
    } else {
      bb = llvm::BasicBlock::Create(*ctx_->impl());
    }
    l = basicblocks_.size();
    basicblocks_.emplace(l, bb);
    *label = l;
    return bb;
  }

  llvm::BasicBlock* get_current_block() {
    return basicblocks_[cur_label_];
  }

  void set_current_block(llvm::BasicBlock* block,
                         jit_label_t label,
                         bool detached = false) {
    if (!detached) {
      auto bb = basicblocks_[cur_label_];
      if (nullptr == bb->getTerminator()) {
        ctx_->builder()->CreateBr(block);
      }
    }
    impl_->getBasicBlockList().push_back(block);
    ctx_->builder()->SetInsertPoint(block);
    cur_label_ = label;
  }

  auto cur_label() const {
    return cur_label_;
  }

private:
  _jit_context* ctx_;
  llvm::Function* impl_;
  std::vector<std::unique_ptr<_jit_value>> args_;
  std::vector<std::unique_ptr<_jit_value>> variables_;
  std::unordered_map<jit_label_t, llvm::BasicBlock*> basicblocks_;
  jit_label_t cur_label_;
};

///////////////////////////////////////////////////////////////////////////////

_jit_function* _jit_context::create_function(jit_type_t signature,
                                             const char* name,
                                             void* address) {
  auto it = functions_.find(name);
  if (it != functions_.end())
    return it->second.get();
  auto j_sig = reinterpret_cast<_jit_signature*>(signature);
  std::vector<llvm::Type*> args(j_sig->arg_types().size());
  for (unsigned i = 0; i < j_sig->arg_types().size(); ++i) {
    args[i] = j_sig->arg_types()[i]->impl();
  }
  auto sig = llvm::FunctionType::get(j_sig->impl(), args, false);
  auto func = llvm::Function::Create(sig,
                                     llvm::Function::ExternalLinkage,
                                     name,
                                     module_);
  auto jfunc = new _jit_function(this, func, address);
  functions_.emplace(name, jfunc);
  return jfunc;
}

static jit_type_t find_common_type(jit_value_t lhs, jit_value_t rhs) {
  auto t1 = lhs->type();
  auto t2 = rhs->type();
  auto s1 = jit_type_get_size(t1);
  auto s2 = jit_type_get_size(t2);
  return (s1 < s2) ? t2 : t1;
}

///////////////////////////////////////////////////////////////////////////////

jit_context_t jit_context_create() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  auto context = new _jit_context();
  if (nullptr == context) {
    std::cerr << "Error: failed to create context" << std::endl;
    return nullptr;
  }
  if (!context->init())
    return nullptr;

  return context;
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
  return context->create_function(signature, "eval");
}

int jit_function_compile(jit_function_t func) {
  auto ctx = func->ctx();
  return ctx->compile(func->impl());
}

void *jit_function_to_closure(jit_function_t func) {
  auto ctx = func->ctx();
  return ctx->closure("eval");
}

///////////////////////////////////////////////////////////////////////////////

jit_type_t jit_type_create_signature(jit_abi_t abi,
                                     jit_type_t return_type,
                                     jit_type_t *args,
                                     unsigned int num_args,
                                     int incref) {
  CH_UNUSED(abi, incref);
  auto sig = new _jit_signature(return_type, args, num_args);
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
  auto kind = type->kind();
  switch (kind) {
  case JIT_TYPE_VOID:
    return 0;
  case JIT_TYPE_BOOL:
    return 1;
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
  return func->create_value(type);
}

jit_type_t jit_value_get_type(jit_value_t value) {
  return value->type();
}

jit_value_t jit_value_get_param(jit_function_t func, unsigned int param) {
  return func->arg(param);
}

jit_value_t jit_value_create_int_constant(jit_function_t func,
                                          jit_ulong const_value,
                                          jit_type_t type) {
  auto builder = func->ctx()->builder();
  auto kind = type->kind();
  switch (kind) {
  case JIT_TYPE_BOOL:
    return func->create_value(builder->getInt1(const_value));
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

jit_ulong jit_value_get_int_constant(jit_value_t value) {
  auto const_value = llvm::dyn_cast<llvm::ConstantInt>(value->impl());
  auto res = const_value->getSExtValue();
  auto size = jit_type_get_size(value->type());
  if (size < 8) {
    auto mask = (1ull << (8 * size)) - 1;
    res &= mask;
  }
  return res;
}

int jit_value_is_constant(jit_value_t value) {
  if (value->is_mutable())
    return false;
  return (llvm::dyn_cast<llvm::ConstantInt>(value->impl()) != nullptr);
}

///////////////////////////////////////////////////////////////////////////////

jit_value_t jit_insn_add(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateAdd(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_sub(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();  
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateSub(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_mul(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateMul(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_sdiv(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateSDiv(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_udiv(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateUDiv(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_srem(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateSRem(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_urem(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateURem(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_neg(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto in = func->resolve_value(value);
  auto res = builder->CreateNeg(in);
  return func->create_value(res);
}

jit_value_t jit_insn_and(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateAnd(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_or(jit_function_t func,
                        jit_value_t value1,
                        jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateOr(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_xor(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateXor(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_not(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto in = func->resolve_value(value);
  auto res = builder->CreateNot(in);
  return func->create_value(res);
}

jit_value_t jit_insn_shl(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateShl(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_sshr(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateAShr(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_ushr(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateLShr(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_eq(jit_function_t func,
                        jit_value_t value1,
                        jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpEQ(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_ne(jit_function_t func,
                        jit_value_t value1,
                        jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpNE(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_slt(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpSLT(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_ult(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpULT(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_sle(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpSLE(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_ule(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpULE(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_sgt(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpSGT(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_ugt(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpUGT(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_sge(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpSGE(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_uge(jit_function_t func,
                         jit_value_t value1,
                         jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto res = builder->CreateICmpUGE(lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_smin(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto cmp = builder->CreateICmpSLT(lhs, rhs);
  auto res = builder->CreateSelect(cmp, lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_umin(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto cmp = builder->CreateICmpULT(lhs, rhs);
  auto res = builder->CreateSelect(cmp, lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_smax(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto cmp = builder->CreateICmpSGT(lhs, rhs);
  auto res = builder->CreateSelect(cmp, lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_umax(jit_function_t func,
                          jit_value_t value1,
                          jit_value_t value2) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = find_common_type(value1, value2);
  auto lhs = func->resolve_value(value1, type);
  auto rhs = func->resolve_value(value2, type);
  auto cmp = builder->CreateICmpUGT(lhs, rhs);
  auto res = builder->CreateSelect(cmp, lhs, rhs);
  return func->create_value(res);
}

jit_value_t jit_insn_load(jit_function_t func, jit_value_t value) {
  if (jit_value_is_constant(value))
    return value;
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  if (!value->is_mutable()) {
    jit_value_t data = value;
    value = func->create_value(value->type());
    builder->CreateStore(data->impl(), value->alloc());
  }
  auto res = builder->CreateLoad(value->alloc());
  return func->create_value(res);
}

int jit_insn_store(jit_function_t func, jit_value_t dest, jit_value_t value) {
  assert(dest->is_mutable());
  auto ctx = func->ctx();
  auto builder = ctx->builder();  
  auto in = func->resolve_value(value, dest->type());
  builder->CreateStore(in, dest->alloc());
  return 1;
}

jit_value_t jit_insn_load_relative(jit_function_t func,
                                   jit_value_t base_addr,
                                   jit_nint offset,
                                   jit_type_t type) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto addr  = func->resolve_value(base_addr);
  if (offset) {
    auto idx = builder->getInt32(offset);
    addr = builder->CreateInBoundsGEP(jit_type_int8->impl(), addr, idx);
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
  auto in = func->resolve_value(value);
  auto addr = func->resolve_value(base_addr);
  if (offset) {
    auto idx = builder->getInt32(offset);
    addr = builder->CreateInBoundsGEP(jit_type_int8->impl(), addr, idx);
  }
  auto ptype = in->getType()->getPointerTo();
  if (ptype != addr->getType()) {
    addr = builder->CreatePointerCast(addr, ptype);
  }
  auto inst = builder->CreateStore(in, addr);
  return (inst != nullptr);
}

jit_value_t jit_insn_add_relative(jit_function_t func,
                                  jit_value_t base_addr,
                                  jit_nint offset) {
  assert(jit_type_ptr == base_addr->type());
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto idx = builder->getInt32(offset);
  auto addr = func->resolve_value(base_addr);
  addr = builder->CreateInBoundsGEP(jit_type_int8->impl(), addr, idx);
  return func->create_value(addr);
}

jit_value_t jit_insn_load_elem(jit_function_t func,
                               jit_value_t base_addr,
                               jit_value_t index,
                               jit_type_t elem_type) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto idx = func->resolve_value(index);
  auto addr = func->resolve_address(base_addr, elem_type);
  addr = builder->CreateInBoundsGEP(elem_type->impl(), addr, idx);
  auto value = builder->CreateLoad(elem_type->impl(), addr);
  return func->create_value(value);
}

jit_value_t jit_insn_load_elem_address(jit_function_t func,
                                       jit_value_t base_addr,
                                       jit_value_t index,
                                       jit_type_t elem_type) {
  assert(jit_type_ptr == base_addr->type());
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto idx = func->resolve_value(index);
  auto addr = func->resolve_address(base_addr, elem_type);
  auto value = builder->CreateInBoundsGEP(elem_type->impl(), addr, idx);
  if (value->getType() != jit_type_ptr->impl()) {
    value = builder->CreatePointerCast(value, jit_type_ptr->impl());
  }
  return func->create_value(value);
}

int jit_insn_store_elem(jit_function_t func,
                        jit_value_t base_addr,
                        jit_value_t index,
                        jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto in = func->resolve_value(value);
  auto elem_type = value->type();
  auto idx = func->resolve_value(index);
  auto addr = func->resolve_address(base_addr, elem_type);
  addr = builder->CreateInBoundsGEP(elem_type->impl(), addr, idx);
  auto inst = builder->CreateStore(in, addr);
  return (inst != nullptr);
}

jit_value_t jit_insn_address_of(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  if (!value->is_mutable()) {    
    jit_value_t data = value;
    value = func->create_value(value->type());
    builder->CreateStore(data->impl(), value->alloc());
  }  
  llvm::Value* alloc = value->alloc();
  if (alloc->getType() != jit_type_ptr->impl()) {
    alloc = builder->CreatePointerCast(alloc, jit_type_ptr->impl());
  }
  return func->create_value(alloc);
}

void jit_insn_set_marker(jit_function_t func, const char* name) {
  CH_UNUSED(func, name);
}

jit_value_t jit_insn_to_bool(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto in = func->resolve_value(value);
  auto zero = jit_value_create_int_constant(func, 0, value->type());
  auto res = builder->CreateICmpNE(in, zero->impl());
  return func->create_value(res);
}

int jit_insn_branch(jit_function_t func, jit_label_t *label) {
  auto BB = func->create_block(label);
  if (!BB)
    return 0;
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  builder->CreateBr(BB);
  return 1;
}

jit_value_t jit_insn_select(jit_function_t func,
                            jit_value_t cond,
                            jit_value_t case_true,
                            jit_value_t case_false) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = case_true->type();
  auto dst = func->create_value(type);
  auto cc = func->resolve_value(cond);
  auto ctype = cond->type();
  if (ctype->kind() != JIT_TYPE_BOOL) {
    auto zero = jit_value_create_int_constant(func, 0, ctype);
    cc = builder->CreateICmpNE(cc, zero->impl());
  }
  auto tt = func->resolve_value(case_true);
  auto ff = func->resolve_value(case_false);
  auto res = builder->CreateSelect(cc, tt, ff);
  builder->CreateStore(res, dst->alloc());
  return dst;
}

jit_value_t jit_insn_switch(jit_function_t func,
                            jit_value_t key,
                            const jit_value_t* preds,
                            const jit_value_t* values,
                            unsigned int num_cases,
                            jit_value_t def_value) {
  assert(num_cases != 0);
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = values[0]->type();
  auto dst = func->create_value(type);
  auto k = func->resolve_value(key);
  jit_label_t l_defBB(jit_label_undefined);
  auto defBB = func->create_block(&l_defBB);
  jit_label_t l_exitBB(jit_label_undefined);
  auto exitBB = func->create_block(&l_exitBB);
  auto sw = builder->CreateSwitch(k, defBB, num_cases);
  for (unsigned int i = 0; i < num_cases; ++i) {
    jit_label_t l_caseBB(jit_label_undefined);
    auto caseBB = func->create_block(&l_caseBB);
    {
      // case block
      func->set_current_block(caseBB, l_caseBB, true);
      auto value = func->resolve_value(values[i]);
      builder->CreateStore(value, dst->alloc());
      builder->CreateBr(exitBB);
    }
    auto pred = func->resolve_value(preds[i]);
    auto i_pred = llvm::dyn_cast<llvm::ConstantInt>(pred);
    sw->addCase(i_pred, caseBB);
  }
  {
    // default block
    func->set_current_block(defBB, l_defBB, true);
    auto value = func->resolve_value(def_value);
    builder->CreateStore(value, dst->alloc());
    builder->CreateBr(exitBB);
  }
  // exit block
  func->set_current_block(exitBB, l_exitBB, true);
  return dst;
}

int jit_insn_branch_if(jit_function_t func,
                       jit_value_t value,
                       jit_label_t *label) {
  jit_label_t l_elseBB(jit_label_undefined);
  auto thenBB = func->create_block(label);
  auto elseBB = func->create_block(&l_elseBB);
  if (!thenBB || !elseBB)
    return 0;
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto type = value->type();
  auto cond = func->resolve_value(value);
  if (type->kind() != JIT_TYPE_BOOL) {
    auto zero = jit_value_create_int_constant(func, 0, type);
    cond = builder->CreateICmpNE(cond, zero->impl());
  }
  builder->CreateCondBr(cond, thenBB, elseBB);
  func->set_current_block(elseBB, l_elseBB);
  return 1;
}

int jit_insn_branch_if_not(jit_function_t func,
                           jit_value_t value,
                           jit_label_t *label) {
  jit_label_t l_elseBB(jit_label_undefined);
  auto thenBB = func->create_block(label);
  auto elseBB = func->create_block(&l_elseBB);
  if (!thenBB || !elseBB)
    return 0;
  auto ctx = func->ctx();
  auto builder = ctx->builder();  
  auto type = value->type();
  auto cond = func->resolve_value(value);
  if (type->kind() != JIT_TYPE_BOOL) {
    auto zero = jit_value_create_int_constant(func, 0, type);
    cond = builder->CreateICmpNE(cond, zero->impl());
  }
  builder->CreateCondBr(cond, elseBB, thenBB);
  func->set_current_block(elseBB, l_elseBB);
  return 1;
}

int jit_insn_label(jit_function_t func, jit_label_t *label) {
  auto bb = func->create_block(label);
  if (!bb)
    return 0;
  func->set_current_block(bb, *label);
  return 1;
}

int jit_insn_label_tight(jit_function_t func, jit_label_t *label) {
  auto cur_label = func->cur_label();
  auto bb = func->create_block(label, true);
  if (!bb)
    return 0;
  if (*label != cur_label) {
    func->set_current_block(bb, *label);
  }
  return 1;
}

int jit_insn_return(jit_function_t func, jit_value_t value) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto in = func->resolve_value(value);
  builder->CreateRet(in);
  return 1;
}

int jit_insn_memcpy(jit_function_t func,
                    jit_value_t dest,
                    jit_value_t src,
                    jit_value_t size) {
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto ll_dest = func->resolve_value(dest);
  auto ll_src = func->resolve_value(src);
  auto ll_size = func->resolve_value(size);
  builder->CreateMemCpy(ll_dest, 1, ll_src, 1, ll_size);
  return 1;
}

jit_value_t jit_insn_call_native(jit_function_t func,
                                 const char *name,
                                 void *native_func,
                                 jit_type_t signature,
                                 jit_value_t *args,
                                 unsigned int num_args,
                                 int flags) {
  CH_UNUSED(native_func, flags);
  assert(flags == JIT_CALL_NOTHROW);
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto j_sig = reinterpret_cast<_jit_signature*>(signature);
  auto jfunc = ctx->create_function(j_sig, name, native_func);
  std::vector<llvm::Value*> ll_args(num_args);
  for (unsigned int i = 0; i < num_args; ++i) {
    ll_args[i] = func->resolve_value(args[i], j_sig->arg_type(i));
  }
  auto res = builder->CreateCall(jfunc->impl(), ll_args);
  return func->create_value(res);
}

jit_value_t jit_insn_sext(jit_function_t func,
                          jit_value_t value,
                          jit_type_t type) {
  auto vtype   = jit_value_get_type(value);
  auto vt_size = jit_type_get_size(vtype);
  auto t_size  = jit_type_get_size(type);
  assert(vt_size <= t_size);
  if (vt_size == t_size)
    return value;
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto in = func->resolve_value(value);
  auto res = builder->CreateSExt(in, type->impl());
  return func->create_value(res);
}

jit_value_t jit_insn_convert(jit_function_t func,
                             jit_value_t value,
                             jit_type_t type,
                             int overflow_check) {
  CH_DBGCHECK(0 == overflow_check, "overflow_check not supported");
  if (value->type()->kind() == type->kind())
    return value;  
  auto ctx = func->ctx();
  auto builder = ctx->builder();
  auto in = func->resolve_value(value);
  auto res = builder->CreateIntCast(in, type->impl(), false);
  return func->create_value(res);
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
    auto target = ctx->target();
    llvm::legacy::PassManager pass;
    llvm::raw_svector_ostream os(sv);
    if (target->addPassesToEmitFile(
          pass, os, nullptr, llvm::TargetMachine::CGFT_AssemblyFile))
      return 0;
    pass.run(*module);
  }
  fprintf(stream, "%s", sv.data());
  return 1;
}
