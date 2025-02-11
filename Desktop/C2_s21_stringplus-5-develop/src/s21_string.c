#include "s21_string.h"

#if defined(__linux__)
#define MAX_ERR 133
#define MIN_ERR 0
#define UNK_ERR "Unknown error "
static const char *err[] = {"Success",
                            "Operation not permitted",
                            "No such file or directory",
                            "No such process",
                            "Interrupted system call",
                            "Input/output error",
                            "No such device or address",
                            "Argument list too long",
                            "Exec format error",
                            "Bad file descriptor",
                            "No child processes",
                            "Resource temporarily unavailable",
                            "Cannot allocate memory",
                            "Permission denied",
                            "Bad address",
                            "Block device required",
                            "Device or resource busy",
                            "File exists",
                            "Invalid cross-device link",
                            "No such device",
                            "Not a directory",
                            "Is a directory",
                            "Invalid argument",
                            "Too many open files in system",
                            "Too many open files",
                            "Inappropriate ioctl for device",
                            "Text file busy",
                            "File too large",
                            "No space left on device",
                            "Illegal seek",
                            "Read-only file system",
                            "Too many links",
                            "Broken pipe",
                            "Numerical argument out of domain",
                            "Numerical result out of range",
                            "Resource deadlock avoided",
                            "File name too long",
                            "No locks available",
                            "Function not implemented",
                            "Directory not empty",
                            "Too many levels of symbolic links",
                            "Unknown error 41",
                            "No message of desired type",
                            "Identifier removed",
                            "Channel number out of range",
                            "Level 2 not synchronized",
                            "Level 3 halted",
                            "Level 3 reset",
                            "Link number out of range",
                            "Protocol driver not attached",
                            "No CSI structure available",
                            "Level 2 halted",
                            "Invalid exchange",
                            "Invalid request descriptor",
                            "Exchange full",
                            "No anode",
                            "Invalid request code",
                            "Invalid slot",
                            "Unknown error 58",
                            "Bad font file format",
                            "Device not a stream",
                            "No data available",
                            "Timer expired",
                            "Out of streams resources",
                            "Machine is not on the network",
                            "Package not installed",
                            "Object is remote",
                            "Link has been severed",
                            "Advertise error",
                            "Srmount error",
                            "Communication error on send",
                            "Protocol error",
                            "Multihop attempted",
                            "RFS specific error",
                            "Bad message",
                            "Value too large for defined data type",
                            "Name not unique on network",
                            "File descriptor in bad state",
                            "Remote address changed",
                            "Can not access a needed shared library",
                            "Accessing a corrupted shared library",
                            ".lib section in a.out corrupted",
                            "Attempting to link in too many shared libraries",
                            "Cannot exec a shared library directly",
                            "Invalid or incomplete multibyte or wide character",
                            "Interrupted system call should be restarted",
                            "Streams pipe error",
                            "Too many users",
                            "Socket operation on non-socket",
                            "Destination address required",
                            "Message too long",
                            "Protocol wrong type for socket",
                            "Protocol not available",
                            "Protocol not supported",
                            "Socket type not supported",
                            "Operation not supported",
                            "Protocol family not supported",
                            "Address family not supported by protocol",
                            "Address already in use",
                            "Cannot assign requested address",
                            "Network is down",
                            "Network is unreachable",
                            "Network dropped connection on reset",
                            "Software caused connection abort",
                            "Connection reset by peer",
                            "No buffer space available",
                            "Transport endpoint is already connected",
                            "Transport endpoint is not connected",
                            "Cannot send after transport endpoint shutdown",
                            "Too many references: cannot splice",
                            "Connection timed out",
                            "Connection refused",
                            "Host is down",
                            "No route to host",
                            "Operation already in progress",
                            "Operation now in progress",
                            "Stale file handle",
                            "Structure needs cleaning",
                            "Not a XENIX named type file",
                            "No XENIX semaphores available",
                            "Is a named type file",
                            "Remote I/O error",
                            "Disk quota exceeded",
                            "No medium found",
                            "Wrong medium type",
                            "Operation canceled",
                            "Required key not available",
                            "Key has expired",
                            "Key has been revoked",
                            "Key was rejected by service",
                            "Owner died",
                            "State not recoverable",
                            "Operation not possible due to RF-kill",
                            "Memory page has hardware error"};
