
# build executables
add_executable(adder adder.cpp)
add_executable(counter counter.cpp)
add_executable(fastmult fastmult.cpp)
add_executable(fifo fifo.cpp)
add_executable(gcd gcd.cpp)
add_executable(vending vending.cpp)

# copy testbench sources
file (GLOB TB_FILES "*_tb.v")
foreach(TB_FILE ${TB_FILES})
    file(COPY ${TB_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

# Define dependent libraries
target_link_libraries(adder ${PROJECT_NAME})
target_link_libraries(counter ${PROJECT_NAME})
target_link_libraries(fastmult ${PROJECT_NAME})
target_link_libraries(fifo ${PROJECT_NAME})
target_link_libraries(gcd ${PROJECT_NAME})
target_link_libraries(vending ${PROJECT_NAME})

#register tests
add_test(NAME adder COMMAND ${EXECUTABLE_OUTPUT_PATH}/adder)
add_test(NAME counter COMMAND ${EXECUTABLE_OUTPUT_PATH}/counter)
add_test(NAME fastmult COMMAND ${EXECUTABLE_OUTPUT_PATH}/fastmult)
add_test(NAME fifo COMMAND ${EXECUTABLE_OUTPUT_PATH}/fifo)
add_test(NAME gcd COMMAND ${EXECUTABLE_OUTPUT_PATH}/gcd)
add_test(NAME vending COMMAND ${EXECUTABLE_OUTPUT_PATH}/vending)
