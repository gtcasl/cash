
# set source files
set(TEST_SOURCES
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
    router.cpp
    cache.cpp
    jitregress.cpp    
    main.cpp
)

# copy resource directory
file(COPY "res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# build executables
add_executable(dogfood dogfood.cpp common.cpp)
add_executable(testsuite ${TEST_SOURCES})

# Define dependent libraries
target_link_libraries(dogfood PRIVATE ${PROJECT_NAME})
target_link_libraries(testsuite PRIVATE ${PROJECT_NAME})

if (CODECOV)
    target_compile_options(testsuite PRIVATE --coverage)
    target_link_libraries(testsuite PRIVATE --coverage)
endif()

# register test
add_test(NAME testsuite COMMAND ${EXECUTABLE_OUTPUT_PATH}/testsuite)
