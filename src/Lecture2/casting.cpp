#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>

// 通用打印函数
void print_binary_generic(const void *ptr, size_t size) {
  const unsigned char *bytes = (const unsigned char *)ptr;
  for (int i = (int)size - 1; i >= 0; i--) {
    for (int j = 7; j >= 0; j--) {
      printf("%d", (bytes[i] >> j) & 1);
    }
  }
}

// 修复右值的问题 引入临时变量 _tmp
#define SHOW_BINARY(x)                                                         \
  do {                                                                         \
    __typeof__(x) _tmp = (x);                                                  \
    print_binary_generic(&_tmp, sizeof(_tmp));                                 \
  } while (0)
void simple_case() {
  int a = -1;
  int b = 0;
  if (a > b) {
    printf("-1 is bigger than 0\n");
  } else {
    printf("Nothing strange happens.\n");
  }
}

void casting_superises() {
  int a = -1;
  unsigned int b = int(0);
  if (a > b) {
    printf("-1 is bigger than 0\n");
    printf("For the normal signed int version, the value of a is: %d\n", a);
    printf("For the unsigned versions, the value of a is: %u\n", a);
  } else {
    printf("Nothing strange happens.\n");
  }

  unsigned int c = UINT_MAX;
  if (a == c) {
    printf("The value of c is equal to a\n");
    printf("For the normal unsigned int version, the value of c is: %u\n", c);
    printf("For signed int version, the value of c is: %d\n", c);
  }
}

void abs_corner_case(int number = 0) {
  int int_max = INT_MAX;
  int int_min = INT_MIN;
  printf("The maximum value of int is %d\n", int_max);
  printf("The minimum value of int is %d\n", int_min);
  printf("The abs of given number %d is %d\n", number, std::abs(number));
  // The abs of given number -2147483648 is -2147483648
  printf("%u\n", ((UINT_MAX << 1) + 1));
  assert((UINT_MAX << 1) + 1 == UINT_MAX);
}

void dangerous_operations() {
  // * the return value of sizeof is unsigned!
  for (int i = 5; i - sizeof(char) >= 0; i--) {
    printf("Entering the Loops\n");
  }
}

void sign_extensions() {
  int a = 5e8;
  for (int i = 0; i < 32; i++) {
    // for alignment only
    printf(" ");
  }
  SHOW_BINARY(a);
  printf("\n");
  printf("The size of b is %lu\n", sizeof(a));

  long long b = (long long)a;
  SHOW_BINARY(b);
  printf("\n");
  printf("The size of b is %lu\n", sizeof(b));

  int c = -5e8;
  for (int i = 0; i < 32; i++) {
    // for alignment only
    printf(" ");
  }
  SHOW_BINARY(c);
  printf("\n");
  printf("The size of c is %lu\n", sizeof(c));

  long long d = (long long)c;
  SHOW_BINARY(d);
  printf("\n");
  printf("The size of d is %lu\n", sizeof(d));
}

void sign_truncations() {
  long long a = 1e18;
  SHOW_BINARY(a);
  printf("\n");

  // do truncations
  for (int i = 0; i < 32; i++) {
    // for alignment only
    printf(" ");
  }
  int b = int(a);
  SHOW_BINARY(b);
  printf("\n");

  printf("Values of a is %lld\n", a);
  printf("Values of b is %d\n", b);
}

int main() {
  // simple_case();
  // casting_superises();
  // abs_corner_case(INT_MIN);

  // ! DANGER, will cause panic
  // dangerous_operations();

  sign_extensions();
  sign_truncations();
  return 0;
}