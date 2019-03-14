#!/bin/bash

VALGRIND_OUTPUT_FILE=$1
VALGRIND_ERRORS_SUMARY=$(cat $VALGRIND_OUTPUT_FILE | grep "ERROR SUMMARY")
ERRORS_NUMBER_POSITION_IN_ERRORS_SUMARY=25
ERRORS_NUMBER=${VALGRIND_ERRORS_SUMARY:$ERRORS_NUMBER_POSITION_IN_ERRORS_SUMARY:1}

if [ $ERRORS_NUMBER -ne 0 ] ; then
    JOB_FAIL=1
    exit $JOB_FAIL
fi

