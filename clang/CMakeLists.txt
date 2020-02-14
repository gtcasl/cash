cmake_minimum_required(VERSION 2.8)

add_definitions(${CLANG_DEFINITIONS})
include_directories(${CLANG_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

set(CLANG_LIBS
    clangFrontendTool
    clangFrontend
    clangDriver
    clangSerialization
    clangCodeGen
    clangParse
    clangSema
    clangAnalysis
    clangIndex
    clangRewrite
    clangAST
    clangLex
    clangBasic
)

set(SOURCE_FILES plugin.cpp)

add_library(cashpp SHARED ${SOURCE_FILES})

target_compile_options(cashpp PRIVATE -fno-exceptions -fno-rtti)

target_link_libraries(cashpp PRIVATE ${CLANG_LIBS})

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS cashpp
  EXPORT ${PROJECT_CONFIG}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})