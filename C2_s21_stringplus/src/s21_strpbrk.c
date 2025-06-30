#include "s21_string.h"

char *s21_strpbrk(const char *str, const char *sym) {
  char *flag = NULL;

  for (s21_size_t i = 0; i < s21_strlen((char *)str); i++)
    for (s21_size_t j = 0; j < s21_strlen((char *)sym); j++) {
      if ((str[i] == sym[j]) && (flag == NULL)) {
        str = str + i;
        flag = (char *)str;
        break;
      }
    }
  return flag;
}