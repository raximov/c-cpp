#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL || start_index > s21_strlen(src)) {
    return s21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  char *res = (char *)calloc(src_len + str_len + 1, sizeof(char));

  if (res) {
    s21_size_t i = 0;
    for (; i < start_index; i++) {
      res[i] = src[i];
    }
    for (s21_size_t j = 0; j < str_len; j++, i++) {
      res[i] = str[j];
    }
    for (s21_size_t j = start_index; j < src_len; j++, i++) {
      res[i] = src[j];
    }
  }

  return res;
}
