
find_path(BFD_INCLUDE_DIR 
  bfd.h 
  ${CMAKE_PLATFORM_IMPLICIT_INCLUDE_DIRECTORIES}
)

find_library(BFD_LIBRARY_PATH
  NAMES bfd
  PATHS ${CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES}
)

if(BFD_INCLUDE_DIR AND BFD_LIBRARY_PATH)
  message(STATUS "Found bfd library: ${BFD_LIBRARY_PATH}")
else()
  message(FATAL_ERROR "Could not find bfd library")
endif()
