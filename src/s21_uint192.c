#include "s21_uint192.h"

#include "s21_decimal_aux.h"

const s21_uint192_t S21_UINT192_DECIMAL_MAX = {
    {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0, 0, 0}};

const s21_uint192_t S21_UINT192_10 = {{10, 0, 0, 0, 0, 0}};

const s21_uint192_t S21_UINT192_UNIT = {{1, 0, 0, 0, 0, 0}};

/*
  check a 192 bit unsigned number for equality with zero
*/
int s21_uint192_iszero(s21_uint192_t *num) {
  return (num->bits[0] == 0 && num->bits[1] == 0 && num->bits[2] == 0 &&
          num->bits[3] == 0 && num->bits[4] == 0 && num->bits[5] == 0);
}

/*
  compare 192 bit unsigned integers lhs < rhs
*/
int s21_uint192_ls(s21_uint192_t lhs, s21_uint192_t rhs) {
  unsigned int *ptr_l = lhs.bits + 5;
  unsigned int *begin_l = lhs.bits;
  unsigned int *ptr_r = rhs.bits + 5;

  while (ptr_l > begin_l && *ptr_l == *ptr_r) {
    --ptr_l;
    --ptr_r;
  }

  return (*ptr_l < *ptr_r);
}

/*
  compare 192 bit unsigned integers lhs <= rhs
*/
int s21_uint192_ls_eq(s21_uint192_t lhs, s21_uint192_t rhs) {
  unsigned int *ptr_l = lhs.bits + 5;
  unsigned int *begin_l = lhs.bits;
  unsigned int *ptr_r = rhs.bits + 5;

  while (ptr_l > begin_l && *ptr_l == *ptr_r) {
    --ptr_l;
    --ptr_r;
  }

  return (*ptr_l <= *ptr_r);
}

/*
  compare 192 bit unsigned integers lhs > rhs
*/
int s21_uint192_gt(s21_uint192_t lhs, s21_uint192_t rhs) {
  unsigned int *ptr_l = lhs.bits + 5;
  unsigned int *begin_l = lhs.bits;
  unsigned int *ptr_r = rhs.bits + 5;

  while (ptr_l > begin_l && *ptr_l == *ptr_r) {
    --ptr_l;
    --ptr_r;
  }

  return (*ptr_l > *ptr_r);
}

/*
  compare 192 bit unsigned integers lhs >= rhs
*/
int s21_uint192_gt_eq(s21_uint192_t lhs, s21_uint192_t rhs) {
  unsigned int *ptr_l = lhs.bits + 5;
  unsigned int *begin_l = lhs.bits;
  unsigned int *ptr_r = rhs.bits + 5;

  while (ptr_l > begin_l && *ptr_l == *ptr_r) {
    --ptr_l;
    --ptr_r;
  }

  return (*ptr_l >= *ptr_r);
}

/*
  compare 192 bit unsigned integers lhs == rhs
*/
int s21_uint192_eq(s21_uint192_t lhs, s21_uint192_t rhs) {
  unsigned int *ptr_l = lhs.bits + 5;
  unsigned int *begin_l = lhs.bits;
  unsigned int *ptr_r = rhs.bits + 5;

  while (ptr_l > begin_l && *ptr_l == *ptr_r) {
    --ptr_l;
    --ptr_r;
  }

  return (*ptr_l == *ptr_r);
}

/*
  compare 192 bit unsigned integers lhs != rhs
*/
int s21_uint192_neq(s21_uint192_t lhs, s21_uint192_t rhs) {
  unsigned int *ptr_l = lhs.bits + 5;
  unsigned int *begin_l = lhs.bits;
  unsigned int *ptr_r = rhs.bits + 5;

  while (ptr_l > begin_l && *ptr_l == *ptr_r) {
    --ptr_l;
    --ptr_r;
  }

  return (*ptr_l != *ptr_r);
}

/*
  make a bitwise shift to the left of a 192 bit unsigned integer
*/
int s21_uint192_shift_left(s21_uint192_t *num) {
  unsigned int w0, w1, w2, w3, w4, w5;
  unsigned int carry;
  int status = S21_DECIMAL_OK;

  w0 = num->bits[0];
  w1 = num->bits[1];
  w2 = num->bits[2];
  w3 = num->bits[3];
  w4 = num->bits[4];
  w5 = num->bits[5];

  if (w5 & 0x80000000U) {
    status = S21_DECIMAL_OVERFLOW;
  }
  carry = (w4 & 0x80000000U) >> 31;
  w5 <<= 1;
  w5 |= carry;
  carry = (w3 & 0x80000000U) >> 31;
  w4 <<= 1;
  w4 |= carry;
  carry = (w2 & 0x80000000U) >> 31;
  w3 <<= 1;
  w3 |= carry;
  carry = (w1 & 0x80000000U) >> 31;
  w2 <<= 1;
  w2 |= carry;
  carry = (w0 & 0x80000000U) >> 31;
  w1 <<= 1;
  w1 |= carry;
  w0 <<= 1;

  num->bits[0] = w0;
  num->bits[1] = w1;
  num->bits[2] = w2;
  num->bits[3] = w3;
  num->bits[4] = w4;
  num->bits[5] = w5;

  return (status);
}

