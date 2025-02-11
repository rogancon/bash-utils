#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PATTERNS 500

typedef struct {
  int e, f, i, v, c, l, n, h, s, o;
  char patterns[MAX_PATTERNS][MAX_LINE_LENGTH];
  int pattern_count;
} arguments;

void add_pattern(arguments *args, char *pattern);
int process_arguments(int argc, char *argv[], arguments *args);
int prioritet(int argc, char *argv[], arguments *args);
int load_patterns_from_file(char *filename, arguments *args);
int compile_patterns(arguments *args, regex_t compiled_patterns[]);
int matches_any_pattern(char *line, regex_t compiled_patterns[], int count,
                        int v_flag, regmatch_t *match);
void grep_stream(FILE *stream, char *filename, arguments *args,
                 regex_t compiled_patterns[], int pattern_count,
                 int is_multiple_files);
int grep_file(char *filename, arguments *args, regex_t compiled_patterns[],
              int pattern_count, int is_multiple_files);
void handle_flag_o(char *line, regex_t compiled_patterns[], int pattern_count,
                   arguments *args, char *filename, int line_number,
                   int is_multiple_files);
void free_patterns(regex_t compiled_patterns[], int count);

int main(int argc, char *argv[]) {
  arguments args = {0};
  regex_t compiled_patterns[MAX_PATTERNS];
  int exit_status = 0;

  if (process_arguments(argc, argv, &args) == 0 &&
      compile_patterns(&args, compiled_patterns) == 0) {
    int file_count = argc - optind;
    int is_multiple_files = file_count > 1;

    if (file_count == 0) {
      grep_stream(stdin, NULL, &args, compiled_patterns, args.pattern_count,
                  is_multiple_files);
    } else {
      for (int i = optind; i < argc; ++i) {
        if (grep_file(argv[i], &args, compiled_patterns, args.pattern_count,
                      is_multiple_files) != 0) {
          exit_status = 1;
        }
      }
    }
  } else {
    exit_status = 1;
  }

  free_patterns(compiled_patterns, args.pattern_count);
  return exit_status;
}

void add_pattern(arguments *args, char *pattern) {
  if (args->pattern_count < MAX_PATTERNS) {
    strncpy(args->patterns[args->pattern_count], pattern,
            sizeof(args->patterns[args->pattern_count]) - 1);
    args->patterns[args->pattern_count]
                  [sizeof(args->patterns[args->pattern_count]) - 1] = '\0';
    args->pattern_count++;
  } else {
    fprintf(stderr, "Pattern limit reached\n");
  }
}

int process_arguments(int argc, char *argv[], arguments *args) {
  int status = 0;
  int opt;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1 && status == 0) {
    switch (opt) {
      case 'e':
        args->e = 1;
        add_pattern(args, optarg);
        break;
      case 'f':
        args->f = 1;
        if (load_patterns_from_file(optarg, args) != 0) {
          status = 1;
        }
        break;
      case 'i':
        args->i = 1;
        break;
      case 'v':
        args->v = 1;
        break;
      case 'c':
        args->c = 1;
        break;
      case 'l':
        args->l = 1;
        break;
      case 'n':
        args->n = 1;
        break;
      case 'h':
        args->h = 1;
        break;
      case 's':
        args->s = 1;
        break;
      case 'o':
        args->o = 1;
        break;
      default:
        fprintf(stderr, "Unknown option\n");
        status = 1;
        break;
    }
  }

  if (status == 0) {
    status = prioritet(argc, argv, args);
  }

  return status;
}

int prioritet(int argc, char *argv[], arguments *args) {
  int status = 0;
  if (args->l) {
    args->o = 0;
    args->n = 0;
    args->h = 1;
  }

  if (args->c) {
    args->o = 0;
    args->n = 0;
  }

  if (args->v && args->o) {
    fprintf(stderr, "Error: -v and -o flags are incompatible\n");
    status = 1;
  }

  if (args->pattern_count == 0 && optind < argc) {
    add_pattern(args, argv[optind++]);
  } else if (args->pattern_count == 0) {
    fprintf(stderr, "Error: No patterns provided\n");
    status = 1;
  }

  return status;
}

