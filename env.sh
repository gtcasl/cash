#!/bin/sh

# setup enviroment variables

CURDIR=`pwd`

export CASH_PATH=$CURDIR

export CPATH=$CASH_PATH/src:$CPATH

export LIBRARY_PATH=$CASH_PATH/src:$LIBRARY_PATH

export LD_LIBRARY_PATH=$CASH_PATH/src:$LD_LIBRARY_PATH

export CASH_DEBUG_LEVEL=2

export CASH_DUMP_AST=1