/*
  set the bit with the index (idx) to the value (bit)
  in a 192 bit unsigned integer
*/
int s21_uint192_setbit(s21_uint192_t *num, int idx, int bit) {
  int status = S21_DECIMAL_OK;
  int k, j;

  if (idx < 0 || idx > 192) {
    status = S21_DECIMAL_ERROR;
  } else {
    k = idx / 32;
    j = idx % 32;
    if (bit) {
      num->bits[k] |= (bit << j);
    } else {
      num->bits[k] &= ~(bit << j);
    }
  }

  return (status);
}

/*
  add 192 bit unsigned integers
*/
int s21_uint192_add(s21_uint192_t num, s21_uint192_t addend,
                    s21_uint192_t *result) {
  unsigned int tmp1, tmp2, tmp3;
  unsigned int carry = 0;
  int idx, high;

  S21_UINT192_RESET_TO_ZERO(result->bits);
  for (int i = 0; i < 12; ++i) {
    idx = i / 2;
    high = i % 2;
    tmp1 = num.bits[idx];
    tmp2 = addend.bits[idx];
    if (high) {
      tmp1 >>= 16;
      tmp2 >>= 16;
    } else {
      tmp1 &= 0xFFFFU;
      tmp2 &= 0xFFFFU;
    }
    tmp3 = tmp1 + tmp2 + carry;
    carry = tmp3 >> 16;
    tmp3 &= 0xFFFFU;
    if (high) {
      tmp3 <<= 16;
    }
    result->bits[idx] |= tmp3;
  }

  return (carry ? S21_DECIMAL_OVERFLOW : S21_DECIMAL_OK);
}

/*
  subtract one 192 bit unsigned integer from another
*/
int s21_uint192_sub(s21_uint192_t num, s21_uint192_t subtrahend,
                    s21_uint192_t *result) {
  unsigned int tmp1, tmp2, tmp3;
  int idx, high;
  int loan = 0;

  S21_UINT192_RESET_TO_ZERO(result->bits);
  for (int i = 0; i < 12; ++i) {
    idx = i / 2;
    high = i % 2;
    tmp1 = num.bits[idx];
    tmp2 = subtrahend.bits[idx];
    if (high) {
      tmp1 >>= 16;
      tmp2 >>= 16;
    } else {
      tmp1 &= 0xFFFFU;
      tmp2 &= 0xFFFFU;
    }
    if (loan) {
      if (tmp1) {
        --tmp1;
        loan = 0;
      } else {
        tmp1 = 0xFFFFU;
        loan = 1;
      }
    }
    if (tmp1 < tmp2) {
      loan = 1;
      tmp1 |= 0x10000U;
    }
    tmp3 = tmp1 - tmp2;
    if (high) {
      tmp3 <<= 16;
    }
    result->bits[idx] |= tmp3;
  }

  return (loan ? S21_DECIMAL_ERROR : S21_DECIMAL_OK);
}

/*
  Fill the array with a bit representation of an unsigned 192-bit integer
  and return the index of the highest non-zero bit,
  if there is no such return -1.
*/
int s21_uint192_fill_bits_array(s21_uint192_t num, int bits_array[192]) {
  unsigned int bits;
  int last_idx = 191;

  for (int i = 0; i < 6; ++i) {
    bits = num.bits[i];
    for (int j = 0; j < 32; ++j) {
      int idx = i * 32 + j;
      bits_array[idx] = bits & 0x1U;
      bits >>= 1;
    }
  }
  while (last_idx >= 0 && !bits_array[last_idx]) {
    --last_idx;
  }

  return (last_idx);
}

