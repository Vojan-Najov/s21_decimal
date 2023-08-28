#include "s21_decimal_aux.h"

const s21_decimal S21_DECIMAL_UNIT = {{1, 0, 0, 0}};
const s21_decimal S21_DECIMAL_MAX = {
    {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0}};
const s21_decimal S21_DECIMAL_10 = {{10, 0, 0, 0}};

/*
  compare 96 bit unsigned integers lhs < rhs
*/
int s21_uint96_ls(s21_decimal lhs, s21_decimal rhs) {
  return (lhs.bits[2] < rhs.bits[2] ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] < rhs.bits[1]) ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] == rhs.bits[1] &&
           lhs.bits[0] < rhs.bits[0]));
}

/*
  compare 96 bit unsigned integers lhs > rhs
*/
int s21_uint96_gt(s21_decimal lhs, s21_decimal rhs) {
  return (lhs.bits[2] > rhs.bits[2] ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] > rhs.bits[1]) ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] == rhs.bits[1] &&
           lhs.bits[0] > rhs.bits[0]));
}

/*
  compare 96 bit unsigned integers lhs == rhs
*/
int s21_uint96_eq(s21_decimal lhs, s21_decimal rhs) {
  return (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] == rhs.bits[1] &&
          lhs.bits[0] == rhs.bits[0]);
}

/*
  compare 96 bit unsigned integers lhs != rhs
*/
int s21_uint96_neq(s21_decimal lhs, s21_decimal rhs) {
  return (lhs.bits[2] != rhs.bits[2] || lhs.bits[1] != rhs.bits[1] ||
          lhs.bits[0] != rhs.bits[0]);
}

/*
  compare 96 bit unsigned integers lhs <= rhs
*/
int s21_uint96_ls_eq(s21_decimal lhs, s21_decimal rhs) {
  return (lhs.bits[2] < rhs.bits[2] ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] < rhs.bits[1]) ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] == rhs.bits[1] &&
           lhs.bits[0] <= rhs.bits[0]));
}

/*
  compare 96 bit unsigned integers lhs >= rhs
*/
int s21_uint96_gt_eq(s21_decimal lhs, s21_decimal rhs) {
  return (lhs.bits[2] > rhs.bits[2] ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] > rhs.bits[1]) ||
          (lhs.bits[2] == rhs.bits[2] && lhs.bits[1] == rhs.bits[1] &&
           lhs.bits[0] >= rhs.bits[0]));
}

