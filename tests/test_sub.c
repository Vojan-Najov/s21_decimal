#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

static s21_decimal num1[] = {
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // i= 0: 2.5
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // i= 1: 0
    {{0x00000000, 0x00000000, 0x00000000, 0x80010000}},  // i= 2: 0.0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // i= 3: 0
    {{0x00000000, 0x00000000, 0x00000000, 0x80010000}},  // i= 4: 0.0
    {{0x00000001, 0x00000000, 0x00000000,
      0x800E0000}},  // i= 5: -0.00000000000001
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // i= 6: 2.5
    {{0x00000183, 0x00000000, 0x00000000, 0x00020000}},  // i= 7: 3.87
    {{0x14490831, 0x00048E23, 0x00000000,
      0x00070000}},  // i= 8: 128218122.2172721
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // i= 9: 1
    {{0x77D5E3AA, 0x0000011C, 0x00000000, 0x00060000}},  // i=10: 1221781.218218
    {{0x80000000, 0x80000000, 0x80000000,
      0x801C0000}},  // i=11: -3.9614081266355540835774234624
    {{0x80000000, 0x80000000, 0x80000000,
      0x000E0000}},  // i=12: 396140812663555.40835774234624
    {{0x00000001, 0x00000000, 0x00000000,
      0x001C0000}},  // i=13: 0.0000000000000000000000000001
    {{0x000F4240, 0x00000000, 0x00000000,
      0x001C0000}},  // i=14: 0.0000000000000000000001000000
    {{0x80000000, 0x80000000, 0x80000000,
      0x00000000}},  // i=15: 39614081266355540835774234624
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00010000}},  // i=16: 7922816251426433759354395033.5
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // i=17: 79228162514264337593543950335
    {{0x1422CF6C, 0x000001FC, 0x00000000,
      0x80030000}},  // i=18: -2182181212.012
    {{0x2564B1EA, 0x3927F1F3, 0x041C50D7,
      0x000B0000}},  // i=19: 12721717217217217.21821901290
    {{0x0001869F, 0x00000000, 0x00000000, 0x00050000}},  // i=20: 0.99999
    {{0x0098967E, 0x00000000, 0x00000000, 0x80060000}},  // i=21: -9.999998
    {{0x000000CF, 0x00000000, 0x00000000, 0x00010000}},  // i=22: 20.7
    {{0x0707E3C5, 0x002D8D61, 0x00000000,
      0x80090000}},  // i=23: -12821821.821281221
    {{0x846A4B4C, 0x0000012A, 0x00000000, 0x00080000}},  // i=24: 12821.21812812
    {{0x000035A3, 0x00000000, 0x00000000,
      0x00170000}},  // i=25: 0.00000000000000000013731
    {{0x79353447, 0x00000004, 0x00000000, 0x00010000}},  // i=26: 1921339911.1
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=27: -79228162514264337593543950333
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=28: -79228162514264337593543950333
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=29: -79228162514264337593543950333
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=30: -79228162514264337593543950334
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=31: -79228162514264337593543950334
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=32: -79228162514264337593543950334
    {{0x25D10992, 0xC0F1C9E2, 0x00000075,
      0x000D0000}},  // i=33: 217217217.2121821219218
    {{0x05D6E6CB, 0x00000000, 0x00000000, 0x00000000}},  // i=34: 97969867
    {{0xCC392EC8, 0x000490A0, 0x00000000,
      0x00000000}},  // i=35: 1284920202309320
    {{0x10C2F579, 0x00000000, 0x00000000, 0x80050000}},  // i=36: -2812.12281
    {{0x00000190, 0x00000000, 0x00000000, 0x80000000}},  // i=37: -400
};

