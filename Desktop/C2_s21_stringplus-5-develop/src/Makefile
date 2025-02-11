СС = gcc
CF = -Wall -Wextra -Werror -std=c11
GCOV = -fprofile-arcs -ftest-coverage

OS := $(shell uname -s)
ifeq ($(OS), Darwin)
	FLAGS = -lcheck -lm
endif
ifeq ($(OS), Linux)
	FLAGS = -lcheck -lm -lsubunit
endif

all: s21_string.a

s21_string.a : s21_sprintf.o s21_string.o
	ar rcs s21_string.a s21_sprintf.o s21_string.o

s21_string.o: s21_string.c
	$(CC) $(CF) -c s21_string.c

s21_sprintf.o: s21_sprintf.c
	$(CC) $(CF) -c s21_sprintf.c

test: s21_string_gcov s21_sprintf_gcov
	$(CC) $(CF) $(GCOV) tests.c s21_string_gcov s21_sprintf_gcov -o tests_str $(FLAGS)
	./tests_str

gcov_report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out
	open out/index.html

s21_string_gcov: s21_string.c
	$(CC) $(CF) $(GCOV) -c s21_string.c -o s21_string_gcov

s21_sprintf_gcov: s21_sprintf.c
	$(CC) $(CF) $(GCOV) -c s21_sprintf.c -o s21_sprintf_gcov

clean:
	rm -rf *.o *.a *.gc* tests_str out *.html *.info *.out *gcov

