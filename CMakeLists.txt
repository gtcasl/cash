
cmake_minimum_required(VERSION 3.2)

project(cash VERSION 0.1.0 LANGUAGES CXX)

include(ExternalProject)

option(LLVMJIT "Enable llvmjit." ON)
option(LIBJIT "Enable libjit." OFF)
option(INTERPRETER "Enable libjit interpreter." OFF)
option(CODECOV "Enable code coverage." OFF)

set(DEFAULT_BUILD_TYPE "Release")

# use C++17 compiler
add_compile_options(-std=c++17 -pedantic -Wall -Wextra -fmax-errors=5)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(PROJECT_CONFIG ${PROJECT_NAME}Config)

# check dependent packages
find_package(IVERILOG REQUIRED)

# set include path
include_directories("include")

# set source files
if (LIBJIT)
    set(PROJECT_SOURCES src/libjit.cpp)
elseif (LLVMJIT)
    set(PROJECT_SOURCES src/llvmjit.cpp)
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
    src/slocmgr.cpp
    src/compile.cpp
    src/simref.cpp
    src/simjit.cpp    
    src/simulatorimpl.cpp
    src/tracerimpl.cpp
    src/verilogwriter.cpp
    src/firrtlwriter.cpp    
    src/eda/altera/avalon_sim.cpp
)

# build library
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

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

if (LIBJIT)
    message("LIBJIT compiler is enabled")
    set(LIBJIT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libjit)
    set(LIBJIT_BUILD_DIR ${CMAKE_BINARY_DIR}/src/libjit_ext-build)
    set(LIBJIT_OPTS --with-pic)
    if (INTERPRETER)
        set(LIBJIT_OPTS ${LIBJIT_OPTS} --enable-interpreter)
        add_definitions(-DJIT_BACKEND_INTERP)
    endif()
    ExternalProject_Add(libjit_ext
        PREFIX ${CMAKE_BINARY_DIR}
        SOURCE_DIR ${LIBJIT_SRC_DIR}
        CONFIGURE_COMMAND ${LIBJIT_SRC_DIR}/configure ${LIBJIT_OPTS}
        BUILD_COMMAND ${MAKE}
        INSTALL_COMMAND ""
    ) 
    ExternalProject_Add_Step(libjit_ext
        bootstrap
        COMMAND ./bootstrap
        DEPENDEES download
        DEPENDERS configure
        WORKING_DIRECTORY ${LIBJIT_SRC_DIR}
    )
    add_library(libjit STATIC IMPORTED GLOBAL)
    add_dependencies(libjit libjit_ext)
    file(MAKE_DIRECTORY ${LIBJIT_BUILD_DIR}/include)
    set_target_properties(libjit PROPERTIES
                          IMPORTED_LOCATION "${LIBJIT_BUILD_DIR}/jit/.libs/libjit.a"
                          INTERFACE_INCLUDE_DIRECTORIES "${LIBJIT_SRC_DIR}/include;${LIBJIT_BUILD_DIR}/include")
    target_link_libraries(${PROJECT_NAME} PRIVATE libjit)    
    add_definitions(-DLIBJIT)
elseif (LLVMJIT)
    find_package(LLVM 8.0 REQUIRED)
    message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
    include_directories(${LLVM_INCLUDE_DIRS})
    add_definitions(${LLVM_DEFINITIONS})

    llvm_map_components_to_libnames(llvm_libs Core ExecutionEngine Interpreter Support nativecodegen mcjit)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs})
    add_definitions(-DLLVMJIT)
endif()

if (CODECOV)
    message("Code coverage is enabled")
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
    target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
endif()

# setup call trace
find_path(LIBBFD_INCLUDE_DIR NAMES "bfd.h")
find_library(LIBBFD_LIBRARY bfd)
set(LIBBFD_INCLUDE_DIRS ${LIBBFD_INCLUDE_DIR} ${LIBDL_INCLUDE_DIR})
find_package_handle_standard_args(LIBBFD DEFAULT_MSG LIBBFD_LIBRARY LIBBFD_INCLUDE_DIR)
mark_as_advanced(LIBBFD_INCLUDE_DIR LIBBFD_LIBRARY)
if (LIBBFD_FOUND)
  MESSAGE(STATUS "Binutils-dev found.")
  target_link_libraries(${PROJECT_NAME} PRIVATE bfd dl)
  add_definitions(-DCALLTRACE)
else()
  MESSAGE(STATUS "Binutils-dev missing.")
endif()

include(GNUInstallDirs)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_CONFIG}
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

# populate public include directory
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_CONFIG}.cmake)

# sub-projects
enable_testing()
add_subdirectory(examples)
add_subdirectory(tests)
