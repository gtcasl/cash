#!/bin/bash

lcov --no-external --capture  --initial --directory $CASH_PATH --output-file /tmp/lcov_base.log

./test.out

lcov --no-external --capture -d $CASH_PATH -o /tmp/lcov_test.log

lcov --add-tracefile /tmp/lcov_base.log --add-tracefile /tmp/lcov_test.log -o /tmp/lcov.log

lcov --remove /tmp/lcov.log '/usr/include/*' '/usr/lib/*' -o /tmp/lcov.log

genhtml /tmp/lcov.log --prefix $CASH_PATH --ignore-errors source --legend --output-directory lcov_html
