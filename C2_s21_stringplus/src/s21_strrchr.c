#include "s21_string.h"

char* s21_strrchr(const char* str, int c) {
  s21_size_t len = s21_strlen((char*)str);
  char* res = s21_NULL;

  if (c == '\0') res = (char*)str + len;

  for (str += len - 1;; str--) {
    if (!*str) break;
    if (*str == c) {
      res = (char*)str;
      break;
    }
  }

  return res;
}
