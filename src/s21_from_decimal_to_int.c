#include "s21_decimal_aux.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = S21_DECIMAL_OK;

  status = s21_truncate(src, &src);
  if (status == S21_DECIMAL_OK) {
    if (s21_sign(&src)) {
      if (src.bits[2] || src.bits[1] ||
          ((src.bits[0] & 0x80000000U) && (src.bits[0] & 0x7FFFFFFFU))) {
        status = S21_DECIMAL_ERROR;
      }
      *dst = ~src.bits[0] + 1;
    } else {
      if (src.bits[2] || src.bits[1] || (src.bits[0] & 0x80000000U)) {
        status = S21_DECIMAL_ERROR;
      }
      *dst = src.bits[0];
    }
  }

  return (status);
}
