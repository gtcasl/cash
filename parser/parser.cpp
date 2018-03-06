#include <iostream>
#include <clang-c/Index.h>

std::ostream& operator<<(std::ostream& os, const CXString& str) {
  os << clang_getCString(str);
  clang_disposeString(str);
  return os;
}

int main(int argc, char **argv) {
  //--
  auto index = clang_createIndex(0, 0);
  auto unit = clang_parseTranslationUnit(
    index,
    "../examples/adder.cpp", nullptr, 0,
    nullptr, 0,
    CXTranslationUnit_None);
  if (unit == nullptr) {
    std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
    exit(-1);
  }

  //--
  auto cursor = clang_getTranslationUnitCursor(unit);
  clang_visitChildren(
    cursor,
    [](CXCursor cursor, CXCursor parent, CXClientData client_data)
    {
      auto kind = clang_getCursorKind(cursor);
      if (kind == CXCursor_VarDecl) {
        CXString filename;
        unsigned line;
        unsigned column;
        {
          CXFile file;
          auto range = clang_getCursorExtent(cursor);
          auto location = clang_getRangeStart(range);
          clang_getFileLocation(location, &file, &line, &column, NULL);
          filename = clang_getFileName(file);
        }
        auto name = clang_getCursorSpelling(cursor);
        auto type = clang_getCursorType(cursor);
        std::cout << clang_getTypeSpelling(type) << " ";
        std::cout << "found variable '" << name << "' at " << filename << ":" << line << ":" << column << std::endl;
      }
      return CXChildVisit_Recurse;
    },
    nullptr);

  //--
  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);

  //--
  return 0;
}
