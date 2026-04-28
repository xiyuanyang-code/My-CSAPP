#include <float.h>
#include <limits.h>
#include <stdio.h>

void quiz(int u, int v) {
  int s, t;
  s = (int)((unsigned)u + (unsigned)v);
  t = u + v;
  if (s == t) {
    printf("They are the same!");
  } else {
    printf("They are not the same!");
  }
  printf("\n");
}

void test_casting_float(int a) {
  float b = a;
  if ((int)b == a) {
    printf("Correct for %d, %f\n", a, b);
  } else {
    printf("Incorrect for %d, %f\n", a, b);
  }
}

void test_casting_double(int a) {
  double b = a;
  if ((int)b == a) {
    printf("Correct for %d, %f\n", a, b);
  } else {
    printf("Incorrect for %d, %f\n", a, b);
  }
}

void test_casting_double_long_long(long long a) {
  double b = a;
  if ((int)b == a) {
    printf("Correct for %lld, %f\n", a, b);
  } else {
    printf("Incorrect for %lld, %f\n", a, b);
  }
}


void show_limit() {
  printf("The largest of int is %d\n", INT_MAX);
  printf("The smallest of int is %d\n", INT_MIN);
  printf("=== float 类型 ===\n");
  printf("最大的浮点数: %.10f\n", FLT_MAX);
  printf("最小的浮点数: %.10f\n", -FLT_MAX);
  printf("最小的正浮点数: %.150f\n\n", FLT_MIN);
  printf("=== double 类型 ===\n");
  printf("最大的浮点数: %.10f\n", DBL_MAX);
  printf("最小的浮点数: %.10f\n", -DBL_MAX);
  printf("最小的正浮点数: %.1050f\n", DBL_MIN);
}

int main() {
  //   int a = -10;
  //   unsigned int b = (unsigned)a;
  //   printf("%u\n", b);
  //   // will print 4294967286

  //   quiz(200, -200);
  //   quiz(200, -300);
  //   quiz(2000000000, 2000000000);

  // show_limit();

  test_casting_float(INT_MAX);
  test_casting_float(INT_MAX - 1);
  test_casting_float(INT_MAX - 2);
  test_casting_float(INT_MAX - 3);
  test_casting_float(INT_MAX - 4);
  test_casting_float(INT_MAX - 5);
  test_casting_float(INT_MIN + 1);

  test_casting_double(INT_MAX);
  test_casting_double(INT_MAX - 1);
  test_casting_double(INT_MAX - 2);
  test_casting_double(INT_MAX - 3);
  test_casting_double(INT_MAX - 4);
  test_casting_double(INT_MAX - 5);
  test_casting_double(INT_MIN + 1);

  test_casting_double_long_long(LONG_LONG_MAX);
  test_casting_double_long_long(LONG_LONG_MAX - 1);
  test_casting_double_long_long(LONG_LONG_MAX - 2);
  test_casting_double_long_long(LONG_LONG_MAX - 3);
  test_casting_double_long_long(LONG_LONG_MAX - 4);
  test_casting_double_long_long(LONG_LONG_MAX - 5);
  test_casting_double_long_long(LONG_LONG_MIN + 1);
  return 0;
}