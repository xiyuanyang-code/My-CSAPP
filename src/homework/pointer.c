#include <stdio.h>

int main() {
  char arr[10] = {'1', '2', '3', '4', '5', '5', '6', '7', '8', '9'};
  int i = 0;
  for (; i < 10; i++) {
    printf("arr[%d]: %p\n", i, arr + i);
  }
  return 0;
}