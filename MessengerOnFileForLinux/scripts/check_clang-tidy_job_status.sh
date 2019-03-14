#!/bin/bash

CLANG_TIDY_OUTPUT_FILE=$1
COMMAND=`grep warning $CLANG_TIDY_OUTPUT_FILE | wc -l`
if [ $COMMAND -ne 0 ] ; then
    JOB_FAIL=1
    exit $JOB_FAIL
fi

