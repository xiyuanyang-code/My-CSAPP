#include <stddef.h>
#include <stdio.h>
void sum_rows1(double *a, double *b, long n) {
  long i, j;
  for (i = 0; i < n; i++) {
    // 频繁的对数组 b 进行读和写的操作
    b[i] = 0;
    for (j = 0; j < n; j++) {
      b[i] += a[i * n + j];
      // * 但是编译器无法自动优化这一点！
      // * 他必须要做最坏的打算: b 变量可能对程序全局的运行产生影响
    }
  }
}

void sum_rows2(double *a, double *b, long n) {
  long i, j;
  for (i = 0; i < n; i++) {
    double val = 0;
    for (j = 0; j < n; j++) {
      val += a[i * n + j];
    }
    b[i] = val;
  }
}

void print_rows(double *array, size_t length) {
  size_t i;
  for (i = 0; i < length; i++) {
    printf("array[%ld]: %f\n", i, array[i]);
  }
}

int main() {
  double a[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
  sum_rows1(a, a + 2, 2);
  print_rows(a, 10);
  printf("\n\n");

  double c[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
  print_rows(c, 10);
  sum_rows2(c, c + 2, 2);
}
