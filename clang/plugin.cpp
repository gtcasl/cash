#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Sema/Sema.h>
#include <llvm/Support/raw_ostream.h>
#include <string>
#include <sstream>
#include "plugin.h"

namespace {

class VarDeclVisitor : public clang::RecursiveASTVisitor<VarDeclVisitor> {
public:  
  VarDeclVisitor(clang::ASTContext &context)
    : source_manager_(context.getSourceManager())
  {}

  bool VisitFunctionDecl(clang::FunctionDecl *decl) {
    /*if (decl->isLateTemplateParsed() &&
        ParsedTemplates.count(decl->getNameAsString()))
      LateParsedDecls.insert(FD);*/
    llvm::outs() << "Found " << decl->getQualifiedNameAsString() << " at "
                 << getDeclLocation(decl->getLocation()) << "\n";  
    return true;
  }

  bool VisitStmt(clang::Stmt *st) {
    llvm::outs() << "Found " << st->getStmtClassName() << " at "
                 << getDeclLocation(st->getBeginLoc()) << "\n";
    return true;
  }

  bool VisitNamedDecl(clang::NamedDecl *decl) {
    llvm::outs() << "Found " << decl->getQualifiedNameAsString() << " , type=" << decl->getDeclKindName() << " at "
                 << getDeclLocation(decl->getLocation()) << "\n";
    return true;
  }

private:
  std::string getDeclLocation(const clang::SourceLocation& sloc) const {
    std::ostringstream oss;
    const auto& ploc = source_manager_.getPresumedLoc(sloc);
    oss << ploc.getFilename() << ":"
        << ploc.getLine() << ":"
        << ploc.getColumn();
    return oss.str();
  }

private:
  clang::SourceManager& source_manager_;
};

class CashPPConsumer : public clang::ASTConsumer {
public:
  CashPPConsumer(clang::CompilerInstance &compiler)
    : compiler_(compiler)
  {}

  void HandleTranslationUnit(clang::ASTContext &context) override {
    VarDeclVisitor visitor(context);
    visitor.TraverseDecl(context.getTranslationUnitDecl());
    /*auto &source_manager = context.getSourceManager();
    const auto &mainFileID = source_manager.getMainFileID();
    const auto &decls = context.getTranslationUnitDecl()->decls();
    for (auto &decl : decls) {
      const auto &fileID = source_manager.getFileID(decl->getLocation());
      if (fileID != mainFileID)
        continue;
      visitor.TraverseDecl(decl);
    }*/   
  }

private:
  clang::CompilerInstance &compiler_;
};

class CashPreprocessor : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler,
                                                        llvm::StringRef inFile) override {
    return std::make_unique<CashPPConsumer>(compiler);
  }

  bool ParseArgs(const clang::CompilerInstance &compiler,
                 const std::vector<std::string> &args) override {
    auto &diag = compiler.getDiagnostics();
    for (unsigned i = 0, e = args.size(); i != e; ++i) {      
      if (args[i] == "-lint") {
        //--
      } else 
      if (args[i] == "-varinfo") {
        //--
      } else {
        diag.Report(diag.getCustomDiagID(clang::DiagnosticsEngine::Error,
                                           "invalid argument"));
        return false;
      }
    }

    if (!args.empty() && args[0] == "help") {
      PrintHelp(llvm::errs());
      return false;
    }

    return true;
  }

  void PrintHelp(llvm::raw_ostream &ros) {
    ros << "CashPreprocessor clang plugin.\n";
    ros << "-lint: check Cash extension macros.\n";
    ros << "-varinfo: resolve __CASH_SRCINFO__ macros.\n";
  }
};

}

static clang::FrontendPluginRegistry::Add<CashPreprocessor>
    X("cash-pp", "Cash Preprocessor");
