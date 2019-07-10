#!/bin/bash

SCRIPT_DIR=`dirname $0`
JIT=$1

function generate() # Handy Extract Program
{
	pushd $SCRIPT_DIR/../../../examples
	CASH_CFLAGS=8 ../bin/$1
	popd
	cp $SCRIPT_DIR/../../../examples/simjit.asm $1_$2.asm
}

generate fifo $JIT
generate matmul $JIT
generate aes $JIT
generate fft $JIT
generate sobel $JIT
generate vectoradd $JIT