#elif defined(__APPLE__)
#define MAX_ERR 106
#define MIN_ERR 0
#define UNK_ERR "Unknown error: "
static const char *err[] = {"Undefined error: 0",
                            "Operation not permitted",
                            "No such file or directory",
                            "No such process",
                            "Interrupted system call",
                            "Input/output error",
                            "Device not configured",
                            "Argument list too long",
                            "Exec format error",
                            "Bad file descriptor",
                            "No child processes",
                            "Resource deadlock avoided",
                            "Cannot allocate memory",
                            "Permission denied",
                            "Bad address",
                            "Block device required",
                            "Resource busy",
                            "File exists",
                            "Cross-device link",
                            "Operation not supported by device",
                            "Not a directory",
                            "Is a directory",
                            "Invalid argument",
                            "Too many open files in system",
                            "Too many open files",
                            "Inappropriate ioctl for device",
                            "Text file busy",
                            "File too large",
                            "No space left on device",
                            "Illegal seek",
                            "Read-only file system",
                            "Too many links",
                            "Broken pipe",
                            "Numerical argument out of domain",
                            "Result too large",
                            "Resource temporarily unavailable",
                            "Operation now in progress",
                            "Operation already in progress",
                            "Socket operation on non-socket",
                            "Destination address required",
                            "Message too long",
                            "Protocol wrong type for socket",
                            "Protocol not available",
                            "Protocol not supported",
                            "Socket type not supported",
                            "Operation not supported",
                            "Protocol family not supported",
                            "Address family not supported by protocol family",
                            "Address already in use",
                            "Can't assign requested address",
                            "Network is down",
                            "Network is unreachable",
                            "Network dropped connection on reset",
                            "Software caused connection abort",
                            "Connection reset by peer",
                            "No buffer space available",
                            "Socket is already connected",
                            "Socket is not connected",
                            "Can't send after socket shutdown",
                            "Too many references: can't splice",
                            "Operation timed out",
                            "Connection refused",
                            "Too many levels of symbolic links",
                            "File name too long",
                            "Host is down",
                            "No route to host",
                            "Directory not empty",
                            "Too many processes",
                            "Too many users",
                            "Disc quota exceeded",
                            "Stale NFS file handle",
                            "Too many levels of remote in path",
                            "RPC struct is bad",
                            "RPC version wrong",
                            "RPC prog. not avail",
                            "Program version wrong",
                            "Bad procedure for program",
                            "No locks available",
                            "Function not implemented",
                            "Inappropriate file type or format",
                            "Authentication error",
                            "Need authenticator",
                            "Device power is off",
                            "Device error",
                            "Value too large to be stored in data type",
                            "Bad executable (or shared library)",
                            "Bad CPU type in executable",
                            "Shared library version mismatch",
                            "Malformed Mach-o file",
                            "Operation canceled",
                            "Identifier removed",
                            "No message of desired type",
                            "Illegal byte sequence",
                            "Attribute not found",
                            "Bad message",
                            "EMULTIHOP (Reserved)",
                            "No message available on STREAM",
                            "ENOLINK (Reserved)",
                            "No STREAM resources",
                            "Not a STREAM",
                            "Protocol error",
                            "STREAM ioctl timeout",
                            "Operation not supported on socket",
                            "Policy not found",
                            "State not recoverable",
                            "Previous owner died",
                            "Interface output queue is full"};
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *res = S21_NULL;
  unsigned char d = (unsigned char)c;
  unsigned char *poi = (unsigned char *)str;
  int br_fl = 0;
  for (s21_size_t i = 0; i < n && br_fl == 0; i++) {
    if (poi[i] == d) {
      res = &poi[i];
      br_fl = 1;
    }
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  const unsigned char *poi1 = (const unsigned char *)str1;
  const unsigned char *poi2 = (const unsigned char *)str2;
  int br_fl = 0;
  for (s21_size_t i = 0; i < n && br_fl == 0; i++) {
    if (poi1[i] != poi2[i]) {
      res = poi1[i] - poi2[i];
      br_fl = 1;
    }
  }
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char value = (unsigned char)c;

  for (s21_size_t i = 0; i < n; i++) {
    s[i] = value;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t len = 0;
  s21_size_t i = 0;
  while (dest[len] != '\0') {
    len++;
  }
  for (; i < n && src[i] != '\0'; i++) {
    dest[len + i] = src[i];
  }
  dest[len + i] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  const char d = (char)c;
  while (*str && *str != d) {
    str++;
  }
  if (*str == 0 && d) {
    str = S21_NULL;
  }
  return (char *)str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  int br_fl = 0;
  for (s21_size_t i = 0; i < n && br_fl == 0; i++) {
    if (str1[i] != str2[i]) {
      res = (int)(str1[i] - str2[i]);
      br_fl = 1;
    }
  }
  return res;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    dest[i] = src[i];
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  s21_size_t leng_one = s21_strlen(str1);
  s21_size_t leng_two = s21_strlen(str2);
  int br_fl = 0;

  while (br_fl == 0 && res < leng_one) {
    s21_size_t i = 0;
    while (br_fl == 0 && i < leng_two) {
      if (str1[res] == str2[i]) {
        br_fl = 1;
      }
      i++;
    }
    if (br_fl == 0) {
      res++;
    }
  }
  return res;
}

char errormes[64];

char *s21_strerror(int errnum) {
  if (errnum >= MIN_ERR && errnum <= MAX_ERR) {
    s21_strcpy(errormes, err[errnum]);
  } else {
    s21_strcpy(errormes, UNK_ERR);
    s21_size_t i = s21_strlen(UNK_ERR);
    int num_size = get_size(errnum);
    if (errnum < 0) {
      errormes[i] = '-';
      errnum = -errnum;
      i++;
    }
    long int dec = 10;
    for (int j = 1; j < num_size; j++) {
      dec = dec * 10;
    }
    for (int l = 0; l < num_size; l++) {
      dec = dec / 10;
      errormes[i] = (errnum / dec) + '0';
      errnum = errnum - dec * (errormes[i] - '0');
      i++;
    }
    errormes[i] = '\0';
  }

  return errormes;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t res = 0;
  while (str[res]) {
    res++;
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t leng_one = s21_strlen(str1);
  s21_size_t leng_two = s21_strlen(str2);
  char *res = S21_NULL;
  int br_fl = 0;

  for (s21_size_t i = 0; i < leng_one && br_fl == 0; i++) {
    for (s21_size_t j = 0; j < leng_two && br_fl == 0; j++) {
      if (str1[i] == str2[j]) {
        res = (char *)&str1[i];
        br_fl = 1;
      }
    }
  }

  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  s21_size_t leng = s21_strlen(str) + 1;
  char d = (char)c;

  for (s21_size_t i = 0; i < leng; i++) {
    if (str[i] == d) {
      res = (char *)&str[i];
    }
  }

  return res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  int br_main = 0, br_sub = 0;
  s21_size_t leng_main = s21_strlen(haystack);
  s21_size_t leng_sub = s21_strlen(needle);

  for (s21_size_t i = 0; i < leng_main && br_main == 0; i++) {
    if (haystack[i] == needle[0]) {
      for (s21_size_t j = 1; j < leng_sub && br_sub == 0; j++) {
        (haystack[i + j] != needle[j]) ? br_sub = 1 : br_sub;
      }
      if (br_sub == 0) {
        res = (char *)&haystack[i];
        br_main = 1;
      } else {
        br_sub = 0;
      }
    }
  }
  if (needle[0] == '\0') {
    res = (char *)&haystack[0];
  }
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *buffer;
  if (str) {
    buffer = str;
  }
  while (buffer && *buffer && s21_strchr(delim, *buffer)) {
    buffer++;
  }
  s21_size_t next_buff_offset = 0;
  int delim_found = 0;
  for (s21_size_t i = 0; !delim_found && buffer && buffer[i]; i++) {
    if (s21_strchr(delim, buffer[i])) {
      delim_found = 1;
      buffer[i] = 0;
      next_buff_offset = i;
    }
  }
  if (!delim_found) {
    next_buff_offset = s21_strlen(buffer);
  }
  char *to_return = buffer;
  if (buffer && *buffer) {
    buffer = buffer + next_buff_offset;
    if (delim_found) {
      buffer++;
    }
  }
  if (to_return && !*to_return) {
    to_return = S21_NULL;
  }
  return to_return;
}

void *s21_to_upper(const char *str) {
  s21_size_t leng = s21_strlen(str);
  char *res = malloc(leng + 1);
  if (res != S21_NULL) {
    for (s21_size_t i = 0; i != leng; ++i) {
      char c = str[i];
      if (c >= 'a' && c <= 'z') {
        c = c - 32;
      }
      res[i] = c;
    }
    res[leng] = 0;
  }
  return res;
}

void *s21_to_lower(const char *str) {
  s21_size_t leng = s21_strlen(str);
  char *res = malloc(leng + 1);
  if (res != S21_NULL) {
    for (s21_size_t i = 0; i != leng; ++i) {
      char c = str[i];
      if (c >= 'A' && c <= 'Z') {
        c = c + 32;
      }
      res[i] = c;
    }
    res[leng] = 0;
  }
  return res;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *res = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_leng = s21_strlen(src) + 1;
    s21_size_t str_leng = s21_strlen(str);

    char temp[src_leng];

    res = calloc(src_leng + str_leng, sizeof(char));

    for (s21_size_t i = 0; i < start_index; i++) {
      res[i] = src[i];
    }
    s21_strcpy(temp, &src[start_index]);
    s21_strcpy(&res[start_index], str);
    s21_strcpy(&res[start_index + str_leng], temp);
  } else if (str == S21_NULL && src != S21_NULL) {
    res = calloc(s21_strlen(src) + 1, sizeof(char));
    s21_size_t len_src = s21_strlen(src);
    s21_strncpy(res, src, len_src);
    res[len_src + 1] = '\0';
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;
  int br_main = 0, br_sub = 0;
  int src_leng = (int)s21_strlen(src);
  s21_size_t l = 0, r = 0;
  s21_size_t trim_leng = s21_strlen(trim_chars);

  for (int i = 0; i < src_leng && br_main == 0; i++) {
    br_sub = 0;
    for (s21_size_t j = 0; j < trim_leng && br_sub == 0; j++) {
      if (src[i] == trim_chars[j]) {
        br_sub = 1;
        l++;
      }
    }
    if (br_sub == 0) {
      br_main = 1;
    }
  }
  br_main = 0;
  for (int m = src_leng - 1; m >= 0 && br_main == 0; m--) {
    br_sub = 0;
    for (s21_size_t n = 0; n < trim_leng && br_sub == 0; n++) {
      if (src[m] == trim_chars[n]) {
        br_sub = 1;
        r++;
      }
    }
    if (br_sub == 0) {
      br_main = 1;
    }
  }
  res = (char *)malloc(src_leng + 1);
  if (trim_leng == 0 || src_leng == 0) {
    s21_strcpy(res, src);
  } else if (src_leng - l - r > 0) {
    s21_size_t f;
    for (f = 0; f + l < src_leng - r; f++) {
      res[f] = src[f + l];
    }
    res[f] = '\0';
  }
  return res;
}