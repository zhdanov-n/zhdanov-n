#ifndef SRC_S21_MATRIX_TEST_H_
#define SRC_S21_MATRIX_TEST_H_

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../s21_matrix.h"

#define S21_INF __builtin_inf()
#define S21_NAN __builtin_nan("")

Suite *suite_create_remove_matrix(void);
Suite *suite_eq_matrix(void);
Suite *suite_sum_matrix(void);
Suite *suite_sub_matrix(void);
Suite *suite_mult_number(void);
Suite *suite_mult_matrix(void);
Suite *suite_transpose(void);
Suite *suite_determinant(void);
Suite *suite_calc_complements(void);
Suite *suite_inverse_matrix(void);

void run_tests(void);
void run_testcase(Suite *testcase);
double get_rand(double min, double max);

#endif  //  SRC_S21_MATRIX_TEST_H_
