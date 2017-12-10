#!/bin/bash

g++ -std=c++17 -O0 -g -Wall -Wextra -Werror -fmax-errors=5 -E -P $1 > preproc.log

clang-format-3.6 preproc.log -i

gedit preproc.log
