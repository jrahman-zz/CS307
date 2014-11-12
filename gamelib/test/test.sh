#!/bin/bash

FAILED_TESTS=""

echo "Running game library tests"

for TEST in *.out; do
    ./${TEST} 2>&1 > "${TEST}.output"
    if [ $? != "0" ]; then
        echo -n "X"
        FAILED_TESTS="${FAILED_TESTS} ${TEST}"
    else
        echo -n "."
    fi
done
echo "" # Print newline

for TEST in ${FAILED_TESTS}; do
    echo "Failed ${TEST}"
    cat "${TEST}.output"
done
