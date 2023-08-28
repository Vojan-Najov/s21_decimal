#include <check.h>
#include <stdio.h>

#include "s21_decimal_aux.h"

static s21_decimal arr[] = {
    {.bits = {0x00000000, 0x00000000, 0x00000000, 0x00000001}},
    {{0x00000000, 0x00000000, 0x00000000, 0x0000000A}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00000064}},
    {{0x00000000, 0x00000000, 0x00000000, 0x000003E8}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00002710}},
    {{0x00000000, 0x00000000, 0x00000000, 0x000186A0}},
    {{0x00000000, 0x00000000, 0x00000000, 0x000F4240}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00989680}},
    {{0x00000000, 0x00000000, 0x00000000, 0x05F5E100}},
    {{0x00000000, 0x00000000, 0x00000000, 0x3B9ACA00}},
    {{0x00000000, 0x00000000, 0x00000002, 0x540BE400}},
    {{0x00000000, 0x00000000, 0x00000017, 0x4876E800}},
    {{0x00000000, 0x00000000, 0x000000E8, 0xD4A51000}},
    {{0x00000000, 0x00000000, 0x00000918, 0x4E72A000}},
    {{0x00000000, 0x00000000, 0x00005AF3, 0x107A4000}},
    {{0x00000000, 0x00000000, 0x00038D7E, 0xA4C68000}},
    {{0x00000000, 0x00000000, 0x002386F2, 0x6FC10000}},
    {{0x00000000, 0x00000000, 0x01634578, 0x5D8A0000}},
    {{0x00000000, 0x00000000, 0x0DE0B6B3, 0xA7640000}},
    {{0x00000000, 0x00000000, 0x8AC72304, 0x89E80000}},
    {{0x00000000, 0x00000005, 0x6BC75E2D, 0x63100000}},
    {{0x00000000, 0x00000036, 0x35C9ADC5, 0xDEA00000}},
    {{0x00000000, 0x0000021E, 0x19E0C9BA, 0xB2400000}},
    {{0x00000000, 0x0000152D, 0x02C7E14A, 0xF6800000}},
    {{0x00000000, 0x0000D3C2, 0x1BCECCED, 0xA1000000}},
    {{0x00000000, 0x00084595, 0x16140148, 0x4A000000}},
    {{0x00000000, 0x0052B7D2, 0xDCC80CD2, 0xE4000000}},
    {{0x00000000, 0x033B2E3C, 0x9FD0803C, 0xE8000000}},
    {{0x00000000, 0x204FCE5E, 0x3E250261, 0x10000000}},
};

START_TEST(test_pow_10) {
  for (size_t i = 0; i < sizeof(arr) / sizeof(s21_decimal); ++i) {
    s21_decimal tmp = {{5, 5, 5, 5}};
    int ret = s21_ratio((int)i, &tmp);
    ck_assert_int_eq(tmp.bits[0], arr[i].bits[3]);
    ck_assert_int_eq(tmp.bits[1], arr[i].bits[2]);
    ck_assert_int_eq(tmp.bits[2], arr[i].bits[1]);
    ck_assert_int_eq(tmp.bits[3], arr[i].bits[0]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

Suite *suite_ratio(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_ratio");
  tc = tcase_create("s21_ratio");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test_pow_10);
    suite_add_tcase(s, tc);
  }

  return (s);
}
