#!/bin/sh

# setup enviroment variables

CURDIR=`pwd`

export CASH_PATH=$CURDIR/src

export CPATH=$CURDIR/src:$CPATH

export LIBRARY_PATH=$CURDIR/src:$LIBRARY_PATH

export LD_LIBRARY_PATH=$CURDIR/src:$LD_LIBRARY_PATH

export CASH_DEBUG_LEVEL=2

export CASH_DUMP_AST=1
