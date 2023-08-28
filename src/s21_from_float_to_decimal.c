#include "s21_decimal.h"
#include "s21_decimal_aux.h"

static char *_fill_intpart(unsigned int mantisa, int exp, char intpart[64]);
static char *_fill_fractpart(unsigned int mantisa, int exp, char fractpart[64]);
static char *_fractpart_to_28_digits(char *fp_first, char *fp_last);
static char *_rounding_intpart(char *ip_first, char *ip_last, int carry);
static int _rounding_fractpart(char *fp_first, char *fp_last, int carry);
static void _rounding(char **ip_first, char *ip_last, char *fp_first,
                      char **fp_last);
static int _to_decimal(char *ip_first, char *ip_last, char *fp_first,
                       char *fp_last, s21_decimal *dst, int sign);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  union {
    float num;
    unsigned int bits;
  } un = {src};
  int sign, exp;
  unsigned int mantisa;
  char intpart[64], fractpart[256];
  char *ip_first, *fp_last;
  int status = S21_DECIMAL_OK;

  sign = un.bits >> 31;
  exp = ((un.bits >> 23) & 0xFFU) - 0x7F;
  mantisa = (un.bits & 0x7FFFFFU) | 0x800000U;
  if (exp > 95) {
    S21_DECIMAL_COPY(dst->bits, S21_DECIMAL_MAX.bits);
    if (sign) {
      dst->bits[3] = 0x80000000U;
    }
    status = S21_DECIMAL_ERROR;
  } else if ((0.f < src && src < 1.e-28f) || (-1.e-28f < src && src < -0.f)) {
    S21_DECIMAL_RESET_TO_ZERO(dst->bits);
    if (sign) {
      dst->bits[3] = 0x80000000U;
    }
    status = S21_DECIMAL_ERROR;
  } else if (src == 0) {
    S21_DECIMAL_RESET_TO_ZERO(dst->bits);
    if (sign) {
      dst->bits[3] = 0x80000000U;
    }
  } else {
    ip_first = _fill_intpart(mantisa, exp, intpart);
    fp_last = _fill_fractpart(mantisa, exp, fractpart);
    _rounding(&ip_first, intpart, fractpart, &fp_last);
    status = _to_decimal(ip_first, intpart, fractpart, fp_last, dst, sign);
  }

  return (status);
}

static char *_fill_intpart(unsigned int mantisa, int exp, char intpart[64]) {
  char *ip_first;

  if (exp >= 23) {
    exp -= 23;
  } else if (exp >= 0) {
    mantisa >>= 23 - exp;
    exp = 0;
  } else {
    mantisa = 0U;
    exp = 0;
  }
  for (int i = 0; i < 64; ++i) {
    intpart[i] = mantisa % 10;
    mantisa /= 10;
  }
  while (exp > 0) {
    for (int i = 0, carry = 0; i < 64; ++i) {
      intpart[i] *= 2;
      intpart[i] += carry;
      carry = intpart[i] / 10;
      intpart[i] %= 10;
    }
    --exp;
  }
  ip_first = intpart + 63;
  while (ip_first >= intpart && *ip_first == 0) {
    --ip_first;
  }
  if (ip_first < intpart) {
    ip_first = (char *)0;
  }

  return (ip_first);
}

static char *_fill_fractpart(unsigned int mantisa, int exp,
                             char fractpart[64]) {
  int carry;
  char *fp_last = (char *)0;

  if (exp < 23) {
    if (exp >= 0) {
      mantisa <<= 9 + exp;
      mantisa >>= 9 + exp;
    }
    for (int i = 23 - exp - 1; i >= 0; --i) {
      fractpart[i] = mantisa & 0x1U;
      mantisa >>= 1;
      if (!fp_last && fractpart[i]) {
        fp_last = fractpart + i;
      }
    }
    if (fp_last) {
      for (char *i = fp_last; i >= fractpart; --i) {
        carry = 0;
        for (char *j = fp_last; j >= i; --j) {
          *j *= 5;
          *j += carry;
          carry = *j / 10;
          *j %= 10;
        }
      }
      fp_last = _fractpart_to_28_digits(fractpart, fp_last);
    }
  }

  return (fp_last);
}

