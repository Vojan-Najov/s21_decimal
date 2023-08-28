#include <check.h>
#include <stdio.h>

#include "s21_decimal_aux.h"
#include "s21_uint192.h"

START_TEST(test_neq) {
  s21_decimal v1 = {{10, 10, 9, 0}};
  s21_decimal v2 = {{10, 10, 11, 0}};
  s21_decimal v3 = {{10, 10, 0, 0}};
  s21_decimal v4 = {{10, 11, 0, 0}};
  s21_decimal v5 = {{10, 0, 0, 0}};
  s21_decimal v6 = {{11, 0, 0, 0}};
  s21_decimal v7 = {{10, 0, 0, 0}};
  s21_decimal v8 = {{10, 0, 0, 0}};

  ck_assert(s21_uint96_neq(v1, v2));
  ck_assert(s21_uint96_neq(v3, v4));
  ck_assert(s21_uint96_neq(v5, v6));
  ck_assert(s21_uint96_neq(v7, v8) == 0);
}
END_TEST

START_TEST(test_ls_eq) {
  s21_decimal v1 = {{10, 10, 9, 0}};
  s21_decimal v2 = {{10, 10, 11, 0}};
  s21_decimal v3 = {{10, 10, 0, 0}};
  s21_decimal v4 = {{10, 11, 0, 0}};
  s21_decimal v5 = {{10, 0, 0, 0}};
  s21_decimal v6 = {{11, 0, 0, 0}};
  s21_decimal v7 = {{10, 0, 0, 0}};
  s21_decimal v8 = {{10, 0, 0, 0}};

  ck_assert(s21_uint96_ls_eq(v1, v2));
  ck_assert(s21_uint96_ls_eq(v3, v4));
  ck_assert(s21_uint96_ls_eq(v5, v6));
  ck_assert(s21_uint96_ls_eq(v7, v8));
}
END_TEST

START_TEST(test_uint192_ls_eq) {
  s21_uint192_t v1 = {{10, 10, 10, 10, 10, 0}};
  s21_uint192_t v2 = {{10, 10, 10, 10, 11, 0}};

  ck_assert(s21_uint192_ls_eq(v1, v2));
}
END_TEST

START_TEST(test_uint192_eq) {
  s21_uint192_t v1 = {{10, 10, 10, 10, 11, 0}};
  s21_uint192_t v2 = {{10, 10, 10, 10, 11, 0}};

  ck_assert(s21_uint192_eq(v1, v2));
}

START_TEST(test_uint192_neq) {
  s21_uint192_t v1 = {{10, 10, 9, 10, 11, 0}};
  s21_uint192_t v2 = {{10, 10, 10, 10, 11, 0}};

  ck_assert(s21_uint192_neq(v1, v2));
}

Suite *suite_aux(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("test_aux");
  tc = tcase_create("test_aux");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_neq);
    tcase_add_test(tc, test_ls_eq);
    tcase_add_test(tc, test_uint192_ls_eq);
    tcase_add_test(tc, test_uint192_eq);
    tcase_add_test(tc, test_uint192_neq);
    suite_add_tcase(s, tc);
  }

  return (s);
}