/*
  calculate the quotient and remainder of dividing
  one 192 bit unsigned number by another
*/
int s21_uint192_div_with_rem(s21_uint192_t n, s21_uint192_t d, s21_uint192_t *q,
                             s21_uint192_t *r) {
  int nbits[192];
  int idx;
  int status = S21_DECIMAL_OK;

  S21_UINT192_RESET_TO_ZERO(q->bits);
  S21_UINT192_RESET_TO_ZERO(r->bits);
  if (s21_uint192_iszero(&d)) {
    status = S21_DECIMAL_DEVIDE_BY_ZERO;
  } else {
    idx = s21_uint192_fill_bits_array(n, nbits);
    for (; idx >= 0; --idx) {
      s21_uint192_shift_left(r);
      r->bits[0] |= nbits[idx];
      if (s21_uint192_gt_eq(*r, d)) {
        s21_uint192_sub(*r, d, r);
        s21_uint192_setbit(q, idx, 1);
      }
    }
  }

  return (status);
}

/*
  calculate the quotient of dividing
  one 192 bit unsigned number by another
*/
int s21_uint192_div(s21_uint192_t n, s21_uint192_t d, s21_uint192_t *q) {
  int status;
  s21_uint192_t rem;

  status = s21_uint192_div_with_rem(n, d, q, &rem);
  (void)rem;

  return (status);
}

/*
  multiply 192 bit unsigned integers
*/
int s21_uint192_multiply(s21_uint192_t a, s21_uint192_t b,
                         s21_uint192_t *result) {
  int bits[192];
  int last_idx;
  s21_uint192_t addend;
  int status = 0;

  S21_UINT192_RESET_TO_ZERO(result->bits);
  if (s21_uint192_ls(a, b)) {
    last_idx = s21_uint192_fill_bits_array(a, bits);
    S21_UINT192_COPY(addend.bits, b.bits);
  } else {
    last_idx = s21_uint192_fill_bits_array(b, bits);
    S21_UINT192_COPY(addend.bits, a.bits);
  }
  for (int i = 0; i <= last_idx; ++i) {
    if (bits[i]) {
      status += s21_uint192_add(*result, addend, result);
    }
    status += s21_uint192_shift_left(&addend);
  }

  return (status ? S21_DECIMAL_OVERFLOW : S21_DECIMAL_OK);
}

/*
  convert an unsigned 192 bit integer to a decimal number using bank rounding
*/
int s21_uint192_to_decimal_with_rounding(s21_uint192_t num, int scale, int sign,
                                         s21_decimal *result) {
  int rem_count = 0;
  s21_uint192_t rem = {{0, 0, 0, 0, 0, 0}};
  int status = S21_DECIMAL_OK;

  while (s21_uint192_gt(num, S21_UINT192_DECIMAL_MAX) ||
         scale > S21_DECIMAL_MAX_SCALE) {
    if (scale) {
      --scale;
      s21_uint192_div_with_rem(num, S21_UINT192_10, &num, &rem);
      if (!s21_uint192_iszero(&rem)) {
        ++rem_count;
      }
    } else {
      status = sign ? S21_DECIMAL_UNDERFLOW : S21_DECIMAL_OVERFLOW;
      break;
    }
  }
  if (status != S21_DECIMAL_OK) {
    S21_DECIMAL_COPY(result->bits, S21_DECIMAL_MAX.bits);
    if (sign) {
      result->bits[3] = 0x80000000U;
    }
  } else {
    S21_UINT192_TO_DECIMAL(result->bits, num.bits);
    if (rem.bits[0] > 5 ||
        (rem.bits[0] == 5 && (rem_count > 1 || (result->bits[0] & 0x1U)))) {
      if (s21_uint96_eq(*result, S21_DECIMAL_MAX)) {
        status = sign ? S21_DECIMAL_UNDERFLOW : S21_DECIMAL_OVERFLOW;
      } else {
        s21_uint96_add(*result, S21_DECIMAL_UNIT, result);
      }
    }
    result->bits[3] = (sign << 31) | (scale << 16);
  }

  return (status);
}

/*
  calculate the power of 10: 10^scale, where scale in [0, 28]
*/
int s21_uint192_ratio(int scale, s21_uint192_t *ratio) {
  int status = S21_DECIMAL_OK;

  S21_UINT192_COPY(ratio->bits, S21_UINT192_UNIT.bits);
  if (0 <= scale && scale <= 28) {
    while (scale) {
      s21_uint192_multiply(*ratio, S21_UINT192_10, ratio);
      --scale;
    }
  } else {
    status = S21_DECIMAL_ERROR;
  }

  return (status);
}

/*
  check that 192 unsigned integer is a multiple of 10
*/
int s21_uint192_multiple_10(s21_uint192_t *res) {
  s21_uint192_t q, r;

  s21_uint192_div_with_rem(*res, S21_UINT192_10, &q, &r);
  (void)q;
  return (s21_uint192_iszero(&r));
}
