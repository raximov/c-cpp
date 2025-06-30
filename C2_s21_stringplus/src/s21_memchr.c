#include "s21_string.h"

void *s21_memchr(const void *arr, int c, s21_size_t n) {
  const unsigned char *ptr = (const unsigned char *)arr;
  s21_size_t i = 0;
  char *flag = s21_NULL;

  for (; i < n; i++) {
    if ((ptr[i] == (unsigned char)c) && (flag == s21_NULL)) {
      flag = (void *)(ptr + i);
      break;
    }
  }

  return flag;
}