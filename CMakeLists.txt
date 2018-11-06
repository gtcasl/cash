
cmake_minimum_required(VERSION 3.5)

project(cash VERSION 0.1.0 LANGUAGES CXX)

include(ExternalProject)

option(LIBJIT "Enable libjit." ON)
option(CODECOV "Enable code coverage." OFF)

set(DEFAULT_BUILD_TYPE "Release")

# use C++17 compiler
add_compile_options(-std=c++17 -pedantic -Wall -Wextra -fmax-errors=1)

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
set(PROJECT_SOURCES
    src/cash.cpp
    src/utils.cpp
    src/platform.cpp
    src/system.cpp
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
    src/timeimpl.cpp
    src/assertimpl.cpp    
    src/printimpl.cpp
    src/udfimpl.cpp
    src/lnode.cpp
    src/logic.cpp
    src/context.cpp
    src/deviceimpl.cpp
    src/compile.cpp    
    src/simulatorimpl.cpp
    src/tracerimpl.cpp
    src/simref.cpp
    src/simjit.cpp
    src/verilogwriter.cpp
    src/firrtlwriter.cpp
    src/eda/altera/avalon_sim.cpp
)

# build library
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

# link pthreads
find_package(Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

if (LIBJIT)
    message("LIBJIT compiler is enabled")
    set(LIBJIT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libjit)
    ExternalProject_Add(libjit_ext
        INSTALL_DIR ${LIBJIT_DIR}
        SOURCE_DIR ${LIBJIT_DIR}
        CONFIGURE_COMMAND ${LIBJIT_DIR}/configure --with-pic
        BUILD_IN_SOURCE 1 # libjit is building source files, so we have to do that :/
        BUILD_COMMAND ${MAKE}
        BUILD_BYPRODUCTS ${LIBJIT_DIR}/jit/.libs/libjit.a
        INSTALL_COMMAND ""
    )

    ExternalProject_Add_Step(libjit_ext
        bootstrap
        COMMAND ./bootstrap
        DEPENDEES download
        DEPENDERS configure
        WORKING_DIRECTORY ${LIBJIT_DIR}
    )
    add_library(libjit STATIC IMPORTED GLOBAL)
    set_target_properties(libjit PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${LIBJIT_DIR}/include")
    set_target_properties(libjit PROPERTIES IMPORTED_LOCATION ${LIBJIT_DIR}/jit/.libs/libjit.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE libjit)
    add_dependencies(libjit libjit_ext)
else()
    add_definitions(-DNLIBJIT)
endif()

if (CODECOV)
    message("Code coverage is enabled")
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
    target_link_libraries(${PROJECT_NAME} PRIVATE --coverage)
endif()

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
