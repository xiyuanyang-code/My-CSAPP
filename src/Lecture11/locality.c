#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 5000
#define N 5000

int sum_array_rows_1(int a[M][N]) {
  int i, j, sum = 0;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      sum += a[i][j];
    }
  }
  return sum;
}

int sum_array_rows_2(int a[M][N]) {
  int i, j, sum = 0;
  for (j = 0; j < N; j++) {
    for (i = 0; i < M; i++) {
      sum += a[i][j];
    }
  }
  return sum;
}

int main() {
  static int a[M][N];

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      a[i][j] = 1;
    }
  }

  clock_t start, end;
  double cpu_time_used;

  // 测试 sum_array_rows_1 (行优先 - 顺着内存走)
  start = clock();
  int res1 = sum_array_rows_1(a);
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Method 1 (Row-major) Result: %d, Time: %f seconds\n", res1,
         cpu_time_used);

  // 测试 sum_array_rows_2 (列优先 - 跳着内存走)
  start = clock();
  int res2 = sum_array_rows_2(a);
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Method 2 (Column-major) Result: %d, Time: %f seconds\n", res2,
         cpu_time_used);

  return 0;
}