#include "s21_string.h"

typedef struct {
  int plus;
  int minus;
  int space;
  int length;
  int percision;
  int shor;
  int lon;
  int str_len;
  char type;
} NiceTry;

void flagger_refresh(NiceTry *flagger);
int param_check(NiceTry *flagger, const char *str, int *err_fl);
void plmnsp_check(NiceTry *flagger, const char *str, int *i, int *br_fl);
void get_word(const char *str, char *num, int *i, int str_len);
int get_num(const char *num, int leng);
void strinsstr(NiceTry flagger, va_list *arges, char *str, int sympos,
               int *err_fl);
int get_usize(long unsigned num);
int sscanf(const char *str, const char *format, ...);
void int_to_char(NiceTry flagger, char *str, long int arg, int num_size,
                 int str_size);
void float_to_char(NiceTry flagger, char *str, double arg, int num_size);
void uint_to_char(NiceTry flagger, char *str, long unsigned arg, int num_size,
                  int str_size);
int char_prep(NiceTry flagger, char *str, char arg);
int int_prep(NiceTry flagger, char *str, long int arg, int *err_fl);
int float_prep(NiceTry flagger, char *str, double arg);
int str_prep(NiceTry flagger, char *str, const char *arg);
int uns_prep(NiceTry flagger, char *str, long unsigned arg, int *err_fl);
double cooler_round(double num, int perc);

int s21_sprintf(char *str, const char *format, ...) {
  int res = 0;

  s21_strcpy(str, format);

  NiceTry flagger;
  va_list arges;
  va_start(arges, format);
  s21_size_t i = 0;
  while (i < s21_strlen(str) && res >= 0) {
    if (str[i] == '%') {
      flagger_refresh(&flagger);
      flagger.str_len = s21_strlen(&str[i]) + 1;
      int sympos = param_check(&flagger, &str[i], &res);
      if (res >= 0) {
        strinsstr(flagger, &arges, &str[i], sympos, &res);
      }
    }
    i++;
  }

  va_end(arges);
  if (res >= 0) {
    res = s21_strlen(str);
  }
  return res;
}

void flagger_refresh(NiceTry *flagger) {
  flagger->plus = 0;
  flagger->minus = 0;
  flagger->space = 0;
  flagger->length = 0;
  flagger->percision = 0;
  flagger->shor = 0;
  flagger->lon = 0;
  flagger->str_len = 0;
  flagger->type = '0';
}

int param_check(NiceTry *flagger, const char *str, int *res) {
  int br_fl = 0;
  int i = 1;

  for (; i < flagger->str_len && br_fl == 0; i++) {
    plmnsp_check(flagger, str, &i, &br_fl);
  }

  char numOne[11];
  get_word(str, numOne, &i, flagger->str_len);

  int leng = s21_strlen(numOne);
  if (leng > 0) {
    flagger->length = get_num(numOne, leng);
  }

  if (str[i] == '.') {
    char numTwo[11];
    i++;
    get_word(str, numTwo, &i, flagger->str_len);
    leng = s21_strlen(numTwo);
    if (leng > 0) {
      flagger->percision = get_num(numTwo, leng);
    }
  }

  if (str[i] == 'h') {
    flagger->shor = 1;
    i++;
  } else if (str[i] == 'l') {
    flagger->lon = 1;
    i++;
  }

  if (*res >= 0) {
    if (str[i] == 'c' || str[i] == 'd' || str[i] == 'f' || str[i] == 's' ||
        str[i] == 'u' || str[i] == '%') {
      flagger->type = str[i];
    } else {
      *res = -1;
    }
  }
  return i;
}

void plmnsp_check(NiceTry *flagger, const char *str, int *i, int *br_fl) {
  switch (str[*i]) {
    case '+':
      flagger->plus = 1;
      break;
    case '-':
      flagger->minus = 1;
      break;
    case ' ':
      flagger->space = 1;
      break;
    default:
      *br_fl = 1;
      (*i)--;
  }
}

void get_word(const char *str, char *num, int *i, int str_len) {
  int numPos = 0;
  int br_fl = 0;
  for (*i = *i; *i < str_len && br_fl == 0; (*i)++) {
    if (str[*i] >= 48 && str[*i] <= 57) {
      num[numPos] = str[*i];
      numPos++;
    } else {
      num[numPos] = '\0';
      br_fl = 1;
      (*i)--;
    }
  }
}

