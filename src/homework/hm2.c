#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void showBinary(const void *data, int sizeBytes, const char *typeName) {
  const unsigned char *bytes = (const unsigned char *)data;
  int count = 0;

  for (int i = sizeBytes - 1; i >= 0; i--) {
    unsigned char byte = bytes[i];
    for (int bit = 7; bit >= 0; bit--) {
      if (count > 0 && count % 4 == 0) {
        printf(" ");
      }
      printf("%d", (byte >> bit) & 1);
      count++;
    }
  }
  printf("\n");
}

// 为不同类型提供便捷宏
#define SHOW_BINARY(var) showBinary(&(var), sizeof(var), #var)

void printBinaryAndHex16(unsigned int num) {
  for (int i = 15; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 4 == 0 && i != 0) {
      printf(" "); // 每4位加空格
    }
  }

  printf("  |  %04X\n", num & 0xFFFF);
}

void question_2() {
  unsigned char a = 0x69;
  unsigned char b = 0x55;
  printBinaryAndHex16(a);
  printBinaryAndHex16(b);
  printBinaryAndHex16(a & b);
  printBinaryAndHex16(a | b);
  printBinaryAndHex16(a ^ b);
  printBinaryAndHex16(~a);
}

void question_3() {
  short a = 15213;
  short b = 30426;
  SHOW_BINARY(a);
  SHOW_BINARY(b);
  short sum = a + b;
  short mul_ans = a * b;
  printf("The size of short type: %ld\n", sizeof(a));
  printf("a+b= %hd\n", sum);
  printf("a*b= %hd\n", mul_ans);
  SHOW_BINARY(sum);
  SHOW_BINARY(mul_ans);
}

void question_4() {
  unsigned short a = 15213;
  unsigned short b = 30426;
  SHOW_BINARY(a);
  SHOW_BINARY(b);
  unsigned short sum = a + b;
  unsigned short mul_ans = a * b;
  printf("The size of short type: %ld\n", sizeof(a));
  printf("a+b= %u\n", sum);
  printf("a*b= %u\n", mul_ans);
  SHOW_BINARY(sum);
  SHOW_BINARY(mul_ans);
}

int question_5_1(int x) { return !!(x); }

int question_5_2(int x) { return !!(~x); }

int question_5_3(int x) { return !(~(x >> 24)); }

int question_5_4(int x) { return !((x & 0xFF) ^ 0xFF); }

void question_5() {
  int x = -1;
  // 1111 1111 1111 1111 1111 1111 1111 1111

  int y = 0;
  // 0000 0000 0000 0000 0000 0000 0000 0000

  int z = 2300;
  // 0000 0000 0000 0000 0000 1000 1111 1100

  SHOW_BINARY(x);
  SHOW_BINARY(y);
  SHOW_BINARY(z);
  unsigned int mask_1 = 0xFF000000;
  // 1111 1111 0000 0000 0000 0000 0000 0000
  SHOW_BINARY(mask_1);

  unsigned int mask_2 = 0xFF - 1;
  // 0000 0000 0000 0000 0000 0000 1111 1110
  SHOW_BINARY(mask_2);

  unsigned int mask_3 = 0xFF;
  SHOW_BINARY(mask_3);

  printf("Result for x in question 5.1: %d\n", question_5_1(x));
  printf("Result for y in question 5.1: %d\n", question_5_1(y));
  printf("Result for z in question 5.1: %d\n", question_5_1(z));

  printf("Result for x in question 5.2: %d\n", question_5_2(x));
  printf("Result for y in question 5.2: %d\n", question_5_2(y));
  printf("Result for z in question 5.2: %d\n", question_5_2(z));

  printf("Result for x in question 5.3: %d\n", question_5_3(x));
  printf("Result for mask_1 in question 5.3: %d\n", question_5_3(mask_1));
  printf("Result for mask_2 in question 5.3: %d\n", question_5_3(mask_2));

  printf("Result for x in question 5.4: %d\n", question_5_4(x));
  printf("Result for mask_1 in question 5.4: %d\n", question_5_4(mask_1));
  printf("Result for mask_2 in question 5.4: %d\n", question_5_4(mask_2));
  printf("Result for mask_3 in question 5.4: %d\n", question_5_4(mask_3));
}

