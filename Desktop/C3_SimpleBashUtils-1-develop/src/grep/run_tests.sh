#!/usr/bin/env bash

echo "Running all tests..."

tests=(test_basic.sh test_flags.sh test_multiple_files.sh test_o.sh test_f.sh)

for test_script in "${tests[@]}"; do
    echo "Running $test_script..."
    bash "$test_script"
    echo
done