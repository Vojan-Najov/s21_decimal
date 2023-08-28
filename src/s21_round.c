#include "s21_decimal_aux.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int sign;
  int scale;
  s21_decimal ratio, rem;
  s21_decimal tmp = {{5, 0, 0, 0}};
  int status = S21_DECIMAL_OK;

  sign = s21_sign(&value);
  scale = s21_scale(&value);

  if (!scale) {
    S21_DECIMAL_COPY(result->bits, value.bits);
  } else {
    status = s21_ratio(scale, &ratio);
    if (status == S21_DECIMAL_OK) {
      s21_uint96_div_with_rem(value, ratio, result, &rem);
      if (!s21_iszero(&rem)) {
        while (--scale > 0) {
          s21_uint96_x10(&tmp);
        }
        if (s21_uint96_gt(rem, tmp) ||
            (s21_uint96_eq(rem, tmp) && (result->bits[0] & 0x1U))) {
          s21_uint96_add(*result, S21_DECIMAL_UNIT, result);
        }
      }
      if (sign) {
        result->bits[3] |= 0x80000000U;
      }
    } else {
      S21_DECIMAL_RESET_TO_ZERO(result->bits);
    }
  }

  return (status);
}