static char *_fractpart_to_28_digits(char *fp_first, char *fp_last) {
  int carry;
  char *ptr = fp_first + 28;

  if (ptr <= fp_last) {
    carry = *ptr / 5;
    fp_last = --ptr;
    while (carry && ptr >= fp_first) {
      *ptr += carry;
      carry = *ptr / 10;
      *ptr %= 10;
      --ptr;
    }
    while (fp_last >= fp_first && *fp_last == 0) {
      --fp_last;
    }
    if (fp_last < fp_first) {
      fp_last = (char *)0;
    }
  }

  return (fp_last);
}

static char *_rounding_intpart(char *ip_first, char *ip_last, int carry) {
  while (carry) {
    *ip_last += carry;
    carry = *ip_last / 10;
    *ip_last %= 10;
    ++ip_last;
  }
  if (ip_last > ip_first) {
    ip_first = ip_last;
  }

  return (ip_first);
}

static int _rounding_fractpart(char *fp_first, char *fp_last, int carry) {
  while (carry && fp_last >= fp_first) {
    *fp_last += carry;
    carry = *fp_last / 10;
    *fp_last %= 10;
    --fp_last;
  }

  return (carry);
}

static void _rounding(char **ip_first, char *ip_last, char *fp_first,
                      char **fp_last) {
  int carry = 0;
  int dcount = 0;
  char *ip_ptr, *fp_ptr;

  ip_ptr = *ip_first;
  while (ip_ptr >= ip_last && dcount < 7) {
    --ip_ptr;
    ++dcount;
  }
  if (dcount == 7) {
    if (ip_ptr >= ip_last) {
      carry = *ip_ptr / 5;
      ++ip_ptr;
      while (ip_last < ip_ptr) {
        *ip_last++ = 0;
      }
    } else if (*fp_last) {
      carry = *fp_first / 5;
      ip_ptr = ip_last;
    }
    *ip_first = _rounding_intpart(*ip_first, ip_ptr, carry);
    *fp_last = (char *)0;
  } else if (*fp_last) {
    if (!*ip_first) {
      *ip_first = ip_last;
    }
    fp_ptr = fp_first;
    if (!dcount) {
      while (fp_ptr <= *fp_last && *fp_ptr == 0) {
        ++fp_ptr;
      }
    }
    while (dcount < 7 && fp_ptr <= *fp_last) {
      ++fp_ptr;
      ++dcount;
    }
    if (dcount == 7 && fp_ptr <= *fp_last) {
      carry = *fp_ptr / 5;
      *fp_ptr = 0;
      *fp_last = fp_ptr--;
      carry = _rounding_fractpart(fp_first, fp_ptr, carry);
      *ip_first = _rounding_intpart(*ip_first, ip_last, carry);
      while (**fp_last == 0 && *fp_last >= fp_first) {
        --*fp_last;
      }
      if (*fp_last < fp_first) {
        *fp_last = (char *)0;
      }
    }
  }
}

static int _to_decimal(char *ip_first, char *ip_last, char *fp_first,
                       char *fp_last, s21_decimal *dst, int sign) {
  int scale = 0;
  s21_decimal tmp = {{0, 0, 0, 0}};
  int status = S21_DECIMAL_OK;

  S21_DECIMAL_RESET_TO_ZERO(dst->bits);
  while (ip_first >= ip_last) {
    tmp.bits[0] = *ip_first;
    s21_uint96_x10(dst);
    status += s21_uint96_add(*dst, tmp, dst);
    --ip_first;
  }
  if (fp_last) {
    while (fp_first <= fp_last && scale < 28) {
      tmp.bits[0] = *fp_first;
      s21_uint96_x10(dst);
      status += s21_uint96_add(*dst, tmp, dst);
      ++scale;
      ++fp_first;
    }
  }
  if (scale) {
    dst->bits[3] = scale << 16;
  }
  if (sign) {
    dst->bits[3] |= 0x80000000U;
  }

  return (status ? S21_DECIMAL_ERROR : S21_DECIMAL_OK);
}
