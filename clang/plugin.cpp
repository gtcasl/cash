#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Sema/Sema.h>
#include <llvm/Support/raw_ostream.h>

#include <string>
#include <vector>
#include <sstream>

namespace {

struct arg_update_t {
  clang::Expr* expr;
  int param;
  std::string value;
  clang::SourceLocation sloc;
};

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
public:  
  using Base = clang::RecursiveASTVisitor<MyASTVisitor>;

  MyASTVisitor(clang::ASTContext &context, std::vector<arg_update_t> &updates)
    : context_(context)
    , updates_(updates)
    , target_(nullptr)
  {}

  bool shouldVisitTemplateInstantiations() const {
    return true;
  }

  bool shouldVisitImplicitCode() const {
    return true;
  }

  bool VisitFunctionDecl(const clang::FunctionDecl* FD) {
    if (target_ != nullptr)
      return true;
    if (FD->getName() == "__builtin_VARNAME") {
      target_ = FD;
    }
    return true;
  }

  bool VisitParmVarDecl(const clang::ParmVarDecl* PD) {    
    if (this->isBuiltinVarName(PD)) {
      auto function = llvm::dyn_cast<clang::Decl>(PD->getParentFunctionOrMethod());
      if (function) {
        functions_.insert(function);
      }
    }
    return true;
  }

  bool TraverseConstructorInitializer(clang::CXXCtorInitializer* CI) {
    auto member = CI->getMember();
    var_name_ = member->getName();
    return Base::TraverseConstructorInitializer(CI);    
  }

  bool VisitVarDecl(const clang::VarDecl *VD) { 
    var_name_ = VD->getName();
    return true;
  }

  bool VisitCXXConstructExpr(clang::CXXConstructExpr* CE) {
    auto callee = CE->getConstructor();
    if (0 == functions_.count(callee))
      return true;

    auto n = CE->getNumArgs();
    for (int i = 0; i < n; ++i) {
      auto arg = CE->getArg(i);
      if (auto da = llvm::dyn_cast<clang::CXXDefaultArgExpr>(arg)) {    
        auto pd = callee->getParamDecl(i);
        if (this->isBuiltinVarName(pd)) {  
          arg_update_t var{CE, i, var_name_, arg->getBeginLoc()};
          updates_.push_back(var);       
        }
      }
    }

    return true;
  }

  bool VisitCXXMemberCallExpr(clang::CXXMemberCallExpr* CE) {
    auto callee = CE->getCalleeDecl();
    if (callee == nullptr)
      return true;

    if (0 == functions_.count(callee))
      return true;

    auto n = CE->getNumArgs();
    for (int i = 0; i < n; ++i) {
      auto arg = CE->getArg(i);
      if (auto da = llvm::dyn_cast<clang::CXXDefaultArgExpr>(arg)) {
        auto pd = callee->getAsFunction()->getParamDecl(i);
        if (this->isBuiltinVarName(pd)) {
          arg_update_t var{CE, i, var_name_, arg->getBeginLoc()};
          updates_.push_back(var);     
        }
      }
    }

    return true;
  }

  bool VisitCallExpr(clang::CallExpr* CE) {
    auto callee = CE->getCalleeDecl();
    if (callee == nullptr)
      return true;

    if (0 == functions_.count(callee))
      return true;

    auto n = CE->getNumArgs();
    for (int i = 0; i < n; ++i) {
      auto arg = CE->getArg(i);
      if (auto da = llvm::dyn_cast<clang::CXXDefaultArgExpr>(arg)) {
        auto pd = callee->getAsFunction()->getParamDecl(i);
        if (this->isBuiltinVarName(pd)) {
          arg_update_t var{CE, i, var_name_, arg->getBeginLoc()};
          updates_.push_back(var);     
        }
      }
    }

    return true;
  }

private:

  bool isBuiltinVarName(const clang::ParmVarDecl* PD) const {
    auto da = PD->getDefaultArg();
    if (da) {    
      if (auto ce = llvm::dyn_cast<clang::CallExpr>(da)) {
        auto cd = ce->getCalleeDecl();        
        if (cd == target_)
          return true;
      }
    }
    return false;
  }

  clang::ASTContext &context_;
  std::vector<arg_update_t> &updates_;
  const clang::Decl* target_;
  std::set<const clang::Decl*> functions_;  
  std::string var_name_;  
};

class MyASTConsumer : public clang::ASTConsumer {
  using Base = clang::ASTConsumer;
public:
  MyASTConsumer(clang::CompilerInstance &compiler)
    : compiler_(compiler)
  {}

  void HandleTranslationUnit(clang::ASTContext &context) override {
    std::vector<arg_update_t> updates;
    MyASTVisitor visitor(context, updates);
    const auto &source_manager = context.getSourceManager();
    const auto &mainFileID = source_manager.getMainFileID();
    const auto &decls = context.getTranslationUnitDecl()->decls();
    for (auto decl : decls) {
      const auto &fileID = source_manager.getFileID(decl->getLocation());
      if (fileID != mainFileID)
        continue;
      visitor.TraverseDecl(decl);
    }

    // apply updates
    for (auto& upd : updates) {
      auto type = context.getConstantArrayType(context.CharTy, llvm::APInt(32, upd.value.size() + 1), clang::ArrayType::Normal, 0);
      auto sl = clang::StringLiteral::Create(context, upd.value, clang::StringLiteral::Ascii, false, type, upd.sloc);
      auto cs = clang::ImplicitCastExpr::Create(context, context.getPointerType(type), clang::CK_ArrayToPointerDecay, sl, nullptr, clang::VK_RValue);
      if (auto expr = llvm::dyn_cast<clang::CXXConstructExpr>(upd.expr)) {
        expr->setArg(upd.param, cs);
      } else if (auto expr = llvm::dyn_cast<clang::CXXMemberCallExpr>(upd.expr)) {
        expr->setArg(upd.param, cs);
      } else if (auto expr = llvm::dyn_cast<clang::CallExpr>(upd.expr)) {
        expr->setArg(upd.param, cs);
      }
    }
  }

private:
  clang::CompilerInstance &compiler_;
};

class MyPlugin : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler,
                                                        llvm::StringRef /*inFile*/) override {
    return std::make_unique<MyASTConsumer>(compiler);
  }

  bool ParseArgs(const clang::CompilerInstance &compiler,
                 const std::vector<std::string> &args) override {
    return true;
  }

  clang::PluginASTAction::ActionType getActionType() override {
    return clang::PluginASTAction::AddBeforeMainAction;
  }

  void PrintHelp(llvm::raw_ostream &ros) {}
};

}

static clang::FrontendPluginRegistry::Add<MyPlugin>
    X("cash-pp", "My plugin");
