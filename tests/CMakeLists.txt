
# set source files
set(TEST_SOURCES
    common.cpp
    basic.cpp
    scalar.cpp
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
    htl.cpp
    float.cpp
    udf.cpp
    fixed.cpp
    main.cpp
)

# build executables
add_executable(dogfood dogfood.cpp)
add_executable(testsuite ${TEST_SOURCES})

# copy testbench sources
file (GLOB TB_FILES "*_tb.v")
foreach(TB_FILE ${TB_FILES})
    file(COPY ${TB_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

# Define dependent libraries
target_link_libraries(dogfood ${PROJECT_NAME})
target_link_libraries(testsuite ${PROJECT_NAME})

# register test
add_test(NAME testsuite COMMAND ${EXECUTABLE_OUTPUT_PATH}/testsuite)
