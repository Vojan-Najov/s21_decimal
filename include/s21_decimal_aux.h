#ifndef S21_DECIMAL_AUX_H
#define S21_DECIMAL_AUX_H

#include "s21_decimal.h"

#define S21_DECIMAL_MAX_SCALE 28

#define S21_DECIMAL_RESET_TO_ZERO(bits)                                        \
  (bits)[0] = (bits)[1] = (bits)[2] = (bits)[3] = 0;

#define S21_DECIMAL_COPY(dst_bits, src_bits)                                   \
  (dst_bits)[0] = (src_bits)[0];                                               \
  (dst_bits)[1] = (src_bits)[1];                                               \
  (dst_bits)[2] = (src_bits)[2];                                               \
  (dst_bits)[3] = (src_bits)[3];

extern const s21_decimal S21_DECIMAL_UNIT;
extern const s21_decimal S21_DECIMAL_MAX;
extern const s21_decimal S21_DECIMAL_10;

/* Auxiliary functions */
int s21_uint96_ls(s21_decimal lhs, s21_decimal rhs);
int s21_uint96_ls_eq(s21_decimal lhs, s21_decimal rhs);
int s21_uint96_eq(s21_decimal lhs, s21_decimal rhs);
int s21_uint96_neq(s21_decimal lhs, s21_decimal rhs);
int s21_uint96_gt(s21_decimal lhs, s21_decimal rhs);
int s21_uint96_gt_eq(s21_decimal lhs, s21_decimal rhs);
int s21_uint96_add(s21_decimal lhs, s21_decimal rhs, s21_decimal *result);
int s21_uint96_sub(s21_decimal lhs, s21_decimal rhs, s21_decimal *result);
int s21_uint96_x10(s21_decimal *num);
int s21_uint96_shift_left(s21_decimal *num);
int s21_uint96_fill_bits_array(s21_decimal num, int bits_array[96]);
int s21_uint96_div(s21_decimal n, s21_decimal d, s21_decimal *q);
int s21_uint96_div_with_rem(s21_decimal n, s21_decimal d, s21_decimal *q,
                            s21_decimal *r);
int s21_sign(s21_decimal *value);
int s21_scale(s21_decimal *value);
int s21_iszero(s21_decimal *value);
int s21_ratio(int scale, s21_decimal *ratio);
int s21_setbit(s21_decimal *num, int idx, int bit);

#endif
