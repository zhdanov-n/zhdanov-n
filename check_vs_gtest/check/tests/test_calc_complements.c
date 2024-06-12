#include "s21_matrix_test.h"

START_TEST(complements_1x1) {
  matrix_t m = {0};
  matrix_t expected = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &m);
  s21_create_matrix(1, 1, &expected);
  m.matrix[0][0] = 21;
  expected.matrix[0][0] = 1;
  int code = s21_calc_complements(&m, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(complements_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 4, &m);

  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, CALCULATION_ERROR);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_normal) {
  matrix_t expected = {0};
  matrix_t m = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &m);
  s21_create_matrix(3, 3, &expected);

  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;

  m.matrix[1][0] = 0;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;

  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;

  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;

  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  int code = s21_calc_complements(&m, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(complements_NULL_A) {
  matrix_t result = {0};
  int code = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}

END_TEST

START_TEST(complements_NULL_res) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  s21_create_matrix(rows, rows, &m);
  int code = s21_calc_complements(&m, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}

END_TEST

START_TEST(complements_NAN) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = S21_NAN;

  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);
  ck_assert_int_eq(code, CALCULATION_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(complements_empty) {
  matrix_t a = {0};
  matrix_t b = {0};
  ck_assert_int_eq(s21_calc_complements(&a, &b), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("case_calc_complements");

  tcase_add_test(tc, complements_1x1);
  tcase_add_test(tc, complements_incorrect);
  tcase_add_test(tc, test_not_sqare);
  tcase_add_test(tc, test_normal);
  tcase_add_test(tc, complements_NULL_A);
  tcase_add_test(tc, complements_NULL_res);
  tcase_add_test(tc, complements_NAN);
  tcase_add_test(tc, complements_empty);

  suite_add_tcase(s, tc);
  return s;
}
