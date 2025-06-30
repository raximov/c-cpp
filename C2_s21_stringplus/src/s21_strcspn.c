#include "s21_string.h"

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t res = 0;

  int found = 0;
  for (s21_size_t i = 0; !found && i < s21_strlen((char*)str1); i++) {
    for (s21_size_t j = 0; !found && j < s21_strlen((char*)str2); j++)
      if (str1[i] == str2[j]) found = 1;
    if (!found) res++;
  }

  return res;
}
