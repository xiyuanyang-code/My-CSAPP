#include <stdio.h>

void swap(long *xp, long *yp) {
  // x_p 地址的值存储在临时变量 t0 中
  long t0 = *xp;
  // y_p 地址的值存储在临时变量 t1 中
  long t1 = *yp;
  // 把 t1 的值写入 x_p 的地址
  *xp = t1;
  // 把 t0 的值写入 y_p 的地址
  *yp = t0;
}

void swap_easier(long *xp, long *yp) {
  // * 只使用一个临时变量
  long temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void print_numbers(long a, long b) {
  printf("\n");
  printf("The value of a is %ld\n", a);
  printf("The value of b is %ld\n", b);
  printf("\n");
}

int main() {
  long a = 10;
  long b = 20;
  print_numbers(a, b);

  // do swap 1
  swap(&a, &b);
  print_numbers(a, b);

  // do swap 2
  swap(&a, &b);
  print_numbers(a, b);
  return 0;
}