#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Sema/Sema.h>
#include <llvm/Support/raw_ostream.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include "TreeTransform.h"

#include <string>
#include <vector>
#include <sstream>

namespace {

static const char Injected_Source[] = R"-(  
  #define __builtin_VARINFO() __builtin_VARINFO_TOKEN()
  inline const char* __builtin_VARINFO_TOKEN() { return ""; }
)-";

struct arg_update_t {
  clang::Expr* expr;
  int param;  
  clang::Expr* arg;
  std::string value;
};

class MyPPCallbacks : public clang::PPCallbacks {
  using Base = clang::PPCallbacks;
public:
  MyPPCallbacks(clang::Preprocessor& pp) : pp_(pp) {}

  void FileChanged(clang::SourceLocation loc, 
                   clang::PPCallbacks::FileChangeReason reason, 
                   clang::SrcMgr::CharacteristicKind fileType, 
                   clang::FileID prevFID) {
    if (clang::PPCallbacks::EnterFile != reason)
      return;

    auto &sm = pp_.getSourceManager();
    auto fileID = sm.getFileID(sm.getFileLoc(loc));
    if (fileID == sm.getMainFileID()) {
      auto newloc = sm.getFileLoc({});
      auto buf = llvm::MemoryBuffer::getMemBuffer(Injected_Source);      
      auto fileID = sm.createFileID(std::move(buf), clang::SrcMgr::C_User, 0, 0, newloc);
      pp_.EnterSourceFile(fileID, nullptr, newloc);
    }   
  }

private:
  clang::Preprocessor& pp_;
};

class HasTokenVisitor : public clang::RecursiveASTVisitor<HasTokenVisitor> {
public:  
  using Base = clang::RecursiveASTVisitor<HasTokenVisitor>;

  HasTokenVisitor(clang::ASTContext &context, const clang::Decl* token) 
    : context_(context)
    , token_(token)
    , found_(false) 
  {}

  bool VisitCallExpr(clang::CallExpr* CE) {   
    auto callee = CE->getCalleeDecl();        
    if (callee == token_) {
      //llvm::outs() << "found!\n";
      found_ = true;
      return false;
    }
    return true;
  }

  /*bool VisitCXXDefaultArgExpr(clang::CXXDefaultArgExpr* DAE) {   
    auto dc = DAE->getUsedContext();
    if (auto callee = llvm::dyn_cast_or_null<clang::FunctionDecl>(dc)) {
      for (int i = 0, n = callee->getNumParams(); i < n; ++i) {
        auto param = callee->getParamDecl(i);
        auto da = param->getDefaultArg();
        if (da) {  
          da->dump(llvm::outs());
          HasTokenVisitor hasToken(context_, token_);
          hasToken.TraverseStmt(da);
          if (hasToken.found()) {
            found_ = true;
            return false;
          }
        }
      }
    }
    return true;
  } */ 

  bool found() const {
    return found_;
  } 

private:

  clang::ASTContext &context_; 
  const clang::Decl* token_;
  bool found_;  
};

class TokenTransform : public clang::TreeTransform<TokenTransform> {
public:
  using Base = clang::TreeTransform<TokenTransform>;
  TokenTransform(clang::Sema &sema) 
    : Base(sema) 
  {}

  clang::ExprResult TransformCallExpr(clang::CallExpr* CE) {
    auto callee = CE->getCalleeDecl();        
    if (callee == token_) {       
      auto &context = SemaRef.getASTContext();
      auto type = context.getStringLiteralArrayType(context.CharTy, name_.size());
      auto sl = clang::StringLiteral::Create(context, name_, clang::StringLiteral::Ascii, false, type, {});
      llvm::outs() << "updated: " << name_ << "\n";
      return sl;
    }
    return Base::TransformCallExpr(CE);
  }

  clang::ExprResult TransformImplicitCastExpr(clang::ImplicitCastExpr *ICE) {
    auto &context = SemaRef.getASTContext();
    clang::CXXCastPath path(ICE->path_size());    
    auto subExpr = this->TransformExpr(ICE->getSubExpr()).get();
    auto res = clang::ImplicitCastExpr::Create(
      context, ICE->getType(), ICE->getCastKind(), subExpr, &path, ICE->getValueKind());
    return res;
  }

