#!/bin/bash

function error_exit() {
	echo ""
	echo "[ERROR] $1"
	echo ""
	exit 1
}

COMPILER="gcc"
LDFLAGS="-lcriterion"
EXECUTABLE="current_test"

all_test_c_files="$(ls -1 test/*.c | tr "\n" " ")"

for test_c_file in ${all_test_c_files}
do
	${COMPILER} -Wall -o ${EXECUTABLE} ${test_c_file} ${LDFLAGS} || error_exit "Compilation failed"
	./${EXECUTABLE} || error_exit "Test failed"
done
