#include "s21_string.h"

char* s21_strchr(const char* str, int c) {
  char* res = s21_NULL;

  for (;; str++) {
    if (!*str) break;
    if (*str == c) {
      res = (char*)str;
      break;
    }
  }

  if (c == '\0') {
    res = (char*)str;
  }

  return res;
}
