#!/bin/bash

lcov --capture --directory $1 --output-file lcov.log
genhtml lcov.log --output-directory genhtml_out