  clang::ExprResult TransformMaterializeTemporaryExpr(clang::MaterializeTemporaryExpr *MTE) {
    auto tmpExpr = this->TransformExpr(MTE->GetTemporaryExpr()).get();
    auto matExpr = SemaRef.CreateMaterializeTemporaryExpr(
          tmpExpr->getType(), tmpExpr, MTE->isBoundToLvalueReference());
    return matExpr;
  }

  auto Transform(clang::Expr *expr, const std::string& name, const clang::Decl* token) {
    name_ = name;
    token_ = token;
    return Base::TransformExpr(expr);
  }

private:
  const clang::Decl* token_;
  std::string name_;
};

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
public:  
  using Base = clang::RecursiveASTVisitor<MyASTVisitor>;

  MyASTVisitor(clang::CompilerInstance &compiler)
    : compiler_(compiler)
    , token_(nullptr)
  {}

  bool shouldVisitTemplateInstantiations() const {
    return true;
  }

  bool shouldVisitImplicitCode() const {
    return true;
  }

  bool VisitFunctionDecl(clang::FunctionDecl* FD) {
    if (token_ != nullptr)
      return true;
    auto id = FD->getIdentifier();
    if (id) {
      if (id->getName() == "__builtin_VARINFO_TOKEN") {
        token_ = FD;
      }
    }
    return true;
  }

  bool TraverseConstructorInitializer(clang::CXXCtorInitializer* CI) {
    if (token_) {
      auto member = CI->getMember();
      if (member && !member->isTemplated()) {
        auto init = CI->getInit();
        if (init) {     
          auto &context = member->getASTContext();
          //llvm::outs() << "field_name=" << member->getName() << "\n";
          auto s = updates_.size();
          this->processArgs(init, context, member->getName());
          auto n = updates_.size();
          if (s != n) {
            std::ostringstream oss;
            const auto& ploc = compiler_.getSourceManager().getPresumedLoc(member->getLocation());
            oss << member->getName().str() << ":" << ploc.getFilename() << ":" << ploc.getLine() << ":" << ploc.getColumn();
            for (int i = s; i < n; ++i) {
              updates_[i].value = oss.str();
            }
          }
        }
      }
    }
    return Base::TraverseConstructorInitializer(CI);
  }

  bool VisitVarDecl(clang::VarDecl *VD) { 
    if (token_ == nullptr)
      return true;  

    if (VD->isTemplated())  
      return true;

    auto init = VD->getInit();
    if (init) {    
      auto &context = VD->getASTContext();
      //llvm::outs() << "decl_name=" << VD->getName() << "\n";
      auto s = updates_.size();
      this->processArgs(init, context, VD->getName());
      auto n = updates_.size();
      if (s != n) {
        std::ostringstream oss;
        const auto& ploc = compiler_.getSourceManager().getPresumedLoc(VD->getLocation());
        oss << VD->getName().str() << ":" << ploc.getFilename() << ":" << ploc.getLine() << ":" << ploc.getColumn();
        for (int i = s; i < n; ++i) {
          updates_[i].value = oss.str();
        }
      }
    }
    return true;
  }

  bool Traverse(clang::Decl* decl) {  
    if (!Base::TraverseDecl(decl))
    return false;

    if (!updates_.empty()) {     
      TokenTransform transform(compiler_.getSema()); 
      for (auto& upd : updates_) {                  
        auto res = transform.Transform(upd.arg, upd.value, token_);
        if (auto expr = llvm::dyn_cast<clang::CXXConstructExpr>(upd.expr)) {
          expr->setArg(upd.param, res.get());
        } else if (auto expr = llvm::dyn_cast<clang::CXXMemberCallExpr>(upd.expr)) {
          expr->setArg(upd.param, res.get());
        } else if (auto expr = llvm::dyn_cast<clang::CallExpr>(upd.expr)) {
          expr->setArg(upd.param, res.get());
        }
      }
      updates_.clear();
    }
    return true;
  }

