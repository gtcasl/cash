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

#ifdef NDEBUG
  #define CH_DBG(...)
#else
  #define CH_DBG(...) if (g_debug) do { llvm::outs() << __VA_ARGS__; llvm::outs().flush(); } while (false)
#endif

namespace {

bool g_debug = false;
bool g_dump_ast = false;

unsigned int g_replace_count = -1;
unsigned int g_replace_id = 0;

static const char Injected_Source[] = R"-(  
  #define __builtin_VARNAME() __builtin_VARNAME_TOKEN()
  inline const char* __builtin_VARNAME_TOKEN() { return ""; }
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
    CH_DBG("@@ processing file: " << sm.getFilename(loc) << "\n");
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
      CH_DBG("@@ found!\n");
      found_ = true;
      return false;
    }
    return true;
  }

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
      CH_DBG("@@ updated: " << name_ << "\n");
      return sl;
    }
    return Base::TransformCallExpr(CE);
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
      if (id->getName() == "__builtin_VARNAME_TOKEN") {
        token_ = FD;
      }
    }
    return true;
  }

  bool TraverseConstructorInitializer(clang::CXXCtorInitializer* CI) {
    do {
      if (token_ == nullptr)
        break;

      auto member = CI->getMember();
      if (member == nullptr || member->isTemplated())
        break;
      
      auto init = CI->getInit();
      if (init == nullptr)
        break;
      
      CH_DBG("@@ field_name=" << member->getName() << "\n");
      
      auto s = updates_.size();
      this->parseAST(init, member->getASTContext());
      auto n = updates_.size();
      if (s != n) {
        for (int i = s; i < n; ++i) {
          updates_[i].value = member->getName();
        } 
      }

      CH_DBG("@@ end\n");
    } while(false);

    return Base::TraverseConstructorInitializer(CI);
  }

  bool VisitVarDecl(clang::VarDecl *VD) {
    if (token_ == nullptr)
      return true;

    if (VD->isTemplated())
      return true;

    auto init = VD->getInit();
    if (init == nullptr)
       return true;

    CH_DBG("@@ decl_name=" << VD->getName() << "\n");
    
    auto s = updates_.size();
    this->parseAST(init, VD->getASTContext());
    auto e = updates_.size();
    if (s != e) {
      for (int i = s; i < e; ++i) {
        updates_[i].value = VD->getName();
      }
    }

    CH_DBG("@@ end\n");
    return true;
  }

  bool Traverse(clang::Decl* decl) {  
    if (!Base::TraverseDecl(decl))
      return false;

    if (!updates_.empty()) {     
      TokenTransform transform(compiler_.getSema()); 
      for (auto& upd : updates_) {      

        auto res = transform.Transform(upd.arg, upd.value, token_);       

      #ifndef NDEBUG
        if (g_debug) {
          if (g_replace_id < g_replace_count) {
            CH_DBG("@@ transform#" << g_replace_id++ << ": " << upd.value << "\n");
          } else {
            break;
          }        
          res.get()->dump(llvm::outs());  
          llvm::outs().flush();
        }
      #endif

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

  void parseAST(clang::Expr *init, clang::ASTContext &context) {

    if (auto EWC = llvm::dyn_cast<clang::ExprWithCleanups>(init)) {
      init = EWC->getSubExpr();
    } 
      
    if (auto BTE = llvm::dyn_cast<clang::CXXBindTemporaryExpr>(init)) {
      init = BTE->getSubExpr();
    }
  
    if (auto CE = llvm::dyn_cast<clang::CXXConstructExpr>(init)) {
      auto callee = CE->getConstructor();
      if (callee) {        
        CH_DBG("@@ CXXConstructExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n");          
        for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
          this->FindToken(CE, callee, i, CE->getArg(i), context);
        }
      }            
    } else
    if (auto CE = llvm::dyn_cast<clang::CXXMemberCallExpr>(init)) {
      auto callee = CE->getDirectCallee();
      if (callee) {
        CH_DBG("@@ CXXMemberCallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n");
        for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
          this->FindToken(CE, callee, i, CE->getArg(i), context);
        }
      }
    } else
    if (auto CE = llvm::dyn_cast<clang::CXXOperatorCallExpr>(init)) {
      auto callee = CE->getDirectCallee();
      if (callee) {
        CH_DBG("@@ CXXOperatorCallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n");
        for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
          this->FindToken(CE, callee, i, CE->getArg(i), context);
        }
      }
    } else 
    if (auto CE = llvm::dyn_cast<clang::CallExpr>(init)) {
      auto callee = CE->getDirectCallee();
      if (callee) {
        CH_DBG("@@ CallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n");
        for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
          this->FindToken(CE, callee, i, CE->getArg(i), context);
        }
      }
    } else {
      CH_DBG("@@ UnknownExpr=" << init->getStmtClassName() << ", " << init->getID(context) << "\n");
    }
  }

  void FindToken(clang::Expr* callexpr,
                 clang::FunctionDecl *callee, 
                 int index, 
                 clang::Expr *arg, 
                 clang::ASTContext &context) {    
    if (auto DAE = llvm::dyn_cast<clang::CXXDefaultArgExpr>(arg)) {
      CH_DBG("@@ CXXDefaultArgExpr=" << DAE->getStmtClassName() << ", " << DAE->getID(context) << "\n");
      auto param = callee->getParamDecl(index);
      auto da = param->getDefaultArg();
      if (da) {  

      #ifndef NDEBUG
        if (g_debug) {
          da->dump(llvm::outs()); 
          llvm::outs().flush();
        }
      #endif
        
        HasTokenVisitor hasToken(context, token_);
        hasToken.TraverseStmt(da);
        if (hasToken.found()) {
          arg_update_t var{callexpr, index, da, ""};
          updates_.push_back(var);     
        }
      }
    } else {
      clang::Expr *expr = arg, *parent = nullptr; 

      if (auto ICE = llvm::dyn_cast<clang::ImplicitCastExpr>(expr)) {
        expr = ICE->getSubExpr();
      }

      if (auto BTE = llvm::dyn_cast<clang::CXXBindTemporaryExpr>(expr)) {
        CH_DBG("@@ CXXBindTemporaryExpr=" << BTE->getStmtClassName() << ", " << BTE->getID(context) << "\n");
        parent = BTE;
        expr = BTE->getSubExpr();
      } else
      if (auto MTE = llvm::dyn_cast<clang::MaterializeTemporaryExpr>(expr)) {
        CH_DBG("@@ MaterializeTemporaryExpr=" << MTE->getStmtClassName() << ", " << MTE->getID(context) << "\n");
        expr = MTE->GetTemporaryExpr();
      } else {
        CH_DBG("@@ UnknownExpr=" << expr->getStmtClassName() << ", " << expr->getID(context) << "\n");
        return;
      }
      
      if (auto ICE = llvm::dyn_cast<clang::ImplicitCastExpr>(expr)) {
        parent = ICE;
        expr = ICE->getSubExpr();
      }      
      
      if (auto BTE = llvm::dyn_cast<clang::CXXBindTemporaryExpr>(expr)) {
        parent = BTE;
        expr = BTE->getSubExpr();
      }

      if (auto ICE = llvm::dyn_cast<clang::ImplicitCastExpr>(expr)) {
        parent = ICE;
        expr = ICE->getSubExpr();        
      }

      if (auto CE = llvm::dyn_cast<clang::CXXConstructExpr>(expr)) {
        CH_DBG("@@ CXXConstructExpr=" << CE->getStmtClassName() << ", " << CE->getID(context) << "\n");

        assert(parent != nullptr);

        auto s = updates_.size();
        for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
          this->FindToken(CE, CE->getConstructor(), i, CE->getArg(i), context);
        }
        auto e = updates_.size();
        if (s != e) {
          auto &sema = compiler_.getSema();
          auto constructor = CE->getConstructor();
          
          llvm::SmallVector<clang::Expr *, 8> args(CE->arguments());

          auto TOE = clang::CXXTemporaryObjectExpr::Create(
              context, 
              constructor, 
              CE->getType(),
              constructor->getTypeSourceInfo(), 
              args, 
              CE->getParenOrBraceRange(),
              CE->hadMultipleCandidates(), 
              CE->isListInitialization(),
              CE->isStdInitListInitialization(), 
              CE->requiresZeroInitialization()
          ); 

          if (auto BTE = llvm::dyn_cast<clang::CXXBindTemporaryExpr>(parent)) {
            BTE->setSubExpr(TOE);
          } else
          if (auto ICE = llvm::dyn_cast<clang::ImplicitCastExpr>(parent)) {
            ICE->setSubExpr(TOE);        
          } else {
            assert(false);
          }

          CH_DBG("@@ replaced TOE\n");

          for (int i = s; i < e; ++i) {
            if (updates_[i].expr == CE) {
              updates_[i].expr = TOE;
            }
          }
        }
      }  else
      if (auto CE = llvm::dyn_cast<clang::CXXMemberCallExpr>(expr)) {
        auto callee = CE->getDirectCallee();
        if (callee) {
          CH_DBG("@@ CXXMemberCallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n");
          for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
            this->FindToken(CE, callee, i, CE->getArg(i), context);
          }
        }
      } else
      if (auto CE = llvm::dyn_cast<clang::CXXOperatorCallExpr>(expr)) {
        auto callee = CE->getDirectCallee();
        if (callee) {
          CH_DBG("@@ CXXOperatorCallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n");
          for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
            this->FindToken(CE, callee, i, CE->getArg(i), context);
          }
        }
      } else 
      if (auto CE = llvm::dyn_cast<clang::CallExpr>(expr)) {
        auto callee = CE->getDirectCallee();
        if (callee) {
          CH_DBG("@@ CallExpr=" << callee->getDeclName() << ", " <<  CE->getID(context) << "\n");
          for (int i = 0, n = CE->getNumArgs(); i < n; ++i) {
            this->FindToken(CE, callee, i, CE->getArg(i), context);
          }
        }
      } else {
        CH_DBG("@@ UnknownExpr=" << expr->getStmtClassName() << ", " << expr->getID(context) << "\n");
      }
    }
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
    CH_DBG("@@ HandleTopLevelDecl()\n");
          
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
    CH_DBG("@@ HandleTranslationUnit()\n");

    auto &source_manager = compiler_.getSourceManager();    
    for (auto decl : context.getTranslationUnitDecl()->decls()) {
      if (source_manager.isInSystemHeader(decl->getLocation())) 
        continue;
      if (!visitor_.Traverse(decl))
        return;
    }

  #ifndef NDEBUG
    if (g_dump_ast) {
      // dump AST
      llvm::outs() << "#######################################################################################\n";
      context.getTranslationUnitDecl()->dump(llvm::outs());
    }
  #endif
  }

