#include "s21_decimal_aux.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  S21_DECIMAL_RESET_TO_ZERO(dst->bits);
  if (src < 0) {
    dst->bits[3] = 0x80000000U;
    src = ~src + 1;
  }
  dst->bits[0] = src;

  return (S21_DECIMAL_OK);
}
