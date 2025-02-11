#!/usr/bin/env bash

rm -f input1.txt input2.txt s21_output.txt orig_output.txt

echo "abc line1" > input1.txt
echo "def line2" >> input1.txt
echo "abc line3" >> input1.txt

echo "xyz line1" > input2.txt
echo "abc line2" >> input2.txt
echo "def line3" >> input2.txt

./s21_grep "abc" input1.txt input2.txt > s21_output.txt
grep "abc" input1.txt input2.txt > orig_output.txt

if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_multiple_files: OK"
else
    echo "test_multiple_files: FAIL"
    diff s21_output.txt orig_output.txt
fi

rm -f input1.txt input2.txt s21_output.txt orig_output.txt