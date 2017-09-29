#!/bin/sh

# setup enviroment variables

CURDIR=`pwd`

export CASH_PATH=$CURDIR/src

export CPATH=$CASH_PATH:$CPATH

export LIBRARY_PATH=$CASH_PATH:$LIBRARY_PATH

export LD_LIBRARY_PATH=$CASH_PATH:$LD_LIBRARY_PATH

export CASH_DEBUG_LEVEL=2

export CASH_DUMP_AST=1