int get_num(const char *num, int leng) {
  int res = 0;
  int ten = 1;
  for (int i = leng - 1; i >= 0; i--) {
    res = res + (num[i] - '0') * ten;
    ten = ten * 10;
  }
  return res;
}

void strinsstr(NiceTry flagger, va_list *arges, char *str, int sympos,
               int *res) {
  char temp[flagger.str_len];
  int inspos = 0;
  s21_strcpy(temp, &str[sympos + 1]);
  s21_memset(str, 0, sympos);

  switch (flagger.type) {
    case 'c':
      inspos = char_prep(flagger, str, (char)va_arg(*arges, int));
      break;
    case 'd':
      inspos = int_prep(
          flagger, str,
          (flagger.lon == 0) ? va_arg(*arges, int) : va_arg(*arges, long int),
          res);
      break;
    case 'f':
      inspos = float_prep(flagger, str, va_arg(*arges, double));
      break;
    case 's':
      inspos = str_prep(flagger, str, va_arg(*arges, char *));
      break;
    case 'u':
      inspos = uns_prep(flagger, str, va_arg(*arges, long unsigned), res);
      break;
    case '%':
      str[inspos] = '%';
      inspos++;
      break;
  }
  if (*res >= 0) {
    s21_strcpy(&str[inspos], temp);
    *res = inspos;
  }
}

int get_size(long int num) {
  int res = 1;
  if (num < 0) {
    num = -num;
  }
  while (num > 9) {
    num = num / 10;
    res++;
  }
  return res;
}

int get_usize(long unsigned num) {
  int res = 1;
  while (num > 9) {
    num = num / 10;
    res++;
  }
  return res;
}

int sscanf(const char *str, const char *format, ...) {
  s21_strlen(str);
  s21_strlen(format);
  return 0;
}

void int_to_char(NiceTry flagger, char *str, long int arg, int num_size,
                 int str_size) {
  long int dec = 10;
  for (int i = 1; i < num_size; i++) {
    dec = dec * 10;
  }

  int j = 0;
  if (arg < 0) {
    str[j] = '-';
    j++;
    arg = -arg;
  } else if (flagger.plus) {
    str[j] = '+';
    j++;
  } else if (flagger.space) {
    str[j] = ' ';
    j++;
  }
  for (; j < str_size - num_size; j++) {
    str[j] = '0';
  }
  for (int l = 0; l < num_size; l++) {
    dec = dec / 10;
    str[j] = (arg / dec) + '0';
    arg = arg - dec * (str[j] - '0');
    j++;
  }
}

void float_to_char(NiceTry flagger, char *str, double arg, int num_size) {
  long int dec = 10;
  long int int_arg = (long int)arg;
  arg = arg - int_arg;
  for (int i = 1; i < num_size; i++) {
    dec = dec * 10;
  }
  int j = 0;
  if (arg < 0) {
    str[j] = '-';
    j++;
    arg = -arg;
  } else if (flagger.plus) {
    str[j] = '+';
    j++;
  } else if (flagger.space) {
    str[j] = ' ';
    j++;
  }

  for (int l = 0; l < num_size; l++) {
    dec = dec / 10;
    str[j] = (int_arg / dec) + '0';
    int_arg = int_arg - dec * (str[j] - '0');
    j++;
  }
  str[j] = '.';
  j++;
  dec = 10;
  for (int k = 1; k < flagger.percision; k++) {
    dec = dec * 10;
  }
  int_arg = round(arg * dec);

  for (int l = 0; l < flagger.percision; l++) {
    dec = dec / 10;
    str[j] = (int_arg / dec) + '0';
    int_arg = int_arg - dec * (str[j] - '0');
    j++;
  }
  for (; j < num_size + flagger.percision + 1; j++) {
    str[j] = '0';
  }
}

void uint_to_char(NiceTry flagger, char *str, long unsigned arg, int num_size,
                  int str_size) {
  long unsigned dec = 10;
  for (int i = 1; i < num_size; i++) {
    dec = dec * 10;
  }

  if (str_size >= num_size) {
    int j = 0;
    if (flagger.plus) {
      str[j] = '+';
      j++;
    } else if (flagger.space) {
      str[j] = ' ';
      j++;
    }
    for (; j < str_size - num_size; j++) {
      str[j] = '0';
    }
    for (int l = 0; l < num_size; l++) {
      dec = dec / 10;
      str[j] = (arg / dec) + '0';
      arg = arg - dec * (str[j] - '0');
      j++;
    }
  }
}