int load_patterns_from_file(char *filename, arguments *args) {
  FILE *file = fopen(filename, "r");
  int status = 0;

  if (file == NULL) {
    if (!args->s) {
      perror(filename);
    }
    status = 1;
  } else {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
      line[strcspn(line, "\n")] = '\0';
      add_pattern(args, line);
    }
    fclose(file);
  }

  return status;
}

int compile_patterns(arguments *args, regex_t compiled_patterns[]) {
  int flags = REG_EXTENDED | (args->i ? REG_ICASE : 0);
  int status = 0;

  for (int i = 0; i < args->pattern_count && status == 0; i++) {
    if (regcomp(&compiled_patterns[i], args->patterns[i], flags) != 0) {
      fprintf(stderr, "Error compiling regex: %s\n", args->patterns[i]);
      status = 1;
    }
  }

  return status;
}

int matches_any_pattern(char *line, regex_t compiled_patterns[], int count,
                        int v_flag, regmatch_t *match) {
  int is_match = 0;
  int i = 0;

  while (i < count && is_match == 0) {
    int status = regexec(&compiled_patterns[i], line, match ? 1 : 0, match, 0);
    if ((status == 0 && !v_flag) || (status == REG_NOMATCH && v_flag)) {
      is_match = 1;
    }
    i++;
  }

  return is_match;
}

void handle_flag_o(char *line, regex_t compiled_patterns[], int pattern_count,
                   arguments *args, char *filename, int line_number,
                   int is_multiple_files) {
  char *ptr = line;
  regmatch_t match;

  // Ищем совпадения для всех паттернов по очереди, двигаясь по строке
  // При нахождении совпадения выводим его и двигаемся дальше
  while (1) {
    int found = 0;
    for (int i = 0; i < pattern_count; i++) {
      if (regexec(&compiled_patterns[i], ptr, 1, &match, 0) == 0) {
        // Нашли совпадение
        found = 1;
        if (!args->h && is_multiple_files && filename) {
          printf("%s:", filename);
        }
        if (args->n) {
          printf("%d:", line_number);
        }
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), ptr + match.rm_so);
        // Сдвигаем указатель за пределы найденного совпадения
        ptr += match.rm_eo;
        break;
      }
    }
    if (!found) {
      // Больше совпадений нет
      break;
    }
  }
}

void grep_stream(FILE *stream, char *filename, arguments *args,
                 regex_t compiled_patterns[], int pattern_count,
                 int is_multiple_files) {
  char line[MAX_LINE_LENGTH];
  int line_number = 0;
  int match_count = 0;

  while (fgets(line, sizeof(line), stream)) {
    line_number++;
    int is_match = matches_any_pattern(line, compiled_patterns, pattern_count,
                                       args->v, NULL);

    if (args->l && is_match) {
      if (filename) {
        printf("%s\n", filename);
      }
      return;
    }

    if (args->c) {
      if (is_match) {
        match_count++;
      }
      continue;
    }

    if (is_match) {
      if (args->o && !args->v) {
        handle_flag_o(line, compiled_patterns, pattern_count, args, filename,
                      line_number, is_multiple_files);
      } else if (args->v) {
        // -v: выводим строки, не совпавшие ни с одним паттерном
        if (!args->h && is_multiple_files && filename) {
          printf("%s:", filename);
        }
        if (args->n) {
          printf("%d:", line_number);
        }
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') {
          printf("\n");
        }
      } else {
        // Обычный вывод совпавших строк
        if (!args->h && is_multiple_files && filename) {
          printf("%s:", filename);
        }
        if (args->n) {
          printf("%d:", line_number);
        }
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') {
          printf("\n");
        }
      }
    }
  }

  if (args->c && !args->l) {
    if (!args->h && is_multiple_files && filename) {
      printf("%s:", filename);
    }
    printf("%d\n", match_count);
  }
}

int grep_file(char *filename, arguments *args, regex_t compiled_patterns[],
              int pattern_count, int is_multiple_files) {
  FILE *file = fopen(filename, "r");
  int status = 0;

  if (file == NULL) {
    if (!args->s) {
      perror(filename);
    }
    status = 1;
  } else {
    grep_stream(file, filename, args, compiled_patterns, pattern_count,
                is_multiple_files);
    fclose(file);
  }

  return status;
}

void free_patterns(regex_t compiled_patterns[], int count) {
  for (int i = 0; i < count; i++) {
    regfree(&compiled_patterns[i]);
  }
}
