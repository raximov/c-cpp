#include "s21_strerror.h"

#include "s21_string.h"

char *s21_strerror(int errcode) {
  static char unknown_error[32];
  static char err_text[100];
  if ((errcode < 0) || ((unsigned long)errcode >=
                        sizeof(error_messages) / sizeof(error_messages[0]))) {
    s21_sprintf(unknown_error, "Unknown error %d", errcode);

    s21_strncpy(err_text, unknown_error, sizeof(err_text) - 1);

  } else {
    s21_strncpy(err_text, error_messages[errcode], sizeof(err_text) - 1);
  }
  return err_text;
}
