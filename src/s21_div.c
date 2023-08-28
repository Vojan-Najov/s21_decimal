#include "s21_decimal_aux.h"
#include "s21_uint192.h"

static void _rounding(s21_uint192_t rem, s21_uint192_t d,
                      s21_uint192_t *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign;
  int scale, scale_1, scale_2;
  s21_uint192_t val_1, val_2, tmp;
  s21_uint192_t res = {{0, 0, 0, 0, 0, 0}};
  int status = S21_DECIMAL_OK;

  if (s21_iszero(&value_2)) {
    if (s21_iszero(&value_1)) {
      S21_DECIMAL_RESET_TO_ZERO(result->bits);
    } else {
      S21_DECIMAL_COPY(result->bits, S21_DECIMAL_MAX.bits);
    }
    result->bits[3] = (s21_sign(&value_1) ^ s21_sign(&value_2)) << 31;
    status = S21_DECIMAL_DEVIDE_BY_ZERO;
  } else {
    sign = s21_sign(&value_1) ^ s21_sign(&value_2);
    scale_1 = s21_scale(&value_1);
    scale_2 = s21_scale(&value_2);
    S21_UINT192_FROM_DECIMAL(val_1.bits, value_1.bits);
    S21_UINT192_FROM_DECIMAL(val_2.bits, value_2.bits);
    if (scale_2 > scale_1) {
      scale = 0;
      s21_uint192_ratio(scale_2 - scale_1, &tmp);
      s21_uint192_multiply(val_1, tmp, &val_1);
    } else {
      scale = scale_1 - scale_2;
    }
    while (!s21_uint192_iszero(&val_1) && scale < S21_DECIMAL_MAX_SCALE) {
      s21_uint192_div_with_rem(val_1, val_2, &tmp, &val_1);
      s21_uint192_add(res, tmp, &res);
      s21_uint192_multiply(res, S21_UINT192_10, &res);
      s21_uint192_multiply(val_1, S21_UINT192_10, &val_1);
      ++scale;
    }
    s21_uint192_div_with_rem(val_1, val_2, &tmp, &val_1);
    s21_uint192_add(res, tmp, &res);
    _rounding(val_1, val_2, &res);
    if (s21_uint192_iszero(&res)) {
      scale = 0;
    } else {
      while (scale > scale_1 && s21_uint192_multiple_10(&res)) {
        --scale;
        s21_uint192_div(res, S21_UINT192_10, &res);
      }
    }
    status = s21_uint192_to_decimal_with_rounding(res, scale, sign, result);
  }

  return (status);
}

static void _rounding(s21_uint192_t rem, s21_uint192_t d,
                      s21_uint192_t *result) {
  s21_uint192_multiply(rem, S21_UINT192_10, &rem);
  s21_uint192_div(rem, d, &rem);
  if (rem.bits[0] >= 5) {
    s21_uint192_add(*result, S21_UINT192_UNIT, result);
  }
}
