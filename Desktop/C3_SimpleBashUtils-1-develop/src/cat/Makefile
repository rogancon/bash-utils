CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = s21_cat

all: $(TARGET)

$(TARGET): s21_cat.c
	$(CC) $(CFLAGS) -o $(TARGET) s21_cat.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
