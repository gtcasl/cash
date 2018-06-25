#!/bin/bash

COV_PATH=$1

# generate coverage trace
lcov --capture --directory $COV_PATH --output-file coverage.info 2> /dev/null

# remove external components
lcov --remove coverage.info '/usr/include/*' '/usr/lib/*' '*/backward.h' '*/catch.h' --output-file coverage.info

# show report
lcov --list coverage.info
