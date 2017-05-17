#!/bin/sh

# setup enviroment variables

CURDIR=`pwd`

export CPATH=$CURDIR:$CPATH

export LIBRARY_PATH=$CURDIR:$LIBRARY_PATH

export LD_LIBRARY_PATH=$CURDIR:$LD_LIBRARY_PATH

export CASH_DEBUG_LEVEL=2

export CASH_DUMP_AST=1
