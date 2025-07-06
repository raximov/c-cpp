#include "s21_matrix_test.h"

int main(void) {
  int number_failed = 0;
  SRunner* sr = srunner_create(NULL);

  srunner_add_suite(sr, create_matrix_suite());
  srunner_add_suite(sr, eq_matrix_suite());
  srunner_add_suite(sr, remove_matrix_suite());
  srunner_add_suite(sr, sum_matrix_suite());
  srunner_add_suite(sr, sub_matrix_suite());
  srunner_add_suite(sr, mul_num_matrix_suite());
  srunner_add_suite(sr, mul_matrix_suite());
  srunner_add_suite(sr, transpose_test());
  srunner_add_suite(sr, calc_complements_test());
  srunner_add_suite(sr, determinant_test());
  srunner_add_suite(sr, inverse_matrix_test());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
