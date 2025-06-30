#include "s21_string.h"

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char value = (unsigned char)c;
  for (size_t i = 0; i < n; i++) {
    s[i] = value;
  }
  return str;
}