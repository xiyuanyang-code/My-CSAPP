#include <stdio.h>
#define ZLEN 6
typedef int zip_dig[ZLEN];

void show_pointer() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9};
  printf("%p\n", arr);
  printf("%p\n", arr + 1);

  char arr_2[10] = {'1', '2', '3'};
  printf("%p\n", arr_2);
  printf("%p\n", arr_2 + 1);

  //   or another methods
  zip_dig cmu = {1, 5, 2, 1, 3};
  printf("%p\n", cmu);
  printf("%p\n", cmu + 1);

  //   this will cause damage
  //   arr += 1;
}

int main() {
  show_pointer();
  return 0;
}