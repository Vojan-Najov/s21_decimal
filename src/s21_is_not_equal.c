#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal lhs, s21_decimal rhs) {
  return (!s21_is_equal(lhs, rhs));
}
