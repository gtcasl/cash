#!/bin/sh

# setup enviroment variables

CURDIR=`pwd`

export CASH_HOME=$CURDIR

export CPATH=$CASH_HOME/src:$CPATH

export LIBRARY_PATH=$CASH_HOME/src:$LIBRARY_PATH

export LD_LIBRARY_PATH=$CASH_HOME/src:$LD_LIBRARY_PATH

export CASH_DEBUG_LEVEL=2

export CASH_DUMP_AST=1

export CASH_DEBUG_VERILOG=1
