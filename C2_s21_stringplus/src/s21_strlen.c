#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  for (s21_size_t len = 0;; len++)
    if (str[len] == '\0') return len;
}
