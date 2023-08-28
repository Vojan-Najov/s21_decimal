#include "s21_decimal_aux.h"
#include "s21_uint192.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign, sign_1, sign_2;
  int scale, scale_1, scale_2;
  s21_uint192_t val_1, val_2, tmp;
  int status = S21_DECIMAL_OK;

  sign_1 = s21_sign(&value_1);
  sign_2 = s21_sign(&value_2);
  if (sign_1 ^ sign_2) {
    s21_negate(value_2, &value_2);
    status = s21_add(value_1, value_2, result);
  } else {
    S21_UINT192_FROM_DECIMAL(val_1.bits, value_1.bits);
    S21_UINT192_FROM_DECIMAL(val_2.bits, value_2.bits);
    scale_1 = s21_scale(&value_1);
    scale_2 = s21_scale(&value_2);
    if (scale_1 > scale_2) {
      scale = scale_1;
      s21_uint192_ratio(scale_1 - scale_2, &tmp);
      s21_uint192_multiply(val_2, tmp, &val_2);
    } else if (scale_2 > scale_1) {
      scale = scale_2;
      s21_uint192_ratio(scale_2 - scale_1, &tmp);
      s21_uint192_multiply(val_1, tmp, &val_1);
    } else {
      scale = scale_1;
    }
    if (sign_1) {
      if (s21_uint192_gt(val_2, val_1)) {
        sign = 0;
        s21_uint192_sub(val_2, val_1, &tmp);
      } else {
        sign = 1;
        s21_uint192_sub(val_1, val_2, &tmp);
      }
    } else {
      if (s21_uint192_gt_eq(val_1, val_2)) {
        sign = 0;
        s21_uint192_sub(val_1, val_2, &tmp);
      } else {
        sign = 1;
        s21_uint192_sub(val_2, val_1, &tmp);
      }
    }
    status = s21_uint192_to_decimal_with_rounding(tmp, scale, sign, result);
  }

  return (status);
}
