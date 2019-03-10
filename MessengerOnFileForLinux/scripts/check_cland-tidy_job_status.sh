#!/bin/bash

CLANG_TIDY_OUTPUT_FILE=$1
COMMAND=`grep warning $CLANG_TIDY_OUTPUT_FILE | wc -l`
if [ $COMMAND -eq 0 ] ; then
    mkdir no_clang-tidy_warnigns
fi
cd no_clang-tidy_warnigns

