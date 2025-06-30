#include "s21_string.h"

void *s21_strncat(char *destination, const char *source, s21_size_t n) {
  s21_size_t i = 0;
  s21_size_t dest_len = s21_strlen(destination);

  for (; i < n && source[i] != '\0'; i++) {
    destination[dest_len + i] = source[i];
  }

  destination[dest_len + i] = '\0';

  return destination;
}
