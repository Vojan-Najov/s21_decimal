#include "s21_decimal_aux.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  S21_DECIMAL_COPY(result->bits, value.bits);
  result->bits[3] ^= (1 << 31);

  return (S21_DECIMAL_OK);
}
