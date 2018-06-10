#!/bin/bash

make

COV_PATH=../

lcov -c -i -d $COV_PATH -o /tmp/lcov_base.log

make run

lcov -c -d $COV_PATH -o /tmp/lcov_test.log

lcov -a /tmp/lcov_base.log -a /tmp/lcov_test.log -o /tmp/lcov.log

lcov -r /tmp/lcov.log '/usr/include/*' '/usr/lib/*' '*/backward.h' '*/catch.h' -o /tmp/lcov.log

genhtml /tmp/lcov.log --demangle-cpp --prefix $COV_PATH --ignore-errors source --legend --output-directory lcov_html
