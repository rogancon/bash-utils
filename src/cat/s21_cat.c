#include <ctype.h>
#include <stdio.h>
#include <string.h>

void print_help(void) {
  printf("Usage: s21_cat [OPTION] [FILE]...\n");
  printf("Options:\n");
  printf("  -b    Number non-empty output lines\n");
  printf("  -e    Display $ at the end of each line\n");
  printf("  -n    Number all output lines\n");
  printf("  -s    Squeeze multiple empty lines\n");
  printf("  -t    Display tabs as ^I\n");
}

void print_line_number(int *line_number, const char *line) {
  printf("%6d\t%s", (*line_number)++, line);
}

int main(int argc, char *argv[]) {
  int number_lines = 0, number_nonblank = 0, squeeze_blank = 0;
  int show_ends = 0, show_tabs = 0;
  char *file_name = NULL;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0) {
      number_lines = 1;
    } else if (strcmp(argv[i], "-b") == 0) {
      number_nonblank = 1;
    } else if (strcmp(argv[i], "-s") == 0) {
      squeeze_blank = 1;
    } else if (strcmp(argv[i], "-e") == 0) {
      show_ends = 1;
    } else if (strcmp(argv[i], "-t") == 0) {
      show_tabs = 1;
    } else {
      file_name = argv[i];
    }
  }

  if (!file_name) {
    print_help();
    return 0;
  }

  FILE *file = fopen(file_name, "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  char line[1024];
  int line_number = 1;
  int last_was_blank = 0;

  while (fgets(line, sizeof(line), file)) {
    // Squeeze blank lines
    if (squeeze_blank && strcmp(line, "\n") == 0) {
      if (last_was_blank) continue;
      last_was_blank = 1;
    } else {
      last_was_blank = 0;
    }

    // Handle -b and -n flags
    if (number_nonblank && strcmp(line, "\n") != 0) {
      print_line_number(&line_number, line);
    } else if (number_lines) {
      print_line_number(&line_number, line);
    } else {
      // Handle -e flag
      if (show_ends) {
        for (char *p = line; *p; p++) {
          if (*p == '\n') {
            printf("$\n");
          } else {
            putchar(*p);
          }
        }
      }
      // Handle -t flag
      else if (show_tabs) {
        for (char *p = line; *p; p++) {
          if (*p == '\t') {
            printf("^I");
          } else {
            putchar(*p);
          }
        }
      } else {
        printf("%s", line);
      }
    }
  }

  fclose(file);
  return 0;
}
