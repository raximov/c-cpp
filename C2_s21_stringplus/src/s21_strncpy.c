#include "s21_string.h"

char* s21_strncpy(char* destptr, const char* srcptr, s21_size_t num) {
  if (num == 0 || destptr == s21_NULL || srcptr == s21_NULL) return destptr;
  s21_size_t i;
  for (i = 0; i < num && srcptr[i] != '\0'; i++) {
    destptr[i] = srcptr[i];
  }
  if (i < num) destptr[i] = '\0';
  return destptr;
}
