#include "s21_string.h"

void *s21_memcpy(void *destination, const void *source, s21_size_t n) {
  if (destination == s21_NULL || source == s21_NULL) return s21_NULL;

  unsigned char *ptr1 = (unsigned char *)destination;
  const unsigned char *ptr2 = (const unsigned char *)source;

  s21_size_t i = 0;
  if (n > 0) {
    for (; i < n; i++) {
      ptr1[i] = ptr2[i];
    }
  }
  return destination;
}