#include <limits.h>
#include <stdio.h>

int forward_tmp(int x) { return (x | -x); }

int forward(int x) { return forward_tmp(x) >> 31; }

void test(int x) {
  printf("The value of the forward functions of %d is %d\n", x, forward(x));
}

int main() {
  int candidates[] = {1, -1, 2, 100, -100, 0, INT_MAX, INT_MIN};
  int length = sizeof(candidates) / sizeof(candidates[0]);
  for (int i = 0; i < length; i++) {
    int candidate = candidates[i];
    test(candidate);
  }
}