/*
  calculate the sum of two 96 bit unsigned integer numbers
*/
int s21_uint96_add(s21_decimal lhs, s21_decimal rhs, s21_decimal *result) {
  unsigned int tmp1, tmp2, tmp3;
  unsigned int carry = 0;
  int idx, high;

  S21_DECIMAL_RESET_TO_ZERO(result->bits);
  for (int i = 0; i < 6; ++i) {
    idx = i / 2;
    high = i % 2;
    tmp1 = lhs.bits[idx];
    tmp2 = rhs.bits[idx];
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
  subtract one 96 bit unsigned integer from another
*/
int s21_uint96_sub(s21_decimal lhs, s21_decimal rhs, s21_decimal *result) {
  unsigned int tmp1, tmp2, tmp3;
  int idx, high;
  int loan = 0;

  S21_DECIMAL_RESET_TO_ZERO(result->bits);
  for (int i = 0; i < 6; ++i) {
    idx = i / 2;
    high = i % 2;
    tmp1 = lhs.bits[idx];
    tmp2 = rhs.bits[idx];
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

  return (loan ? S21_DECIMAL_UNDERFLOW : S21_DECIMAL_OK);
}

/*
  multiply a 96 bit unsigned integer by 10
*/
int s21_uint96_x10(s21_decimal *num) {
  unsigned int b0, b1, b2;
  unsigned int x8, x2;
  unsigned int carry0, carry1, carry2;

  b0 = num->bits[0];
  b1 = num->bits[1];
  b2 = num->bits[2];
  carry0 = ((b0 & 0xE0000000U) >> 29) + ((b0 & 0x80000000U) >> 31);
  x8 = b0 << 3;
  x2 = b0 << 1;
  b0 = x8 + x2;
  if (((x8 >> 2) + (x2 >> 2) + (((x8 & 0x3) + (x2 & 0x3)) >> 2)) &
      0xC0000000U) {
    ++carry0;
  }
  carry1 = ((b1 & 0xE0000000U) >> 29) + ((b1 & 0x80000000U) >> 31);
  x8 = b1 << 3;
  x2 = b1 << 1;
  b1 = x8 + x2;
  if (((x8 >> 2) + (x2 >> 2) + (((x8 & 0x3) + (x2 & 0x3)) >> 2)) &
      0xC0000000U) {
    ++carry1;
  }
  b1 += carry0;
  x8 = b1;
  x2 = carry0;
  if (((x8 >> 2) + (x2 >> 2) + (((x8 & 0x3) + (x2 & 0x3)) >> 2)) &
      0xC0000000U) {
    ++carry1;
  }
  carry2 = ((b2 & 0xE0000000U) >> 29) + ((b2 & 0x80000000U) >> 31);
  x8 = b2 << 3;
  x2 = b2 << 1;
  b2 = x8 + x2;
  if (((x8 >> 2) + (x2 >> 2) + (((x8 & 0x3) + (x2 & 0x3)) >> 2)) &
      0xC0000000U) {
    ++carry2;
  }
  b2 += carry1;
  x8 = b2;
  x2 = carry1;
  if (((x8 >> 2) + (x2 >> 2) + (((x8 & 0x3) + (x2 & 0x3)) >> 2)) &
      0xC0000000U) {
    ++carry2;
  }
  num->bits[0] = b0;
  num->bits[1] = b1;
  num->bits[2] = b2;

  return (carry2 ? S21_DECIMAL_OVERFLOW : S21_DECIMAL_OK);
}

/*
  calculate the power of 10: 10^scale, where scale in [0, 28]
*/
int s21_ratio(int scale, s21_decimal *ratio) {
  int status = S21_DECIMAL_OK;

  S21_DECIMAL_COPY(ratio->bits, S21_DECIMAL_UNIT.bits);
  if (0 <= scale && scale <= 28) {
    while (scale && status == S21_DECIMAL_OK) {
      status = s21_uint96_x10(ratio);
      --scale;
    }
  } else {
    status = S21_DECIMAL_ERROR;
  }

  return (status);
}

/*
  make a bitwise shift to the left of a 96 bit unsigned number
*/
int s21_uint96_shift_left(s21_decimal *num) {
  unsigned int b0, b1, b2;
  unsigned int carry;
  int status = S21_DECIMAL_OK;

  b0 = num->bits[0];
  b1 = num->bits[1];
  b2 = num->bits[2];

  if (b0 & 0x80000000U) {
    status = S21_DECIMAL_OVERFLOW;
  }
  b2 <<= 1;
  carry = (b1 & 0x80000000U) >> 31;
  b2 |= carry;
  b1 <<= 1;
  carry = (b0 & 0x80000000U) >> 31;
  b1 |= carry;
  b0 <<= 1;
  num->bits[0] = b0;
  num->bits[1] = b1;
  num->bits[2] = b2;

  return (status);
}

/*
  set the bit with the index (idx) to the value (bit) in a decimal number
*/
int s21_setbit(s21_decimal *num, int idx, int bit) {
  int status = S21_DECIMAL_OK;
  int k, j;

  if (idx < 0 || idx > 127) {
    status = S21_DECIMAL_ERROR;
  } else {
    k = idx / 32;
    j = idx % 32;
    if (bit) {
      num->bits[k] |= (1 << j);
    } else {
      num->bits[k] &= ~(1 << j);
    }
  }

  return (status);
}

/*
  Fill the array with a bit representation of an unsigned 96-bit integer
  and return the index of the highest non-zero bit,
  if there is no such return -1.
*/
int s21_uint96_fill_bits_array(s21_decimal num, int bits_array[96]) {
  unsigned int bits;
  int last_idx = 95;

  for (int i = 0; i < 3; ++i) {
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
  one 96 bit unsigned number by another
*/
int s21_uint96_div_with_rem(s21_decimal n, s21_decimal d, s21_decimal *q,
                            s21_decimal *r) {
  int nbits[96];
  int idx = -1;
  int status = S21_DECIMAL_OK;

  S21_DECIMAL_RESET_TO_ZERO(q->bits);
  S21_DECIMAL_RESET_TO_ZERO(r->bits);
  if (d.bits[2] == 0 && d.bits[1] == 0 && d.bits[0] == 0) {
    status = S21_DECIMAL_DEVIDE_BY_ZERO;
  } else {
    idx = s21_uint96_fill_bits_array(n, nbits);
    for (; idx >= 0; --idx) {
      s21_uint96_shift_left(r);
      r->bits[0] |= nbits[idx];
      if (s21_uint96_gt_eq(*r, d)) {
        s21_uint96_sub(*r, d, r);
        s21_setbit(q, idx, 1);
      }
    }
  }

  return (status);
}

/*
  calculate the quotient of dividing
  one 96 bit unsigned number by another
*/
int s21_uint96_div(s21_decimal n, s21_decimal d, s21_decimal *q) {
  s21_decimal r;
  int status;

  status = s21_uint96_div_with_rem(n, d, q, &r);
  (void)r;

  return (status);
}

/*
  return sign bit of s21_decimal
*/
inline int s21_sign(s21_decimal *value) { return (value->bits[3] >> 31); }

/*
  return scale of s21_decimal
*/
inline int s21_scale(s21_decimal *value) {
  return ((value->bits[3] >> 16) & 0xFFU);
}

/*
  check the 96 bit unsigned number is zero
*/
inline int s21_iszero(s21_decimal *value) {
  return (value->bits[0] == 0 && value->bits[1] == 0 && value->bits[2] == 0);
}
