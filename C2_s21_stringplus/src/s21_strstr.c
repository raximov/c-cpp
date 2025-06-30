#include "s21_string.h"

char *s21_strstr(const char *orig, const char *match) {
  s21_size_t orig_len = s21_strlen(orig);
  s21_size_t match_len = s21_strlen(match);

  if (orig_len < match_len) return s21_NULL;

  if (match_len == 0) return (char *)orig;

  for (s21_size_t i = 0; i <= orig_len - match_len; i++) {
    s21_size_t j;
    for (j = 0; j < match_len; j++) {
      if (orig[i + j] != match[j]) break;
    }
    if (j == match_len) return (char *)(orig + i);
  }

  return s21_NULL;
}
