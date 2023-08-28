#ifndef S21_UINT192_H
#define S21_UINT192_H

#include "s21_decimal.h"

#define S21_UINT192_RESET_TO_ZERO(bits) \
  for (int i = 0; i < 6; ++i) {         \
    (bits)[i] = 0;                      \
  }

#define S21_UINT192_COPY(dst_bits, src_bits) \
  for (int i = 0; i < 6; ++i) {              \
    (dst_bits)[i] = (src_bits)[i];           \
  }

#define S21_UINT192_FROM_DECIMAL(dst_bits, src_bits) \
  (dst_bits)[0] = (src_bits)[0];                     \
  (dst_bits)[1] = (src_bits)[1];                     \
  (dst_bits)[2] = (src_bits)[2];                     \
  (dst_bits)[3] = (dst_bits)[4] = (dst_bits)[5] = 0;

#define S21_UINT192_TO_DECIMAL(dst_bits, src_bits) \
  (dst_bits)[0] = (src_bits)[0];                   \
  (dst_bits)[1] = (src_bits)[1];                   \
  (dst_bits)[2] = (src_bits)[2];

typedef struct s21_uint192 {
  unsigned int bits[6];
} s21_uint192_t;

extern const s21_uint192_t S21_UINT192_DECIMAL_MAX;

extern const s21_uint192_t S21_UINT192_10;

extern const s21_uint192_t S21_UINT192_UNIT;

/*
  check a 192 bit unsigned number for equality with zero
*/
int s21_uint192_iszero(s21_uint192_t *num);

/*
  compare 192 bit unsigned integers lhs < rhs
*/
int s21_uint192_ls(s21_uint192_t lhs, s21_uint192_t rhs);

/*
  compare 192 bit unsigned integers lhs <= rhs
*/
int s21_uint192_ls_eq(s21_uint192_t lhs, s21_uint192_t rhs);

/*
  compare 192 bit unsigned integers lhs > rhs
*/
int s21_uint192_gt(s21_uint192_t lhs, s21_uint192_t rhs);

/*
  compare 192 bit unsigned integers lhs >= rhs
*/
int s21_uint192_gt_eq(s21_uint192_t lhs, s21_uint192_t rhs);

/*
  compare 192 bit unsigned integers lhs == rhs
*/
int s21_uint192_eq(s21_uint192_t lhs, s21_uint192_t rhs);

/*
  compare 192 bit unsigned integers lhs != rhs
*/
int s21_uint192_neq(s21_uint192_t lhs, s21_uint192_t rhs);

/*
  make a bitwise shift to the left of a 192 bit unsigned integer
*/
int s21_uint192_shift_left(s21_uint192_t *num);

/*
   set the bit with the index (idx) to the value (bit)
   in a 192 bit unsigned integer
*/
int s21_uint192_setbit(s21_uint192_t *num, int idx, int bit);

/*
  add 192 bit unsigned integers
*/
int s21_uint192_add(s21_uint192_t num, s21_uint192_t addend,
                    s21_uint192_t *result);

/*
  subtract one 96 bit unsigned integer from another
*/
int s21_uint192_sub(s21_uint192_t num, s21_uint192_t subtrahend,
                    s21_uint192_t *result);

/*
   Fill the array with a bit representation of an unsigned 96-bit integer
   and return the index of the highest non-zero bit,
   if there is no such return -1.
*/
int s21_uint192_fill_bits_array(s21_uint192_t num, int bits_array[192]);

/*
  calculate the quotient and remainder of dividing
  one 96 bit unsigned number by another
*/
int s21_uint192_div_with_rem(s21_uint192_t n, s21_uint192_t d, s21_uint192_t *q,
                             s21_uint192_t *r);

/*
  calculate the quotient and of dividing
  one 96 bit unsigned number by another
*/
int s21_uint192_div(s21_uint192_t n, s21_uint192_t d, s21_uint192_t *q);

/*
  multiply 192 bit unsigned integers
*/
int s21_uint192_multiply(s21_uint192_t a, s21_uint192_t b,
                         s21_uint192_t *result);

/*
  convert an unsigned 196 bit integer to a decimal number using bank rounding
*/
int s21_uint192_to_decimal_with_rounding(s21_uint192_t num, int scale, int sign,
                                         s21_decimal *result);

/*
  calculate the power of 10: 10^scale, where scale in [0, 28]
*/
int s21_uint192_ratio(int scale, s21_uint192_t *ratio);

/*
  check that 192 unsigned integer is a multiple of 10
*/
int s21_uint192_multiple_10(s21_uint192_t *res);

#endif
