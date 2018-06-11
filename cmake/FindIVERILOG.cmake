
FIND_PROGRAM(IVERILOG_PATH iverilog)

if (IVERILOG_PATH)
  message(STATUS "Found iverilog program: ${IVERILOG_PATH}")
else (IVERILOG_PATH)
  message(FATAL_ERROR "Couldn't find iverilog program")
endif (IVERILOG_PATH)
