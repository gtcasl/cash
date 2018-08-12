#!/bin/bash

COV_PATH=$1

# generate coverage trace
lcov --capture --directory $COV_PATH --output-file coverage.info 2> /dev/null

# remove external components
lcov --remove coverage.info '/usr/include/*' '/usr/lib/*' '*/examples/*' '*/tests/*' --output-file coverage.info

# report summary
lcov --list coverage.info

# report details
genhtml coverage.info --quiet --demangle-cpp --prefix $COV_PATH --ignore-errors source --legend --output-directory lcov_html