private:

  void processArgs(clang::Expr *init, clang::ASTContext &context, llvm::StringRef name) {
    if (auto EWC = llvm::dyn_cast<clang::ExprWithCleanups>(init)) {
      init = EWC->getSubExpr();
    }

    if (auto BTE = llvm::dyn_cast<clang::CXXBindTemporaryExpr>(init)) {
      init = BTE->getSubExpr();
    }

    if (auto CE = llvm::dyn_cast<clang::CXXConstructExpr>(init)) {
      auto callee = CE->getConstructor();
      //llvm::outs() << "CXXConstructExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n";          
      for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
        auto da = this->FindToken(callee, i, CE->getArg(i), context);
        if (da) {
          arg_update_t var{CE, i, da, ""};
          updates_.push_back(var);     
        }
      }            
    } else
    if (auto CE = llvm::dyn_cast<clang::CXXMemberCallExpr>(init)) {
      auto callee = CE->getCalleeDecl()->getAsFunction();
      //llvm::outs() << "CXXMemberCallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n";
      for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
        auto da = this->FindToken(callee, i, CE->getArg(i), context);
        if (da) {
          arg_update_t var{CE, i, da, ""};
          updates_.push_back(var);     
        }
      }
    } else
    if (auto CE = llvm::dyn_cast<clang::CallExpr>(init)) {
      auto callee = CE->getCalleeDecl()->getAsFunction();
      //llvm::outs() << "CallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n";
      for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
        auto da = this->FindToken(callee, i, CE->getArg(i), context);
        if (da) {
          arg_update_t var{CE, i, da, ""};
          updates_.push_back(var);     
        }
      }
    }
  }

  clang::Expr* FindToken(clang::FunctionDecl *callee, int index, clang::Expr *arg, clang::ASTContext &context) {
    if (auto dae = llvm::dyn_cast<clang::CXXDefaultArgExpr>(arg)) {
      //llvm::outs() << "CXXDefaultArgExpr=" << dae->getStmtClassName() << dae->getID(context) << "\n";
      auto param = callee->getParamDecl(index);
      auto da = param->getDefaultArg();
      if (da) {  
        //da->dump(llvm::outs());
        HasTokenVisitor hasToken(context, token_);
        hasToken.TraverseStmt(da);
        if (hasToken.found())
          return da;
      }
    }
    return nullptr;
  }

  clang::CompilerInstance &compiler_;
  std::vector<arg_update_t> updates_;
  std::set<const clang::Decl*> functions_;   
  const clang::Decl* token_;
};

class MyASTConsumer : public clang::ASTConsumer {
  using Base = clang::ASTConsumer;
public:
  MyASTConsumer(clang::CompilerInstance &compiler)
    : compiler_(compiler)
    , visitor_(compiler)
  {}

  void Initialize(clang::ASTContext& context) override {
    auto &pp = compiler_.getPreprocessor();
    auto cb = std::make_unique<MyPPCallbacks>(pp);
    compiler_.getPreprocessor().addPPCallbacks(std::move(cb));
  }

  bool HandleTopLevelDecl(clang::DeclGroupRef DG) override {    
   auto &source_manager = compiler_.getSourceManager();
    for (auto decl : DG) {
      if (source_manager.isInSystemHeader(decl->getLocation())) 
        continue;      
      if (!visitor_.Traverse(decl))
        return false;
    }
    return true;
  }

  void HandleTranslationUnit(clang::ASTContext &context) override {
    auto &source_manager = compiler_.getSourceManager();
    for (auto decl : context.getTranslationUnitDecl()->decls()) {
      if (source_manager.isInSystemHeader(decl->getLocation())) 
        continue;      
      if (!visitor_.Traverse(decl))
        return;
    }

    // dump AST
    llvm::outs() << "#######################################################################################\n";
    context.getTranslationUnitDecl()->dump(llvm::outs());
  }

private:
  clang::CompilerInstance &compiler_;
  MyASTVisitor visitor_;
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
