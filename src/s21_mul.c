#include "s21_decimal_aux.h"
#include "s21_uint192.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int sign, scale;
  s21_uint192_t val1, val2;
  s21_uint192_t prod;
  int status = S21_DECIMAL_OK;

  sign = s21_sign(&value_1) ^ s21_sign(&value_2);
  scale = s21_scale(&value_1) + s21_scale(&value_2);
  S21_UINT192_FROM_DECIMAL(val1.bits, value_1.bits);
  S21_UINT192_FROM_DECIMAL(val2.bits, value_2.bits);
  s21_uint192_multiply(val1, val2, &prod);
  status = s21_uint192_to_decimal_with_rounding(prod, scale, sign, result);

  return (status);
}
