#!/bin/bash

CLANG_TIDY_OUTPUT_FILE=$1
COMMAND=`grep warning $CLANG_TIDY_OUTPUT_FILE | wc -l`
if [ $COMMAND -eq 0 ] ; then
    exit 0
fi


