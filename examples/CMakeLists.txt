# set programs list
set(EXAMPLES 
    adder 
    counter 
    fastmul 
    fifo 
    gcd 
    vending    
    sqrt
    matmul
    aes    
    fft
    sobel
	vectoradd
)

# copy resource directory
file(COPY "res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

foreach(EXAMPLE ${EXAMPLES})

    # build executable
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    
    # define dependent libraries
    target_link_libraries(${EXAMPLE} PRIVATE ${PROJECT_NAME})

    if (PLUGIN)
        # enable clang-plugin
        add_dependencies(${EXAMPLE} cashpp)
        set_target_properties(${EXAMPLE} PROPERTIES COMPILE_FLAGS "-Xclang -load -Xclang ${CMAKE_BINARY_DIR}/lib/libcashpp.so -Xclang -add-plugin -Xclang cash-pp")
    endif()

    # register test
    add_test(NAME ${EXAMPLE} COMMAND ${EXECUTABLE_OUTPUT_PATH}/${EXAMPLE})
    set_tests_properties(${EXAMPLE} PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")

endforeach()