static s21_decimal num2[] = {
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // i= 0: 2.5
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // i= 1: 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // i= 2: 0
    {{0x00000000, 0x00000000, 0x00000000, 0x80010000}},  // i= 3: 0.0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // i= 4: 0
    {{0x00000006, 0x00000000, 0x00000000,
      0x000F0000}},  // i= 5: 0.000000000000006
    {{0x00000064, 0x00000000, 0x00000000, 0x00000000}},  // i= 6: 100
    {{0x00004DA6, 0x00000000, 0x00000000, 0x00020000}},  // i= 7: 198.78
    {{0x164214B7, 0x00000028, 0x00000000, 0x00040000}},  // i= 8: 17217212.1271
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // i= 9: 2.5
    {{0x00212155, 0x00000000, 0x00000000, 0x00070000}},  // i=10: 0.2171221
    {{0x80000000, 0x80000000, 0x80000000,
      0x801C0000}},  // i=11: -3.9614081266355540835774234624
    {{0x80000000, 0x80000000, 0x80000000,
      0x000E0000}},  // i=12: 396140812663555.40835774234624
    {{0x00000001, 0x00000000, 0x00000000,
      0x001C0000}},  // i=13: 0.0000000000000000000000000001
    {{0x000186A0, 0x00000000, 0x00000000,
      0x00140000}},  // i=14: 0.00000000000000100000
    {{0x00000000, 0x00000000, 0x00000000, 0x000A0000}},  // i=15: 0.0000000000
    {{0x00000005, 0x00000000, 0x00000000, 0x00010000}},  // i=16: 0.5
    {{0x00000000, 0x00000000, 0x00000000, 0x000A0000}},  // i=17: 0.0000000000
    {{0xF96C01C5, 0x0007B6B6, 0x00000000,
      0x800B0000}},  // i=18: -21712.21821882821
    {{0x00033F4A, 0x00000000, 0x00000000, 0x000C0000}},  // i=19: 0.000000212810
    {{0x00000001, 0x00000000, 0x00000000, 0x00050000}},  // i=20: 0.00001
    {{0x00000002, 0x00000000, 0x00000000, 0x80060000}},  // i=21: -0.000002
    {{0x00003F86, 0x00000000, 0x00000000,
      0x00160000}},  // i=22: 0.0000000000000000016262
    {{0x058FEC8A, 0x00000000, 0x00000000, 0x00050000}},  // i=23: 933.18282
    {{0x0081787B, 0x00000000, 0x00000000, 0x80080000}},  // i=24: -0.08484987
    {{0x0001F8A8, 0x00000000, 0x00000000, 0x00030000}},  // i=25: 129.192
    {{0xD927FFFF, 0xE1003B28, 0x00000004,
      0x00140000}},  // i=26: 0.89999999999999999999
    {{0x00000005, 0x00000000, 0x00000000, 0x00010000}},  // i=27: 0.5
    {{0x00000033, 0x00000000, 0x00000000, 0x00020000}},  // i=28: 0.51
    {{0x00000031, 0x00000000, 0x00000000, 0x00020000}},  // i=29: 0.49
    {{0x00000005, 0x00000000, 0x00000000, 0x00010000}},  // i=30: 0.5
    {{0x00000033, 0x00000000, 0x00000000, 0x00020000}},  // i=31: 0.51
    {{0x00000031, 0x00000000, 0x00000000, 0x00020000}},  // i=32: 0.49
    {{0x2B1BA438, 0x0022C51B, 0x00000000,
      0x00060000}},  // i=33: 9786869686.182968
    {{0x0365445B, 0x00000000, 0x00000000, 0x000C0000}},  // i=34: 0.000056968283
    {{0x13F6BD6D, 0x1738423E, 0x00000000,
      0x000D0000}},  // i=35: 167316.0095958482285
    {{0x10C44951, 0x00000000, 0x00000000, 0x80030000}},  // i=36: -281299.281
    {{0x00000190, 0x00000000, 0x00000000, 0x80000000}},  // i=37: -400
};

