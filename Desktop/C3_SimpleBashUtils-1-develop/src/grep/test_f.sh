#!/usr/bin/env bash

rm -f patterns.txt input.txt s21_output.txt orig_output.txt

echo "abc" > patterns.txt
echo "XYZ" >> patterns.txt

echo "abc line" > input.txt
echo "XYZ line" >> input.txt
echo "no match here" >> input.txt

./s21_grep -f patterns.txt input.txt > s21_output.txt
grep -f patterns.txt input.txt > orig_output.txt

if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_f: OK"
else
    echo "test_f: FAIL"
    diff s21_output.txt orig_output.txt
fi

rm -f patterns.txt input.txt s21_output.txt orig_output.txt