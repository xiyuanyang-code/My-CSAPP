#include "limits.h"
#include "stdio.h"

int get_negative_value(int x) { return (~x + 1); }

int main() {
  int a = 10;
  printf("Normal cases for int numbers:\n");
  printf("The negative number of %d is %d\n", a, get_negative_value(a));

  int b = INT_MIN;
  int c = INT_MAX;
  printf("Special cases for TMIN\n");
  printf("The negative number of %d is %d\n", b, get_negative_value(b));
  printf("The negative number of %d is %d\n", c, get_negative_value(c));
  return 0;
}