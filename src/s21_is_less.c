#include "s21_decimal_aux.h"

int s21_is_less(s21_decimal lhs, s21_decimal rhs) {
  int sign_lhs, sign_rhs;
  int scale;
  s21_decimal q_lhs = {{lhs.bits[0], lhs.bits[1], lhs.bits[2], 0}};
  s21_decimal q_rhs = {{rhs.bits[0], rhs.bits[1], rhs.bits[2], 0}};
  s21_decimal r_lhs = {{0, 0, 0, 0}};
  s21_decimal r_rhs = {{0, 0, 0, 0}};
  s21_decimal ratio;
  int status = S21_DECIMAL_FALSE;

  if (!(s21_iszero(&lhs) && s21_iszero(&rhs))) {
    sign_lhs = s21_sign(&lhs);
    sign_rhs = s21_sign(&rhs);
    if (sign_lhs && !sign_rhs) {
      status = S21_DECIMAL_TRUE;
    } else if (sign_lhs == sign_rhs) {
      scale = s21_scale(&lhs) - s21_scale(&rhs);
      if (scale > 0) {
        s21_ratio(scale, &ratio);
        s21_uint96_div_with_rem(lhs, ratio, &q_lhs, &r_lhs);
      } else if (scale < 0) {
        scale = -scale;
        s21_ratio(scale, &ratio);
        s21_uint96_div_with_rem(rhs, ratio, &q_rhs, &r_rhs);
      }
      if (sign_lhs) {
        if (s21_uint96_gt(q_lhs, q_rhs) ||
            (s21_uint96_eq(q_lhs, q_rhs) && s21_uint96_gt(r_lhs, r_rhs))) {
          status = S21_DECIMAL_TRUE;
        }
      } else {
        if (s21_uint96_ls(q_lhs, q_rhs) ||
            (s21_uint96_eq(q_lhs, q_rhs) && s21_uint96_ls(r_lhs, r_rhs))) {
          status = S21_DECIMAL_TRUE;
        }
      }
    }
  }

  return (status);
}
