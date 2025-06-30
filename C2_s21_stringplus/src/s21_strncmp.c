#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, size_t n) {
  int diff = 0;
  s21_size_t i = 0;

  while (i < n) {
    char c1 = str1[i];
    char c2 = str2[i];
    if (c1 == '\0' || c1 != c2) {
      diff = c1 - c2;
      break;
    }
    i++;
  }

  return diff;
}
