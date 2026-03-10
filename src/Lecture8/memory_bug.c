#include <stdio.h>

typedef struct {
  int a[2];
  double d_1;
  double d_2;
} struct_t;

struct_t fun(int i) {
  // volatile 关键词声明会禁止编译器进行优化
  volatile struct_t s;
  s.d_1 = 3.14;
  s.d_2 = 4.33;
  s.a[i] = 1073741824;
  return s;
}



int main() {
  printf("The Size of struct_t: %lu\n", sizeof(struct_t));
  for (int i = 0; i <= 6; i++) {
    printf("Current (i=%d), d_1: %.10f, d_2: %.10f\n", i, fun(i).d_1, fun(i).d_2);
  }
  return 0;
}