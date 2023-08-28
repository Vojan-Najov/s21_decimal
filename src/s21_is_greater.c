#include "s21_decimal.h"

int s21_is_greater(s21_decimal lhs, s21_decimal rhs) {
  return (s21_is_less(rhs, lhs));
}
