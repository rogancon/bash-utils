#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

Suite *s21_sprintf_suite(void);

int main(void) {
  int number_failed;
  SRunner *sr = srunner_create(s21_sprintf_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

START_TEST(test_s21_memchr) {
  char str[] = "Hello, world!";
  int ints[] = {9, 5, 4, 3, 5, 7};
  int c = 'o';
  size_t n = 5;

  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
  ck_assert_ptr_eq(s21_memchr(str, 'x', n), memchr(str, 'x', n));
  ck_assert_ptr_eq(s21_memchr(ints, 4, n), memchr(ints, 4, n));
  ck_assert_ptr_eq(s21_memchr(ints, 10, n), memchr(ints, 10, n));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char str_one[] = "abcdef";
  char str_two[] = "abcdeg";
  int ints1[] = {4, 3, 7, 12, 55, 33};
  int ints2[] = {4, 3, 7, 3, 55, 33};
  size_t n = 5;

  ck_assert_int_eq(s21_memcmp(str_one, str_two, n),
                   memcmp(str_one, str_two, n));
  ck_assert_int_eq(s21_memcmp(str_one, str_one, n),
                   memcmp(str_one, str_one, n));
  ck_assert_int_eq(s21_memcmp(ints1, ints2, n), memcmp(ints1, ints2, n));
  ck_assert_int_eq(s21_memcmp(ints1, ints1, n), memcmp(ints1, ints1, n));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char src[] = "Hello, world!";
  char dest_one[20] = "";
  char std_dest_one[20] = "";
  char dest_two[20] = "";
  char std_dest_two[20] = "";

  s21_memcpy(dest_one, src, s21_strlen(src) + 1);
  memcpy(std_dest_one, src, strlen(src) + 1);
  s21_memcpy(dest_two, src, 5);
  memcpy(std_dest_two, src, 5);

  ck_assert_str_eq(dest_one, std_dest_one);
  ck_assert_str_eq(dest_two, std_dest_two);
}
END_TEST

START_TEST(test_s21_memset) {
  char str_one[20] = "Hello, world!";
  char std_str_one[20] = "Hello, world!";
  int c = 'x';
  char str_two[20] = "Hello, world!";
  char std_str_two[20] = "Hello, world!";
  int d = '\0';

  s21_memset(str_one, c, 5);
  memset(std_str_one, c, 5);
  s21_memset(str_two, d, s21_strlen(str_two));
  memset(std_str_two, d, s21_strlen(std_str_two));

  ck_assert_str_eq(str_one, std_str_one);
  ck_assert_str_eq(str_two, std_str_two);
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest_one[20] = "Hello, ";
  char std_dest_one[20] = "Hello, ";
  char dest_two[20] = "";
  char std_dest_two[20] = "";
  char src[] = "world!";

  s21_strncat(dest_one, src, 3);
  strncat(std_dest_one, src, 3);
  s21_strncat(dest_two, src, 0);
  strncat(std_dest_two, src, 0);

  ck_assert_str_eq(dest_one, std_dest_one);
  ck_assert_str_eq(dest_two, std_dest_two);
}
END_TEST

START_TEST(test_s21_strchr_empty) {
  const char *str = "";
  const char key = 'c';
  ck_assert_ptr_eq(s21_strchr(str, key), strchr(str, key));
}
END_TEST

START_TEST(test_s21_strchr_empty_nullterm) {
  const char *str = "";
  const char key = 0;
  ck_assert_ptr_eq(s21_strchr(str, key), strchr(str, key));
}
END_TEST

START_TEST(test_s21_strchr_short_first) {
  const char *str = "abc";
  const char key = 'a';
  ck_assert_ptr_eq(s21_strchr(str, key), strchr(str, key));
}
END_TEST

START_TEST(test_s21_strchr_short_last) {
  const char *str = "abc";
  const char key = 'c';
  ck_assert_ptr_eq(s21_strchr(str, key), strchr(str, key));
}
END_TEST

START_TEST(test_s21_strchr_short_absent) {
  const char *str = "abc";
  const char key = 'd';
  ck_assert_ptr_eq(s21_strchr(str, key), strchr(str, key));
}
END_TEST

START_TEST(test_s21_strchr_short_nullterm) {
  const char *str = "abc";
  const char key = 0;
  ck_assert_ptr_eq(s21_strchr(str, key), strchr(str, key));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char str_one[] = "abcdef";
  char str_two[] = "abcdeg";
  char str_three[] = "\0";
  char str_four[] = " ";
  size_t n = 5;

  ck_assert_int_eq(s21_strncmp(str_one, str_two, n),
                   strncmp(str_one, str_two, n));
  ck_assert_int_eq(s21_strncmp(str_one, str_one, n),
                   strncmp(str_one, str_one, n));
  ck_assert_int_eq(s21_strncmp(str_three, str_four, 1),
                   strncmp(str_three, str_four, 1));
  ck_assert_int_eq(s21_strncmp(str_three, str_three, n),
                   strncmp(str_three, str_three, n));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char src[] = "Hello, world!";
  char dest_one[20] = "";
  char std_dest_one[20] = "";
  char dest_two[20] = "";
  char std_dest_two[20] = "";

  s21_strncpy(dest_one, src, 5);
  strncpy(std_dest_one, src, 5);
  s21_strncpy(dest_two, src, s21_strlen(src) + 1);
  strncpy(std_dest_two, src, strlen(src) + 1);

  ck_assert_str_eq(dest_one, std_dest_one);
  ck_assert_str_eq(dest_two, std_dest_two);
}
END_TEST

START_TEST(test_s21_strcspn) {
  char str_one[] = "abcdef";
  char str_two[] = "xyz";
  char str_three[] = "";

  ck_assert_int_eq(s21_strcspn(str_one, str_two), strcspn(str_one, str_two));
  ck_assert_int_eq(s21_strcspn(str_one, "cd"), strcspn(str_one, "cd"));
  ck_assert_int_eq(s21_strcspn(str_one, str_three),
                   strcspn(str_one, str_three));
  ck_assert_int_eq(s21_strcspn(str_three, str_one),
                   strcspn(str_three, str_one));
}
END_TEST

START_TEST(test_s21_strerror) {
  for (int i = -2; i < 150; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_s21_strlen) {
  char str_one[] = "Hello, world!";
  char str_two[] = "";
  char str_three[] = "\0";

  ck_assert_int_eq(s21_strlen(str_one), strlen(str_one));
  ck_assert_int_eq(s21_strlen(str_two), strlen(str_two));
  ck_assert_int_eq(s21_strlen(str_three), strlen(str_three));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  char str_one[] = "abcdef";
  char str_two[] = "xyz";
  char str_three[] = "";

  ck_assert_int_eq(s21_strcspn(str_one, str_two), strcspn(str_one, str_two));
  ck_assert_int_eq(s21_strcspn(str_one, "cd"), strcspn(str_one, "cd"));
  ck_assert_int_eq(s21_strcspn(str_one, str_three),
                   strcspn(str_one, str_three));
  ck_assert_int_eq(s21_strcspn(str_three, str_one),
                   strcspn(str_three, str_one));
}
END_TEST

START_TEST(test_s21_strrchr_empty) {
  const char *str = "";
  const char key = 'c';
  ck_assert_ptr_eq(s21_strrchr(str, key), strrchr(str, key));
}
END_TEST

START_TEST(test_s21_strrchr_empty_nullterm) {
  const char *str = "";
  const char key = 0;
  ck_assert_ptr_eq(s21_strrchr(str, key), strrchr(str, key));
}
END_TEST

START_TEST(test_s21_strrchr_short_first) {
  const char *str = "abc";
  const char key = 'a';
  ck_assert_ptr_eq(s21_strrchr(str, key), strrchr(str, key));
}
END_TEST

START_TEST(test_s21_strrchr_short_last) {
  const char *str = "abc";
  const char key = 'c';
  ck_assert_ptr_eq(s21_strrchr(str, key), strrchr(str, key));
}
END_TEST

START_TEST(test_s21_strrchr_short_absent) {
  const char *str = "abc";
  const char key = 'd';
  ck_assert_ptr_eq(s21_strrchr(str, key), strrchr(str, key));
}
END_TEST

START_TEST(test_s21_strrchr_short_nullterm) {
  const char *str = "abc";
  const char key = 0;
  ck_assert_ptr_eq(s21_strrchr(str, key), strrchr(str, key));
}
END_TEST

START_TEST(test_s21_strstr) {
  char haystack[] = "Hello, world!";
  char needle[] = "world";

  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  ck_assert_ptr_eq(s21_strstr(haystack, "xyz"), strstr(haystack, "xyz"));
  ck_assert_ptr_eq(s21_strstr(haystack, ""), strstr(haystack, ""));
}
END_TEST

START_TEST(test_s21_strtok_empty_both) {
  char str_i[] = "";
  char str_f[] = "";
  const char *delim = "";
  ck_assert_pstr_eq(s21_strtok(str_i, delim), strtok(str_f, delim));
  for (int i = 0; i < 30; ++i) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

START_TEST(test_s21_strtok_empty_delim) {
  char str_i[] = "abcdef";
  char str_f[] = "abcdef";
  const char *delim = "";
  ck_assert_pstr_eq(s21_strtok(str_i, delim), strtok(str_f, delim));
  for (int i = 0; i < 30; ++i) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

START_TEST(test_s21_strtok_empty_str) {
  char str_i[] = "";
  char str_f[] = "";
  const char *delim = ",./";
  ck_assert_pstr_eq(s21_strtok(str_i, delim), strtok(str_f, delim));
  for (int i = 0; i < 30; ++i) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

START_TEST(test_s21_strtok_short_every_char) {
  char str_i[] = "abccbbccccbaa";
  char str_f[] = "abccbbccccbaa";
  const char *delim = "abc";
  ck_assert_pstr_eq(s21_strtok(str_i, delim), strtok(str_f, delim));
  for (int i = 0; i < 30; ++i) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

START_TEST(test_s21_strtok_short_every_other_char) {
  char str_i[] = "a.b,c/d,e.f.g/d.";
  char str_f[] = "a.b,c/d,e.f.g/d.";
  const char *delim = "./,";
  ck_assert_pstr_eq(s21_strtok(str_i, delim), strtok(str_f, delim));
  for (int i = 0; i < 30; i++) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

START_TEST(test_s21_strtok_second_buffer_after_draining) {
  const char *delim = "./,";
  char str1_i[] = "a.b,c/d,e.f.g/d.";
  char str1_f[] = "a.b,c/d,e.f.g/d.";
  ck_assert_pstr_eq(s21_strtok(str1_i, delim), strtok(str1_f, delim));
  for (int i = 0; i < 30; ++i) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
  char str2_i[] = "aa,bb.cd./vd.vd//";
  char str2_f[] = "aa,bb.cd./vd.vd//";
  ck_assert_pstr_eq(s21_strtok(str2_i, delim), strtok(str2_f, delim));
  for (int i = 0; i < 30; ++i) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

START_TEST(test_s21_strtok_second_buffer_right_away) {
  const char *delim = "./,";
  char str1_i[] = "a.b,c/d,e.f.g/d.";
  char str1_f[] = "a.b,c/d,e.f.g/d.";
  ck_assert_pstr_eq(s21_strtok(str1_i, delim), strtok(str1_f, delim));
  char str2_i[] = "aa,bb.cd./vd.vd//";
  char str2_f[] = "aa,bb.cd./vd.vd//";
  ck_assert_pstr_eq(s21_strtok(str2_i, delim), strtok(str2_f, delim));
  for (int i = 0; i < 30; ++i) {
    ck_assert_pstr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  const char *str = "";
  const char *expected = "";
  char *actual = s21_to_lower(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_to_lower_short_no_upper) {
  const char *str = "abc123def*/xz";
  const char *expected = "abc123def*/xz";
  char *actual = s21_to_lower(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_to_lower_short_only_upper) {
  const char *str = "ABCDEFGXYZ";
  const char *expected = "abcdefgxyz";
  char *actual = s21_to_lower(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_to_lower_short_mixed) {
  const char *str = "AaBbCcDd//--000XxYyZZzz";
  const char *expected = "aabbccdd//--000xxyyzzzz";
  char *actual = s21_to_lower(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  const char *str = "";
  const char *expected = "";
  char *actual = s21_to_upper(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_to_upper_short_no_lower) {
  const char *str = "ABC123DEF*/XZ";
  const char *expected = "ABC123DEF*/XZ";
  char *actual = s21_to_upper(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_to_upper_short_only_lower) {
  const char *str = "abcdefgxyz";
  const char *expected = "ABCDEFGXYZ";
  char *actual = s21_to_upper(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_to_upper_short_mixed) {
  const char *str = "AaBbCcDd//--000XxYyZZzz";
  const char *expected = "AABBCCDD//--000XXYYZZZZ";
  char *actual = s21_to_upper(str);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_both_empty) {
  const char *src = "";
  const char *str = "";
  const size_t index = 0;
  const char *expected = "";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_src_empty) {
  const char *src = "";
  const char *str = "123321";
  const size_t index = 0;
  const char *expected = "123321";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_str_empty_start) {
  const char *src = "123321";
  const char *str = "";
  const size_t index = 0;
  const char *expected = "123321";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_str_empty_end) {
  const char *src = "123321";
  const char *str = "";
  const size_t index = 6;
  const char *expected = "123321";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_str_empty_arbitrary) {
  const char *src = "123312";
  const char *str = "";
  const size_t index = 3;
  const char *expected = "123312";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_one_char_start) {
  const char *src = "123321";
  const char *str = "a";
  const size_t index = 0;
  const char *expected = "a123321";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_one_char_end) {
  const char *src = "123321";
  const char *str = "a";
  const size_t index = 6;
  const char *expected = "123321a";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_one_char_arbitrary) {
  const char *src = "123321";
  const char *str = "a";
  const size_t index = 3;
  const char *expected = "123a321";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_multiple_chars_start) {
  const char *src = "123321";
  const char *str = "abcdw";
  const size_t index = 0;
  const char *expected = "abcdw123321";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_multiple_chars_end) {
  const char *src = "123321";
  const char *str = "abcdw";
  const size_t index = 6;
  const char *expected = "123321abcdw";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_insert_multiple_chars_arbitrary) {
  const char *src = "123321";
  const char *str = "abcdw";
  const size_t index = 3;
  const char *expected = "123abcdw321";
  char *actual = (char *)s21_insert(src, str, index);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_both_empty) {
  const char *str = "";
  const char *trim_chars = "";
  const char *expected = "";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_empty_str) {
  const char *str = "";
  const char *trim_chars = "abcd";
  const char *expected = "";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_empty_trim_chars) {
  const char *str = "abcddeedfs";
  const char *trim_chars = "";
  const char *expected = "abcddeedfs";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_one_start) {
  const char *str = "abc";
  const char *trim_chars = "a";
  const char *expected = "bc";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_one_end) {
  const char *str = "abc";
  const char *trim_chars = "c";
  const char *expected = "ab";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_one_both_sides) {
  const char *str = "aba";
  const char *trim_chars = "a";
  const char *expected = "b";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_multiple_same_start) {
  const char *str = "aaaabc";
  const char *trim_chars = "a";
  const char *expected = "bc";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_multiple_same_end) {
  const char *str = "abcccccccccc";
  const char *trim_chars = "c";
  const char *expected = "ab";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_multiple_same_both_sides) {
  const char *str = "aaaaaabcbcbcbcbcbaaaaa";
  const char *trim_chars = "a";
  const char *expected = "bcbcbcbcbcb";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_multiple_different_start) {
  const char *str = "bcccbbbcccaaa";
  const char *trim_chars = "bc";
  const char *expected = "aaa";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_multiple_different_end) {
  const char *str = "aaaatbccbbbbbcbcbcbccc";
  const char *trim_chars = "bc";
  const char *expected = "aaaat";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_trim_multiple_different_both_sides) {
  const char *str =
      "12332133213223123311a0-/0aaa333333333222222211321232112312";
  const char *trim_chars = "312";
  const char *expected = "a0-/0aaa";
  char *actual = (char *)s21_trim(str, trim_chars);
  ck_assert_str_eq(actual, expected);
  if (actual) {
    free(actual);
  }
}
END_TEST

START_TEST(test_s21_sprintf_basic_string) {
  char buffer_one[100] = "";
  int len_one = sprintf(buffer_one, "Hello, World!");
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "Hello, World!");
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_integer_format) {
  char buffer_one[100] = "";
  int len_one = sprintf(buffer_one, "int: %d", 42);
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "int: %d", 42);
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_multiple_formats) {
  char buffer_one[100] = "";
  int len_one =
      sprintf(buffer_one, "Name: %s, Age: %d, Height: %.2f", "Alice", 30, 5.7);
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "Name: %s, Age: %d, Height: %.2f",
                            "Alice", 30, 5.7);
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_string_with_padding) {
  char buffer_one[100] = "";
  int len_one = sprintf(buffer_one, "%14s", "Test");
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "%14s", "Test");
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_special_characters) {
  char buffer_one[100] = "";
  int len_one = sprintf(buffer_one, "Tab:\tBackslash:\\Line break:\n");
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "Tab:\tBackslash:\\Line break:\n");
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_basic_unsigned) {
  char buffer_one[100] = "";
  unsigned int x = 255;
  int len_one = sprintf(buffer_one, "Unsigned: %u", x);
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "Unsigned: %u", x);
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_signed_long) {
  char buffer_one[100] = "";
  long val_oneue = 1234567890L;
  int len_one = sprintf(buffer_one, "Long: %ld", val_oneue);
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "Long: %ld", val_oneue);
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_char) {
  char buffer_one[100] = "";
  char buffer_two[100] = "";
  char *buffer_three = "%c Test %c Test %c Test %c Test %c";
  int a = 9;
  int b = 10;
  int c = 17;
  int d = 66;
  int e = 124;
  ck_assert_int_eq(sprintf(buffer_one, buffer_three, a, b, c, d, e),
                   s21_sprintf(buffer_two, buffer_three, a, b, c, d, e));
  ck_assert_pstr_eq(buffer_one, buffer_two);
}
END_TEST

START_TEST(test_s21_sprintf_short_decimal) {
  char buffer_one[100] = "";
  short val_oneue = 42;
  int len_one = sprintf(buffer_one, "Short: %hd", val_oneue);
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "Short: %hd", val_oneue);
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}
END_TEST

START_TEST(test_s21_sprintf_basic_percent) {
  char buffer_one[100] = "";
  int len_one = sprintf(buffer_one, "Percentage: %%");
  char buffer_two[100] = "";
  int len_two = s21_sprintf(buffer_two, "Percentage: %%");
  ck_assert_str_eq(buffer_one, buffer_two);
  ck_assert_int_eq(len_one, len_two);
}

START_TEST(test_s21_sprintf_negative) {
  char str_one[100] = "";
  char str_two[100] = "";
  char *str_three = "%d, %d, %d";
  int val_one = 012;
  int val_two = -017;
  int val_three = 07464;
  ck_assert_int_eq(
      sprintf(str_one, str_three, val_one, val_two, val_three),
      s21_sprintf(str_two, str_three, val_one, val_two, val_three));
  ck_assert_pstr_eq(str_one, str_two);
}
END_TEST

START_TEST(test_s21_sprintf_sizes) {
  char str_one[100] = "";
  char str_two[100] = "";
  char *str_three = "%ld, %ld, %hd, %hd";
  long int val_one = 3088675747373646;
  long val_two = 33030030303;
  short int val_three = 22600;
  short val_four = -120;
  ck_assert_int_eq(
      sprintf(str_one, str_three, val_one, val_two, val_three, val_four),
      s21_sprintf(str_two, str_three, val_one, val_two, val_three, val_four));
  ck_assert_pstr_eq(str_one, str_two);
}
END_TEST

START_TEST(test_s21_sprintf_string) {
  char str_one[100] = "";
  char str_two[100] = "";
  char *str_three = "%s Test %s Test %s";
  char *val_one = "One";
  char *val_two = "T w o?";
  char *val_three = "TThhrreeee";
  ck_assert_int_eq(
      sprintf(str_one, str_three, val_one, val_two, val_three),
      s21_sprintf(str_two, str_three, val_one, val_two, val_three));
  ck_assert_pstr_eq(str_one, str_two);
}
END_TEST

START_TEST(test_s21_sprintf_unsigned) {
  char str_one[200] = "";
  char str_two[200] = "";
  char *str_three = "%6.5u Test %.23u Test %3.u TEST %.u";
  unsigned int val_one = 3015;
  unsigned int val_two = 712;
  unsigned int val_three = 99;
  unsigned int val_four = 38;
  ck_assert_int_eq(
      sprintf(str_one, str_three, val_one, val_two, val_three, val_four),
      s21_sprintf(str_two, str_three, val_one, val_two, val_three, val_four));
  ck_assert_pstr_eq(str_one, str_two);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  char str_one[100] = "";
  char str_two[100] = "";
  char *str_three = "Test Tes%%%%t";
  int val_one = 012;
  int val_two = 017;
  ck_assert_int_eq(sprintf(str_one, str_three, val_one, val_two),
                   s21_sprintf(str_two, str_three, val_one, val_two));
  ck_assert_pstr_eq(str_one, str_two);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s = suite_create("String");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strchr_empty);
  tcase_add_test(tc_core, test_s21_strchr_empty_nullterm);
  tcase_add_test(tc_core, test_s21_strchr_short_first);
  tcase_add_test(tc_core, test_s21_strchr_short_last);
  tcase_add_test(tc_core, test_s21_strchr_short_absent);
  tcase_add_test(tc_core, test_s21_strchr_short_nullterm);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strerror);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strrchr_empty);
  tcase_add_test(tc_core, test_s21_strrchr_empty_nullterm);
  tcase_add_test(tc_core, test_s21_strrchr_short_first);
  tcase_add_test(tc_core, test_s21_strrchr_short_last);
  tcase_add_test(tc_core, test_s21_strrchr_short_absent);
  tcase_add_test(tc_core, test_s21_strrchr_short_nullterm);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_strtok_empty_both);
  tcase_add_test(tc_core, test_s21_strtok_empty_delim);
  tcase_add_test(tc_core, test_s21_strtok_empty_str);
  tcase_add_test(tc_core, test_s21_strtok_short_every_char);
  tcase_add_test(tc_core, test_s21_strtok_short_every_other_char);
  tcase_add_test(tc_core, test_s21_strtok_second_buffer_after_draining);
  tcase_add_test(tc_core, test_s21_strtok_second_buffer_right_away);
  tcase_add_test(tc_core, test_s21_to_lower_empty);
  tcase_add_test(tc_core, test_s21_to_lower_short_no_upper);
  tcase_add_test(tc_core, test_s21_to_lower_short_only_upper);
  tcase_add_test(tc_core, test_s21_to_lower_short_mixed);
  tcase_add_test(tc_core, test_s21_to_upper_empty);
  tcase_add_test(tc_core, test_s21_to_upper_short_no_lower);
  tcase_add_test(tc_core, test_s21_to_upper_short_only_lower);
  tcase_add_test(tc_core, test_s21_to_upper_short_mixed);
  tcase_add_test(tc_core, test_s21_insert_both_empty);
  tcase_add_test(tc_core, test_s21_insert_src_empty);
  tcase_add_test(tc_core, test_s21_insert_str_empty_start);
  tcase_add_test(tc_core, test_s21_insert_str_empty_end);
  tcase_add_test(tc_core, test_s21_insert_str_empty_arbitrary);
  tcase_add_test(tc_core, test_s21_insert_one_char_start);
  tcase_add_test(tc_core, test_s21_insert_one_char_end);
  tcase_add_test(tc_core, test_s21_insert_one_char_arbitrary);
  tcase_add_test(tc_core, test_s21_insert_multiple_chars_start);
  tcase_add_test(tc_core, test_s21_insert_multiple_chars_end);
  tcase_add_test(tc_core, test_s21_insert_multiple_chars_arbitrary);
  tcase_add_test(tc_core, test_s21_trim_both_empty);
  tcase_add_test(tc_core, test_s21_trim_empty_str);
  tcase_add_test(tc_core, test_s21_trim_empty_trim_chars);
  tcase_add_test(tc_core, test_s21_trim_one_start);
  tcase_add_test(tc_core, test_s21_trim_one_end);
  tcase_add_test(tc_core, test_s21_trim_one_both_sides);
  tcase_add_test(tc_core, test_s21_trim_multiple_same_start);
  tcase_add_test(tc_core, test_s21_trim_multiple_same_end);
  tcase_add_test(tc_core, test_s21_trim_multiple_same_both_sides);
  tcase_add_test(tc_core, test_s21_trim_multiple_different_start);
  tcase_add_test(tc_core, test_s21_trim_multiple_different_end);
  tcase_add_test(tc_core, test_s21_trim_multiple_different_both_sides);
  tcase_add_test(tc_core, test_s21_sprintf_char);
  tcase_add_test(tc_core, test_s21_sprintf_basic_string);
  tcase_add_test(tc_core, test_s21_sprintf_integer_format);
  tcase_add_test(tc_core, test_s21_sprintf_multiple_formats);
  tcase_add_test(tc_core, test_s21_sprintf_string_with_padding);
  tcase_add_test(tc_core, test_s21_sprintf_special_characters);
  tcase_add_test(tc_core, test_s21_sprintf_basic_unsigned);
  tcase_add_test(tc_core, test_s21_sprintf_signed_long);
  tcase_add_test(tc_core, test_s21_sprintf_short_decimal);
  tcase_add_test(tc_core, test_s21_sprintf_basic_percent);
  tcase_add_test(tc_core, test_s21_sprintf_negative);
  tcase_add_test(tc_core, test_s21_sprintf_sizes);
  tcase_add_test(tc_core, test_s21_sprintf_string);
  tcase_add_test(tc_core, test_s21_sprintf_unsigned);
  tcase_add_test(tc_core, test_s21_sprintf_percent);

  suite_add_tcase(s, tc_core);

  return s;
}