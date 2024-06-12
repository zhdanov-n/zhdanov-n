#include "s21_matrix_test.h"

START_TEST(determinant_single) {
  const int size = 1;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 21;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 21, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_simple) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 4;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 3;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant1) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant2) {
  const int size = 4;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant3) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant4) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 7;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 1;
  m.matrix[2][0] = 9;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = 1;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -32, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant5) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = -3;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 7, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant6) {
  const int size = 1;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -5, 1e-6);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant7) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  rows = -rows;
  s21_create_matrix(rows, rows, &m);
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant8) {
  matrix_t m = {0};
  int rows = 4;
  int cols = 5;
  s21_create_matrix(rows, cols, &m);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, CALCULATION_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_NULL) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  s21_create_matrix(rows, rows, &m);
  double res = 0;
  int code = s21_determinant(NULL, &res);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_NULL_res) {
  matrix_t m = {0};
  int rows = rand() % 100 + 1;
  s21_create_matrix(rows, rows, &m);
  int code = s21_determinant(&m, NULL);
  ck_assert_int_eq(code, INCORRECT_MATRIX);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_NAN) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = -5;
  m.matrix[0][1] = -4;
  m.matrix[1][0] = -2;
  m.matrix[1][1] = S21_NAN;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, CALCULATION_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant9) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][1] = 6;
  A.matrix[0][2] = 7;
  A.matrix[1][2] = 8;
  A.matrix[2][2] = 9;
  ck_assert_int_eq(0, s21_determinant(&A, &result));
  ck_assert_ldouble_eq_tol(0, result, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant10) {
  int res = 0;
  double determ = 0;
  matrix_t A = {NULL, 0, 0};

  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant11) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 5;
  A.matrix[1][0] = 1;
  A.matrix[2][0] = 0;
  A.matrix[0][1] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][1] = 5;
  A.matrix[0][2] = 1;
  A.matrix[1][2] = 6;
  A.matrix[2][2] = 9;
  ck_assert_int_eq(0, s21_determinant(&A, &result));
  ck_assert_ldouble_eq_tol(8, result, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant12) {
  double result = 0;
  matrix_t A = {0};
  s21_create_matrix(1, 2, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), 2);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_determinant(void) {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("case_determinant");

  tcase_add_test(tc, determinant_single);
  tcase_add_test(tc, determinant_simple);
  tcase_add_test(tc, determinant1);
  tcase_add_test(tc, determinant2);
  tcase_add_test(tc, determinant3);
  tcase_add_test(tc, determinant4);
  tcase_add_test(tc, determinant5);
  tcase_add_test(tc, determinant6);
  tcase_add_loop_test(tc, determinant7, 0, 1);
  tcase_add_test(tc, determinant8);
  tcase_add_test(tc, determinant_NULL);
  tcase_add_test(tc, determinant_NULL_res);
  tcase_add_test(tc, determinant_NAN);
  tcase_add_test(tc, determinant9);
  tcase_add_test(tc, determinant10);
  tcase_add_test(tc, determinant11);
  tcase_add_test(tc, determinant12);

  suite_add_tcase(s, tc);
  return s;
}
