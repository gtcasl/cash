
cmake_minimum_required(VERSION 3.2)

project(cash VERSION 0.1.0 LANGUAGES CXX)

include(ExternalProject)

set(JIT "LLVM" CACHE STRING "JIT library to use")
set(JITs "LLVM;LIBJIT;OFF")
set_property(CACHE JIT PROPERTY STRINGS ${JITs})

option(CODECOV "Enable code coverage." OFF)
option(CALLTRACE "Enable call trace." ON)

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
include_directories("include")

#
# set source files
#

if (JIT STREQUAL "LLVM")
  set(PROJECT_SOURCES src/llvmjit.cpp src/simjit.cpp)
elseif (JIT STREQUAL "LIBJIT")
  set(PROJECT_SOURCES src/libjit.cpp src/simjit.cpp)
endif()

if (CALLTRACE)
  set(PROJECT_SOURCES src/slocmgr.cpp ${PROJECT_SOURCES})
endif()

set(PROJECT_SOURCES
  ${PROJECT_SOURCES}
  src/utils.cpp
  src/platform.cpp
  src/system.cpp
  src/logic.cpp
  src/lnode.cpp
  src/lnodeimpl.cpp
  src/ioimpl.cpp
  src/proxyimpl.cpp
  src/cdimpl.cpp
  src/litimpl.cpp
  src/regimpl.cpp
  src/memimpl.cpp
  src/selectimpl.cpp
  src/opimpl.cpp
  src/bindimpl.cpp
  src/timeimpl.cpp
  src/assertimpl.cpp
  src/printimpl.cpp
  src/udfimpl.cpp
  src/deviceimpl.cpp
  src/context.cpp
  src/brconv.cpp
  src/compile.cpp
  src/simref.cpp
  src/simulatorimpl.cpp
  src/tracerimpl.cpp
  src/verilogwriter.cpp
  src/firrtlwriter.cpp
  src/eda/altera/avalon_sim.cpp
)

# build library
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
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
  llvm_map_components_to_libnames(llvm_libs Core ExecutionEngine Support nativecodegen mcjit)
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

# setup call trace
if (CALLTRACE)
  find_path(LIBBFD_INCLUDE_DIR NAMES "bfd.h")
  find_library(LIBBFD_LIBRARY bfd)
  set(LIBBFD_INCLUDE_DIRS ${LIBBFD_INCLUDE_DIR} ${LIBDL_INCLUDE_DIR})
  find_package_handle_standard_args(LIBBFD DEFAULT_MSG LIBBFD_LIBRARY LIBBFD_INCLUDE_DIR)
  mark_as_advanced(LIBBFD_INCLUDE_DIR LIBBFD_LIBRARY)
  if (LIBBFD_FOUND)
    message(STATUS "Binutils-dev found.")
    target_link_libraries(${PROJECT_NAME} PRIVATE bfd dl)
    add_definitions(-DCALLTRACE)
  else()
    message(FATAL_ERROR "Binutils-dev missing!")
  endif()
else()
  message(STATUS "Calltrace disabled.")
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
