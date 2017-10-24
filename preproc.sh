#!/bin/bash

g++ -std=c++14 -O0 -g -fmax-errors=5 -E -dD $1 > preproc.log

clang-format-3.6 preproc.log -i

gedit preproc.log
