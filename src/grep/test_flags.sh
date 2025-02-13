#!/usr/bin/env bash

rm -f s21_output.txt orig_output.txt input.txt no_such_file.txt

echo "abc" > input.txt
echo "AbC" >> input.txt
echo "XYZabc123" >> input.txt

# -i
./s21_grep -i "abc" input.txt > s21_output.txt
grep -i "abc" input.txt > orig_output.txt
if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_flags -i: OK"
else
    echo "test_flags -i: FAIL"
    diff s21_output.txt orig_output.txt
fi

# -v
./s21_grep -v "abc" input.txt > s21_output.txt
grep -v "abc" input.txt > orig_output.txt
if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_flags -v: OK"
else
    echo "test_flags -v: FAIL"
    diff s21_output.txt orig_output.txt
fi

# -c
./s21_grep -c "abc" input.txt > s21_output.txt
grep -c "abc" input.txt > orig_output.txt
if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_flags -c: OK"
else
    echo "test_flags -c: FAIL"
    diff s21_output.txt orig_output.txt
fi

# -l
./s21_grep -l "abc" input.txt > s21_output.txt
grep -l "abc" input.txt > orig_output.txt
if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_flags -l: OK"
else
    echo "test_flags -l: FAIL"
    diff s21_output.txt orig_output.txt
fi

# -n
./s21_grep -n "abc" input.txt > s21_output.txt
grep -n "abc" input.txt > orig_output.txt
if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_flags -n: OK"
else
    echo "test_flags -n: FAIL"
    diff s21_output.txt orig_output.txt
fi

# -h
echo "abc" > no_such_file.txt
./s21_grep -h "abc" input.txt input.txt > s21_output.txt
grep -h "abc" input.txt input.txt > orig_output.txt
if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_flags -h: OK"
else
    echo "test_flags -h: FAIL"
    diff s21_output.txt orig_output.txt
fi

# -s
./s21_grep -s "abc" no_file_here.txt > s21_output.txt 2>&1
grep -s "abc" no_file_here.txt > orig_output.txt 2>&1
if diff s21_output.txt orig_output.txt > /dev/null; then
    echo "test_flags -s: OK"
else
    echo "test_flags -s: FAIL"
    diff s21_output.txt orig_output.txt
fi

rm -f s21_output.txt orig_output.txt input.txt no_such_file.txt