#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define S21_DECIMAL_OK 0
#define S21_DECIMAL_OVERFLOW 1
#define S21_DECIMAL_UNDERFLOW 2
#define S21_DECIMAL_DEVIDE_BY_ZERO 3
#define S21_DECIMAL_ERROR 1
#define S21_DECIMAL_FALSE 0
#define S21_DECIMAL_TRUE 1

typedef struct {
  unsigned int bits[4];
} s21_decimal;

/* Arithmetic operators */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
/* Comparison operators */
int s21_is_less(s21_decimal lhs, s21_decimal rhs);
int s21_is_less_or_equal(s21_decimal lhs, s21_decimal rhs);
int s21_is_greater(s21_decimal lhs, s21_decimal rhs);
int s21_is_greater_or_equal(s21_decimal lhs, s21_decimal rhs);
int s21_is_equal(s21_decimal lhs, s21_decimal rhs);
int s21_is_not_equal(s21_decimal lhs, s21_decimal rhs);
/* Convertors */
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
/* Another functions */
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