static s21_decimal result[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00010000}},  // i= 0: 0.0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // i= 1: 0
    {{0x00000000, 0x00000000, 0x00000000, 0x80010000}},  // i= 2: 0.0
    {{0x00000000, 0x00000000, 0x00000000, 0x00010000}},  // i= 3: 0.0
    {{0x00000000, 0x00000000, 0x00000000, 0x80010000}},  // i= 4: 0.0
    {{0x00000010, 0x00000000, 0x00000000,
      0x800F0000}},  // i= 5: -0.000000000000016
    {{0x000003CF, 0x00000000, 0x00000000, 0x80010000}},  // i= 6: -97.5
    {{0x00004C23, 0x00000000, 0x00000000, 0x80020000}},  // i= 7: -194.91
    {{0x22281D59, 0x0003F18C, 0x00000000,
      0x00070000}},  // i= 8: 111000910.0901721
    {{0x0000000F, 0x00000000, 0x00000000, 0x80010000}},  // i= 9: -1.5
    {{0xAE39C34F, 0x00000B1C, 0x00000000,
      0x00070000}},  // i=10: 1221781.0010959
    {{0x00000000, 0x00000000, 0x00000000,
      0x801C0000}},  // i=11: 0.0000000000000000000000000000
    {{0x00000000, 0x00000000, 0x00000000,
      0x000E0000}},  // i=12: 0.00000000000000
    {{0x00000000, 0x00000000, 0x00000000,
      0x001C0000}},  // i=13: 0.0000000000000000000000000000
    {{0x4E635DC0, 0x00000918, 0x00000000,
      0x801C0000}},  // i=14: -0.0000000000000009999999000000
    {{0x80000000, 0x80000000, 0x80000000,
      0x00000000}},  // i=15: 39614081266355540835774234624
    {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00010000}},  // i=16: 7922816251426433759354395033.0
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // i=17: 79228162514264337593543950335
    {{0x3D3DEA3B, 0xD45ACA59, 0x0000000B,
      0x800B0000}},  // i=18: -2182159499.79378117179
    {{0x75EBB3DA, 0x3B8F737F, 0x291B2868,
      0x000C0000}},  // i=19: 12721717217217217.218218800090
    {{0x0001869E, 0x00000000, 0x00000000, 0x00050000}},  // i=20: 0.99998
    {{0x0098967C, 0x00000000, 0x00000000, 0x80060000}},  // i=21: -9.999996
    {{0x035FC07A, 0x7E1382FF, 0x00002BD5,
      0x00160000}},  // i=22: 20.6999999999999999983738
    {{0x4D0FB265, 0x002D8E3A, 0x00000000,
      0x80090000}},  // i=23: -12822755.004101221
    {{0x84EBC3C7, 0x0000012A, 0x00000000, 0x00080000}},  // i=24: 12821.30297799
    {{0x827FCA5D, 0x3C3F28D0, 0x000AAFBF,
      0x80170000}},  // i=25: -129.19199999999999999986269
    {{0xDA380000, 0x5C68A936, 0x3E14F384,
      0x00130000}},  // i=26: 1921339910.2000000000000000000
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=27: -79228162514264337593543950334
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=28: -79228162514264337593543950334
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=29: -79228162514264337593543950333
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=30: -79228162514264337593543950334
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=31: -79228162514264337593543950335
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // i=32: -79228162514264337593543950334
    {{0x1B79E26E, 0xB810475F, 0x00001443,
      0x800D0000}},  // i=33: -9569652468.9707858780782
    {{0x47DE6BA5, 0x4F9AE2F8, 0x00000005,
      0x000C0000}},  // i=34: 97969866.999943031717
    {{0x6E564293, 0x510205DD, 0x29849C5D,
      0x000D0000}},  // i=35: 1284920202142003.9904041517715
    {{0x7BE9AE2B, 0x00000006, 0x00000000, 0x00050000}},  // i=36: 278487.15819
    {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},  // i=37: 0
};

static s21_decimal err_num1[] = {
    {{0x00000006, 0x00000000, 0x00000000, 0x80010000}},  // -0.6
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 10
};

static s21_decimal err_num2[] = {
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593543950335
};

static int err_result[] = {
    2,
    2,
    1,
    1,
};

START_TEST(test) {
  for (size_t i = 0; i < sizeof(num1) / sizeof(s21_decimal); ++i) {
    // printf("i = %zu\n", i);
    s21_decimal tmp;
    int ret = s21_sub(num1[i], num2[i], &tmp);
    // printf("%08x %08x %08x %08x\n",
    //	tmp.bits[3], tmp.bits[2], tmp.bits[1], tmp.bits[0]);
    // printf("%08x %08x %08x %08x\n",
    //	result[i].bits[3],
    // result[i].bits[2],result[i].bits[1],result[i].bits[0]); printf("\n");
    ck_assert_int_eq(tmp.bits[0], result[i].bits[0]);
    ck_assert_int_eq(tmp.bits[1], result[i].bits[1]);
    ck_assert_int_eq(tmp.bits[2], result[i].bits[2]);
    ck_assert_int_eq(tmp.bits[3], result[i].bits[3]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

START_TEST(error_test) {
  for (size_t i = 0; i < sizeof(err_num1) / sizeof(s21_decimal); ++i) {
    s21_decimal tmp;
    int ret = s21_sub(err_num1[i], err_num2[i], &tmp);
    if (tmp.bits[0] == 0) {
      tmp.bits[0] = 1;
    }
    ck_assert_int_eq(ret, err_result[i]);
  }
}

Suite *suite_sub(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sub");
  tc = tcase_create("s21_sub");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, test);
    tcase_add_test(tc, error_test);
    suite_add_tcase(s, tc);
  }

  return (s);
}
