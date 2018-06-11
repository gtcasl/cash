
cmake_minimum_required(VERSION 3.5)

project(cash VERSION 0.1.0 LANGUAGES CXX)

add_compile_options(-std=c++17 -pedantic -Wall -Wextra --coverage)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")

set(DEFAULT_BUILD_TYPE "Release")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(PROJECT_CONFIG ${PROJECT_NAME}Config)

# check dependent packages
find_package(BFD REQUIRED)
find_package(IVERILOG REQUIRED)

# set include path
include_directories("include")

# set source files
set(PROJECT_SOURCES
    src/utils.cpp
    src/platform.cpp
    src/bitvector.cpp
    src/scalar.cpp
    src/lnodeimpl.cpp
    src/ioimpl.cpp
    src/proxyimpl.cpp
    src/cdimpl.cpp
    src/litimpl.cpp
    src/regimpl.cpp
    src/memimpl.cpp
    src/selectimpl.cpp
    src/aluimpl.cpp
    src/bindimpl.cpp
    src/assertimpl.cpp
    src/timeimpl.cpp
    src/printimpl.cpp
    src/udfimpl.cpp
    src/lnode.cpp
    src/logic.cpp
    src/context.cpp
    src/compile.cpp
    src/deviceimpl.cpp
    src/simulatorimpl.cpp
    src/tracerimpl.cpp
    src/vcdtracerimpl.cpp
    src/verilogwriter.cpp
    src/firrtlwriter.cpp
    src/cash.cpp
)

# build library
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

# add link libraries
target_link_libraries(${PROJECT_NAME} ${BFD_LIBRARY_PATH})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

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