int char_prep(NiceTry flagger, char *str, char arg) {
  int i = 0;
  if (flagger.length > 0) {
    if (flagger.minus) {
      str[i] = arg;
      for (i = 1; i < flagger.length; i++) {
        str[i] = ' ';
      }
    } else {
      for (i = 0; i < flagger.length - 1; i++) {
        str[i] = ' ';
      }
      str[flagger.length - 1] = arg;
      i++;
    }
  } else {
    str[i] = arg;
    i++;
  }

  return i;
}

int int_prep(NiceTry flagger, char *str, long int arg, int *res) {
  int i = 0;
  if (flagger.lon == 0 && (arg < INT_MIN || arg > INT_MAX)) {
    *res = -1;
  } else {
    int num_size = get_size(arg);
    int temp_size =
        ((flagger.percision > num_size) ? flagger.percision : num_size) +
        ((arg < 0 || flagger.plus || flagger.space) ? 1 : 0);
    char temp[temp_size];
    int_to_char(flagger, temp, arg, num_size, temp_size);

    if (flagger.minus) {
      for (; i < temp_size; i++) {
        str[i] = temp[i];
      }
      for (; i < flagger.length; i++) {
        str[i] = ' ';
      }
    } else {
      for (; i < flagger.length - temp_size; i++) {
        str[i] = ' ';
      }
      for (int l = 0; l < temp_size; l++) {
        str[i] = temp[l];
        i++;
      }
    }
  }
  return i;
}

int float_prep(NiceTry flagger, char *str, double arg) {
  int i = 0;
  if (flagger.percision == 0) {
    flagger.percision = 6;
  }

  arg = cooler_round(arg, flagger.percision);
  int num_size = get_size(arg);
  int temp_size = num_size + flagger.percision + 1 +
                  ((arg < 0 || flagger.plus || flagger.space) ? 1 : 0);
  char temp[temp_size];
  float_to_char(flagger, temp, arg, num_size);
  if (flagger.minus) {
    for (; i < temp_size; i++) {
      str[i] = temp[i];
    }
    for (; i < flagger.length - temp_size; i++) {
      str[i] = ' ';
    }
  } else {
    for (; i < flagger.length - temp_size; i++) {
      str[i] = ' ';
    };
    for (int l = 0; l < temp_size; l++) {
      str[i] = temp[l];
      i++;
    }
  }

  return i;
}

int str_prep(NiceTry flagger, char *str, const char *arg) {
  int i = 0;
  int leng = s21_strlen(arg);
  if (flagger.percision > 0 && flagger.percision < leng) {
    leng = flagger.percision;
  }
  char temp[leng];
  s21_strncpy(temp, arg, leng);

  if (flagger.length < leng) {
    flagger.length = leng;
  }

  if (flagger.minus) {
    for (; i < leng; i++) {
      str[i] = temp[i];
    }
    for (; i < flagger.length; i++) {
      str[i] = ' ';
    }
  } else {
    for (; i < flagger.length - leng; i++) {
      str[i] = ' ';
    }
    int l = 0;
    for (; i < flagger.length; i++) {
      str[i] = temp[l];
      l++;
    }
  }

  return i;
}

int uns_prep(NiceTry flagger, char *str, long unsigned arg, int *res) {
  int i = 0;
  if (flagger.lon == 0 && arg > UINT_MAX) {
    *res = -1;
  } else {
    int num_size = get_usize(arg);
    int temp_size =
        ((flagger.percision > num_size) ? flagger.percision : num_size) +
        ((flagger.plus || flagger.space) ? 1 : 0);
    char temp[temp_size];
    uint_to_char(flagger, temp, arg, num_size, temp_size);

    if (flagger.minus) {
      for (; i < temp_size; i++) {
        str[i] = temp[i];
      }
      for (; i < flagger.length; i++) {
        str[i] = ' ';
      }
    } else {
      for (; i < flagger.length - temp_size; i++) {
        str[i] = ' ';
      }
      for (int l = 0; l < temp_size; l++) {
        str[i] = temp[l];
        i++;
      }
    }
  }
  return i;
}

double cooler_round(double num, int perc) {
  long int dec = 1;
  for (int i = 1; i < perc; i++) {
    dec = dec * 10;
  }
  return round(num * dec) / dec;
}

char *s21_strcpy(char *destination, const char *source) {
  s21_size_t i;
  s21_size_t leng = s21_strlen(source);
  for (i = 0; i < leng && source[i] != '\0'; i++) {
    destination[i] = source[i];
  }
  if (source[i] == '\0') {
    destination[i] = '\0';
  }
  return destination;
}