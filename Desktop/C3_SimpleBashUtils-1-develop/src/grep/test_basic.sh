#!/usr/bin/env bash

rm -f s21_output.txt orig_output.txt input.txt

echo "Hello World" > input.txt
echo "Hello Universe" >> input.txt
echo "Goodbye Mars" >> input.txt

./s21_grep "Hello" input.txt > s21_output.txt
grep "Hello" input.txt > orig_output.txt

if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_basic: OK"
else
    echo "test_basic: FAIL"
    diff s21_output.txt orig_output.txt
fi

rm -f s21_output.txt orig_output.txt input.txt