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

  show_limit();
  return 0;
}