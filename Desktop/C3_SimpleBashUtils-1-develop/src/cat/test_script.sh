#!/bin/bash

TEST_FILE="test.txt"
RESULT_FILE="result.txt"
EXPECTED_FILE="expected.txt"

run_test() {
    FLAG=$1
    bin/s21_cat $FLAG "$TEST_FILE" > "$RESULT_FILE"
    cat $FLAG "$TEST_FILE" > "$EXPECTED_FILE"

    if diff "$RESULT_FILE" "$EXPECTED_FILE" > /dev/null; then
        echo "Test $FLAG passed!"
    else
        echo "Test $FLAG failed!"
        diff "$RESULT_FILE" "$EXPECTED_FILE"
    fi

    rm -f "$RESULT_FILE" "$EXPECTED_FILE"
}

# Test all flags
run_test "-n"
run_test "-b"
run_test "-s"
run_test "-e"
run_test "-t"
