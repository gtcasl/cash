
# set programs list
set(EXAMPLES 
    adder 
    counter 
    fastmult 
    fifo 
    gcd 
    vending
)

foreach(EXAMPLE ${EXAMPLES})

    # build executable
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)

    # define dependent libraries
    target_link_libraries(${EXAMPLE} ${PROJECT_NAME})

    # register test
    add_test(NAME ${EXAMPLE} COMMAND ${EXECUTABLE_OUTPUT_PATH}/${EXAMPLE})
    set_tests_properties(${EXAMPLE} PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")

endforeach()
