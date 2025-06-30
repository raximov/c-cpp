#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;

  s21_size_t len = s21_strlen(str);
  char *result = (char *)malloc((len + 1) * sizeof(char));

  if (result != s21_NULL) {
    for (s21_size_t i = 0; i < len; i++) {
      result[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] - 32 : str[i];
    }
    result[len] = '\0';
  }

  return result;
}