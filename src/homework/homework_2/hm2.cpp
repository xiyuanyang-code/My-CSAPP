#include <Imath/half.h>
#include <cstdio>
#include <iostream>
#include <ostream>

void showBinary(const void *data, int sizeBytes, const char *typeName) {
  const unsigned char *bytes = (const unsigned char *)data;
  int count = 0;

  for (int i = sizeBytes - 1; i >= 0; i--) {
    unsigned char byte = bytes[i];
    for (int bit = 7; bit >= 0; bit--) {
      if (count > 0 && count % 4 == 0) {
        printf(" ");
      }
      printf("%d", (byte >> bit) & 1);
      count++;
    }
  }
  printf("\n");
}

#define SHOW_BINARY(var) showBinary(&(var), sizeof(var), #var)

int main() {
  Imath::half a = 1.23;
  Imath::half b = 3.14;
  Imath::half c = a + b;
  Imath::half d = a * b;
  std::cout << "a value: " << a << std::endl;
  std::cout << "b value: " << b << std::endl;
  std::cout << "c value: " << c << std::endl;
  std::cout << "d value: " << d << std::endl;
  SHOW_BINARY(a);
  SHOW_BINARY(b);
  SHOW_BINARY(c);
  SHOW_BINARY(d);
  return 0;
}