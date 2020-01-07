#!/bin/bash

CASH_DIR=$1

# exit on error
set +e

# Test LLVM Release project
 mkdir -p build_llr
 pushd build_llr
 cmake -DJIT=LLVM -DCMAKE_BUILD_TYPE=Release $CASH_DIR
 make -j`nproc` all
 make test   
 CASH_CFLAGS=256 make test    # Turn off JIT
 CASH_CFLAGS=512 make test    # Turn off CFO opts
 CASH_CFLAGS=523904 make test # Turn off all opts
 pushd tests
 valgrind ../bin/testsuite
 CASH_CFLAGS=256 valgrind ../bin/testsuite
 CASH_CFLAGS=512 valgrind ../bin/testsuite
 CASH_CFLAGS=523904 valgrind ../bin/testsuite
 popd
 popd

# Test LIBJIT Release project
 mkdir -p build_jbr
 pushd build_jbr
 cmake -DJIT=LIBJIT -DCMAKE_BUILD_TYPE=Release $CASH_DIR
 make -j`nproc` all
 make test
 CASH_CFLAGS=523904 make test
 pushd tests
 valgrind ../bin/testsuite
 CASH_CFLAGS=523904 valgrind ../bin/testsuite
 popd
 popd

# Test LLVM Debug project
 export CASH_DEBUG_LEVEL=3
 mkdir -p build_lld
 pushd build_lld
 cmake -DJIT=LLVM -DCMAKE_BUILD_TYPE=Debug -DCODECOV=ON $CASH_DIR
 make -j`nproc` all 
 CASH_CFLAGS=15  make test
 CASH_CFLAGS=271 make test
 CASH_CFLAGS=527 make test
 CASH_CFLAGS=523919 make test
 CASH_CFLAGS=524288 make test
 popd