#!/bin/bash

lcov -c -d $1 -o lcov.log
genhtml lcov.log --output-directory genhtml_out