void question_6() {
  int num_a, num_b;
  int res_sum, res_mul;
  num_a = 0x78563412;
  num_b = 0x7F5E3B1A;
  res_sum = num_a + num_b;
  res_mul = num_a * num_b;
  printf("Small Endian: sum is %d %X, and mul is %d %X,\n", res_sum, res_sum,
         res_mul, res_mul);
  SHOW_BINARY(res_sum);
  SHOW_BINARY(res_mul);
  num_a = 0x12345678;
  num_b = 0x1A3B5E7F;
  res_sum = num_a + num_b;
  res_mul = num_a * num_b;
  printf("Big Endian: sum is %d %X, and mul is %d %X,\n", res_sum, res_sum,
         res_mul, res_mul);
  SHOW_BINARY(res_sum);
  SHOW_BINARY(res_mul);
}

void question_7() {
  int a = 0x12345678;
  short b = 0x9ABC;
  char c = 0xDE;
  unsigned char buf[8] = {0};

  memcpy(buf, &a, sizeof(a));
  SHOW_BINARY(a);
  // 0001 0010 0011 0100 0101 0110 0111 1000
  memcpy(buf + 4, &b, sizeof(b));
  SHOW_BINARY(b);
  // 1001 1010 1011 1100
  memcpy(buf + 6, &c, sizeof(c));
  SHOW_BINARY(c);
  // 1101 1110

  for (int i = 0; i < 8; i++) {
    printf("buf[%d]: 0x%02X\n", i, buf[i]);
  }
}

void question_8() {
  float num = -12.25;
  float num_2 = -12.00;
  printf("Current size of num: %ld\n", sizeof(num));
  SHOW_BINARY(num);
  SHOW_BINARY(num_2);
}

void question_10() {
  long long i;
  float num_1, num_2;
  for (i = 0; i < 10e38; i++) {
    num_1 = (float)i;
    num_2 = (float)(i + 1);
    if ((num_1) == (num_2)) {
      printf("%lld: %f, %f\n", i, num_1, num_2);
      break;
    }
  }
}

void question_12_1() {
  long l_1 = LONG_MAX;
  long l_2 = LONG_MIN;
  long l_3 = LONG_MAX - 1;
  bool expression_1 = (l_1 == (long)(double)l_1);
  bool expression_2 = (l_2 == (long)(double)l_2);
  bool expression_3 = (l_3 == (long)(double)l_3);
  printf("Current expression is %d\n", expression_1);
  printf("Current expression is %d\n", expression_2);
  printf("Current expression is %d\n", expression_3);
}

void question_12_2() {
  float f_1 = FLT_MAX;
  float f_2 = FLT_MIN;
  float f_3 = (f_1 + f_2) / 2;
  bool expression_1 = (f_1 == (float)(double)f_1);
  bool expression_2 = (f_2 == (float)(double)f_2);
  bool expression_3 = (f_3 == (float)(double)f_3);
  printf("Current expression is %d\n", expression_1);
  printf("Current expression is %d\n", expression_2);
  printf("Current expression is %d\n", expression_3);
}

void question_12_3() {
  float f_4 = NAN;
  float f_1 = FLT_MAX;
  float f_2 = FLT_MIN;
  float f_3 = (f_1 + f_2) / 2;
  bool expression_1 = (f_1 == -(-f_1));
  bool expression_2 = (f_2 == -(-f_2));
  bool expression_3 = (f_3 == -(-f_3));
  bool expression_4 = (f_4 == -(-f_4));
  printf("Current expression is %d\n", expression_1);
  printf("Current expression is %d\n", expression_2);
  printf("Current expression is %d\n", expression_3);
  printf("Current expression is %d\n", expression_4);
}

void question_12_5() {
  double d = DBL_MAX;
  double f = FLT_MAX;
  bool expression = ((d + f) - d == f);
  printf("Current expression is %d\n", expression);
}

void question_12() {
  question_12_1();
  printf("\n");
  question_12_2();
  printf("\n");
  question_12_3();
  printf("\n");
  question_12_5();
}

int main() {
  question_2();
  printf("\n\n");
  question_3();
  printf("\n\n");
  question_4();
  printf("\n\n");
  question_5();
  printf("\n\n");
  question_6();
  printf("\n\n");
  question_7();
  printf("\n\n");
  question_8();
  printf("\n\n");
  question_10();
  printf("\n\n");
  question_12();
  return 0;
}