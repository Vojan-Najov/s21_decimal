#include "s21_decimal_aux.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = S21_DECIMAL_OK;
  int scale, sign;
  s21_decimal ratio;

  sign = s21_sign(&value);
  scale = s21_scale(&value);
  if (scale == 0) {
    S21_DECIMAL_COPY(result->bits, value.bits);
  } else {
    status = s21_ratio(scale, &ratio);
    if (status == S21_DECIMAL_OK) {
      s21_uint96_div(value, ratio, result);
      if (sign) {
        result->bits[3] |= 0x80000000U;
      }
    } else {
      S21_DECIMAL_RESET_TO_ZERO(result->bits);
    }
  }

  return (status);
}
