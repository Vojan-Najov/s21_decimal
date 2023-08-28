#include "s21_decimal_aux.h"
#include "s21_uint192.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign, sign_1, sign_2;
  int scale_1, scale_2, scale;
  s21_uint192_t val_1, val_2;
  s21_uint192_t tmp, rem;
  int status = S21_DECIMAL_OK;
  int round_flag;

  S21_DECIMAL_RESET_TO_ZERO(result->bits);
  if (s21_iszero(&value_2)) {
    status = S21_DECIMAL_DEVIDE_BY_ZERO;
  } else {
    sign_1 = s21_sign(&value_1);
    sign_2 = s21_sign(&value_2);
    sign = sign_1;
    scale_1 = s21_scale(&value_1);
    scale_2 = s21_scale(&value_2);
    S21_UINT192_FROM_DECIMAL(val_1.bits, value_1.bits);
    S21_UINT192_FROM_DECIMAL(val_2.bits, value_2.bits);
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
    round_flag = s21_uint192_gt(val_1, S21_UINT192_DECIMAL_MAX);
    if (s21_uint192_ls(val_1, val_2)) {
      S21_DECIMAL_COPY(result->bits, value_1.bits);
    } else {
      s21_uint192_div_with_rem(val_1, val_2, &tmp, &rem);
      if (s21_uint192_gt(tmp, S21_UINT192_DECIMAL_MAX)) {
        status = sign_1 ^ sign_2 ? S21_DECIMAL_UNDERFLOW : S21_DECIMAL_OVERFLOW;
      } else {
        S21_UINT192_TO_DECIMAL(result->bits, rem.bits);
        if (round_flag) {
          scale = scale_1;
          result->bits[3] = (scale_2 - scale_1) << 16;
          s21_round(*result, result);
        }
        result->bits[3] = (sign << 31) | (scale << 16);
      }
    }
  }

  return (status);
}