private:
  clang::CompilerInstance &compiler_;
  MyASTVisitor visitor_;
};

class MyPlugin : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler,
                                                        llvm::StringRef /*inFile*/) override {
    auto rc = std::getenv("CASHPP_REPLACE_COUNT");
    if (rc) {
      g_replace_count = atoi(rc);
      llvm::outs() << "CASHPP_REPLACE_COUNT=" << g_replace_count << "\n";      
    }
    return std::make_unique<MyASTConsumer>(compiler);
  }

  clang::PluginASTAction::ActionType getActionType() override {
    return clang::PluginASTAction::AddBeforeMainAction;
  }

  bool ParseArgs(const clang::CompilerInstance &compiler,
                 const std::vector<std::string> &args) override {
    for (int i = 0, e = args.size(); i != e; ++i) {
      if (args[i] == "help") {
        this->PrintHelp(llvm::errs());
        return false;
      } else 
      if (args[i] == "debug") {
        g_debug = true;
      } else 
      if (args[i] == "dump-ast") {
        g_dump_ast = true;
      } else {
        auto &D = compiler.getDiagnostics();
        D.Report(D.getCustomDiagID(clang::DiagnosticsEngine::Error, "invalid argument '%0'"));
        return false;
      }      
    }
    return true;
  }

  void PrintHelp(llvm::raw_ostream &ros) {
    ros << "Cash Preprocessor Clang Plugin\n";
    ros << "Options:\n";
    ros << "debug : Enable debug mode.\n";
    ros << "dump-ast : Dump updated AST.\n";
    ros << "help : Show usage.\n";
  }
};

}

static clang::FrontendPluginRegistry::Add<MyPlugin>
    X("cash-pp", "My plugin");
