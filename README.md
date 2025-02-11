# Simple Bash Utils

## Project Overview
This project implements custom versions of two classic Unix text processing utilities: `cat` and `grep`. These utilities were developed in C (C11 standard) as part of the School 21 curriculum. The project focuses on understanding the fundamental principles of Unix text processing tools and developing structured programming skills.

## Project Structure
```
src/
├── cat/
│   ├── s21_cat.c
│   ├── s21_cat.h
│   └── Makefile
└── grep/
    ├── s21_grep.c
    ├── s21_grep.h
    └── Makefile
```

## Implemented Features

### s21_cat Utility
Implementation of the `cat` utility with support for the following flags:
- `-b` (GNU: `--number-nonblank`) - numbers only non-empty lines
- `-e` implies `-v` (GNU only: `-E` the same, but without `-v`) - displays end-of-line characters as `$`
- `-n` (GNU: `--number`) - numbers all output lines
- `-s` (GNU: `--squeeze-blank`) - squeeze multiple adjacent blank lines
- `-t` implies `-v` (GNU: `-T` the same, but without `-v`) - displays tabs as `^I`

### s21_grep Utility
Implementation of the `grep` utility with support for the following flags:
- `-e` - pattern
- `-i` - ignore case
- `-v` - invert match
- `-c` - output count of matching lines only
- `-l` - output matching files only
- `-n` - precede each matching line with a line number
- `-h` - output matching lines without preceding them by file names
- `-s` - suppress error messages
- `-f` - obtain patterns from file
- `-o` - output the matched parts of a matching line

## Detailed Usage Examples

### s21_cat

#### Basic Usage
```bash
# Simple file output
./s21_cat file.txt

# Output multiple files
./s21_cat file1.txt file2.txt file3.txt
```

#### Line Numbering
```bash
# Number all lines
./s21_cat -n text.txt
1 First line
2
3 Third line

# Number non-empty lines only
./s21_cat -b text.txt
1 First line

2 Third line
```

#### Working with Empty Lines and Special Characters
```bash
# Squeeze empty lines and show end-of-line characters
./s21_cat -s -e text.txt
First line$
$
Third line$

# Display tabs and number lines
./s21_cat -t -n text.txt
1    Line^Iwith^Itabs
2    Second^Iline
```

### s21_grep

#### Basic Search
```bash
# Search for a string in file
./s21_grep "search" file.txt

# Case-insensitive search
./s21_grep -i "WORD" file.txt

# Inverted search
./s21_grep -v "exclude" file.txt
```

#### Working with Multiple Patterns
```bash
# Search for multiple patterns
./s21_grep -e "pattern1" -e "pattern2" file.txt

# Use patterns from file
./s21_grep -f patterns.txt file.txt
```

#### Additional Output Options
```bash
# Output only the count of matches
./s21_grep -c "word" file.txt

# Output line numbers with matches
./s21_grep -n "word" file.txt

# Output only the matching parts
./s21_grep -o "word" file.txt
```

## Implementation Features

### General Features
- Efficient memory handling with leak checks
- Error handling with informative messages
- Modular architecture for easy maintenance and extension
- Optimized file reading with buffering

### s21_cat Features
- Efficient empty line squeezing algorithm for `-s` flag
- Optimized large file processing through line-by-line reading
- Proper binary file handling
- Support for various text encodings

### s21_grep Features
- Optimized regular expressions using pcre library
- Efficient search algorithm for multiple patterns
- Proper UTF-8 string handling
- Optimized large file processing with line-by-line processing

## Technical Details
- Written in C (C11 standard)
- Compiled using gcc
- Follows POSIX.1-2017 standard
- Adheres to Google Style Guide
- Uses regular expressions (pcre/regex library)
- Includes comprehensive integration tests

## Build Instructions

### Building s21_cat
```bash
cd src/cat
make s21_cat
```

### Building s21_grep
```bash
cd src/grep
make s21_grep
```

## Testing
The project includes integration tests that compare the behavior of these implementations with the original Unix utilities. Tests cover various flag combinations and usage scenarios.

## Development Process
The development followed these key principles:
1. Modular design
2. Comprehensive error handling
3. Efficient memory management
4. Consistent code style
5. Thorough testing

## License
This project is part of the School 21 curriculum and is provided for educational purposes.
