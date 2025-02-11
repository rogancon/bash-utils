CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
INCLUDES = 
SOURCES = s21_grep.c
OBJECTS = $(SOURCES:.c=.o)
EXEC = s21_grep

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)  # Здесь отступ — табуляция

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@  # Здесь отступ — табуляция

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(EXEC)

re: fclean all
