#!/usr/bin/env bash

rm -f input.txt s21_output.txt orig_output.txt

echo "abc abc123 abcd" > input.txt

./s21_grep -o "abc" input.txt > s21_output.txt
grep -o "abc" input.txt > orig_output.txt

if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_o: OK"
else
    echo "test_o: FAIL"
    diff s21_output.txt orig_output.txt
fi

rm -f input.txt s21_output.txt orig_output.txt