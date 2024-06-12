#include "s21_matrix_test.h"

START_TEST(mult_number_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  double mult_number = get_rand(-10e5, 10e5);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  double mult_number = get_rand(-10e5, 10e5);

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), INCORRECT_MATRIX);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_A_NULL) {
  double a = 5.5;
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(NULL, a, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_number_result_NULL) {
  double a = 5.5;
  int m = 0;
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m++;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, a, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_matrix_NAN) {
  double a = 5.5;
  int m = 0;
  matrix_t A = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m++;
    }
  }
  A.matrix[2][2] = S21_NAN;
  ck_assert_int_eq(s21_mult_number(&A, a, &C), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mult_number_number_NAN) {
  double a = S21_NAN;
  int m = 0;
  matrix_t A = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m++;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, a, &C), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mult_number_number_INF) {
  double a = S21_INF;
  int m = 0;
  matrix_t A = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m++;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, a, &C), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
}
END_TEST

Suite *suite_mult_number(void) {
  Suite *s = suite_create("suite_mult_number");
  TCase *tc = tcase_create("case_mult_number");

  tcase_add_loop_test(tc, mult_number_matrix, 0, 15);
  tcase_add_loop_test(tc, mult_number_matrix2, 0, 15);
  tcase_add_test(tc, mult_number_A_NULL);
  tcase_add_test(tc, mult_number_result_NULL);
  tcase_add_test(tc, mult_number_matrix_NAN);
  tcase_add_test(tc, mult_number_number_NAN);
  tcase_add_test(tc, mult_number_number_INF);

  suite_add_tcase(s, tc);
  return s;
}
