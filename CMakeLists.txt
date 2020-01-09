cmake_minimum_required(VERSION 3.2)

project(cash VERSION 0.1.0 LANGUAGES CXX)

set(JIT "LLVM" CACHE STRING "JIT library to use")
set(JITs "LLVM;LIBJIT;OFF")
set_property(CACHE JIT PROPERTY STRINGS ${JITs})

option(CODECOV "Enable code coverage." OFF)

set(DEFAULT_BUILD_TYPE "Release")

# use C++17 compiler
add_compile_options(-std=c++17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(PROJECT_CONFIG ${PROJECT_NAME}Config)

# check dependent packages
find_package(IVERILOG REQUIRED)

# set include path
include_directories("include" "src/core" "src/ast" "src/compiler" "src/hdl")

#
# set source files
#

set(SOURCE_FILES  
  src/core/utils.cpp
  src/core/platform.cpp  
  src/core/context.cpp
  src/core/brconv.cpp  
  src/core/lnode.cpp
  src/core/lnodeimpl.cpp
  src/core/logic.cpp
  src/core/system.cpp
  src/core/deviceimpl.cpp
  src/core/simulatorimpl.cpp
  src/core/tracerimpl.cpp
  src/ast/ioimpl.cpp
  src/ast/proxyimpl.cpp
  src/ast/cdimpl.cpp
  src/ast/litimpl.cpp
  src/ast/regimpl.cpp
  src/ast/memimpl.cpp
  src/ast/selectimpl.cpp
  src/ast/opimpl.cpp
  src/ast/bindimpl.cpp
  src/ast/timeimpl.cpp
  src/ast/assertimpl.cpp
  src/ast/printimpl.cpp
  src/ast/udfimpl.cpp  
  src/hdl/verilogwriter.cpp
  src/hdl/firrtlwriter.cpp      
  src/eda/altera/avalon_sim.cpp
  src/compiler/compile.cpp 
  src/compiler/simref.cpp
)

if (JIT STREQUAL "LLVM")
  set(SOURCE_FILES ${SOURCE_FILES} 
      src/compiler/simjit.cpp 
      src/compiler/llvmjit.cpp
  )
elseif (JIT STREQUAL "LIBJIT")
  set(SOURCE_FILES ${SOURCE_FILES} 
      src/compiler/simjit.cpp 
      src/compiler/libjit.cpp
  )      
endif()

# build library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_compile_options(${PROJECT_NAME} PRIVATE -pedantic -Werror -Wall -Wextra)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR})

# link pthreads
find_package(Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

if (JIT STREQUAL "LIBJIT")
  message(STATUS "using LIBJIT library.")
  find_library(LIBJIT jit)
  find_path(LIBJIT_INC jit/jit.h)
  include_directories(${LIBJIT_INC})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBJIT})
  add_definitions(-DLIBJIT)
elseif (JIT STREQUAL "LLVM")
  message(STATUS "using LLVM library.")
  find_package(LLVM 8 REQUIRED)
  message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
  message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
  include_directories(${LLVM_INCLUDE_DIRS})
  add_definitions(${LLVM_DEFINITIONS})
  llvm_map_components_to_libnames(llvm_libs mcjit codegen native)
  target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs})
  add_definitions(-DLLVMJIT)
else()
  message(STATUS "JIT disabled.")
endif()

if (CODECOV)
  message(STATUS "Code coverage is enabled")
  target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
  target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
else()
  message(STATUS "Code coverage disabled.")
endif()

include(GNUInstallDirs)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_CONFIG}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# populate public include directory
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_CONFIG}.cmake)

# sub-projects
enable_testing()
add_subdirectory(examples)
add_subdirectory(tests)
#add_subdirectory(clang)