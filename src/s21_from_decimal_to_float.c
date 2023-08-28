#include "s21_decimal_aux.h"

/* return a^k, k is integer number not less than 0 */
static float _s21_pow(float base, int k) {
  float result = 1.0;
  float a = base;

  /* INVARIANT: a^k * result = base^k */
  while (k > 0) {
    if (k % 2) {
      result *= a;
      --k;
    } else {
      a *= a;
      k /= 2;
    }
  }

  return (result);
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  float num;
  int sign, scale, idx;
  int bits_array[96];

  sign = s21_sign(&src);
  scale = s21_scale(&src);
  if (s21_iszero(&src)) {
    num = sign ? -0.0f : 0.0f;
  } else {
    idx = s21_uint96_fill_bits_array(src, bits_array);
    num = (float)bits_array[0];
    for (int i = 1; i <= idx; ++i) {
      if (bits_array[i]) {
        num += _s21_pow(2.0f, i);
      }
    }
    if (scale) {
      num /= _s21_pow(10.0f, scale);
    }
    if (sign) {
      num = -num;
    }
  }
  *dst = num;

  return (S21_DECIMAL_OK);
}
