# set source files
set(SOURCE_FILES
    common.cpp    
    static.cpp
    basic.cpp
    system.cpp
    literals.cpp
    proxies.cpp
    aggregates.cpp
    select.cpp
    arithm.cpp
    reg.cpp
    mem.cpp
    module.cpp
    sim.cpp
    misc.cpp
    hof.cpp
    htl.cpp
    float.cpp
    udf.cpp
    fixed.cpp
    complex.cpp    
    jitregress.cpp    
    errors.cpp
    router.cpp    
    main.cpp
)

if (NOT ${CMAKE_CXX_COMPILER} MATCHES "clang")
    # cache.cpp fails on Clang (TODO: investigate why)
    set(SOURCE_FILES ${SOURCE_FILES} cache.cpp)
endif()

# copy resource directory
file(COPY "res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# build executables
add_executable(dogfood dogfood.cpp)
add_executable(testsuite ${SOURCE_FILES})

# define dependent libraries
target_link_libraries(dogfood PRIVATE ${PROJECT_NAME})
target_link_libraries(testsuite PRIVATE ${PROJECT_NAME})

if (CODECOV)
    # enable code coverage
    target_compile_options(testsuite PRIVATE --coverage)
    target_link_libraries(testsuite PRIVATE --coverage)
endif()

if (PLUGIN)
    # enable clang-plugin
    add_dependencies(dogfood cashpp)
    add_dependencies(testsuite cashpp)
    set_target_properties(dogfood PROPERTIES COMPILE_FLAGS "-Xclang -load -Xclang ${CMAKE_BINARY_DIR}/lib/libcashpp.so -Xclang -add-plugin -Xclang cash-pp")
    set_target_properties(testsuite PROPERTIES COMPILE_FLAGS "-Xclang -load -Xclang ${CMAKE_BINARY_DIR}/lib/libcashpp.so -Xclang -add-plugin -Xclang cash-pp")
endif()

# register test
add_test(NAME testsuite COMMAND ${EXECUTABLE_OUTPUT_PATH}/testsuite)