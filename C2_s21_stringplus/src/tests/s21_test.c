#include "s21_test.h"

#include <stdio.h>

int main() {
  int failed_cnt = 0;

  Suite* s[] = {
      test_memchr(),   test_memcmp(),  test_memcpy(),   test_memset(),
      test_sprintf(),  test_strncat(), test_strchr(),   test_strncmp(),
      test_strncpy(),  test_insert(),  test_trim(),     test_strcspn(),
      test_strerror(), test_strlen(),  test_strpbrk(),  test_strrchr(),
      test_strstr(),   test_strtok(),  test_to_lower(), test_to_upper(),
      test_sscanf(),   NULL,
  };

  for (int i = 0; s[i]; i++) {
    SRunner* runner = srunner_create(s[i]);

    srunner_run_all(runner, CK_NORMAL);

    failed_cnt += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  printf("\n---------------TESTS FAILED: %d---------------\n", failed_cnt);
  return 0;
}
