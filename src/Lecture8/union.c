#include <stdio.h>
typedef union {
  float f;
  unsigned u;
} bit_float_t;

float bit_2_float(unsigned u) {
  bit_float_t arg;
  arg.u = u;
  return arg.f;
}

unsigned float_2_bit(float f) {
  bit_float_t arg;
  arg.f = f;
  return arg.u;
}

int main() {
  // both for 4 bytes
  printf("The length of float: %lu\n", sizeof(float));
  printf("The length of unsigned: %lu\n", sizeof(unsigned));

  float num_1 = 0.01;
  unsigned num_2 = 20;

  printf("Casting directly: %u\n", (unsigned) num_1);
  printf("Casting directly: %f\n", (float) num_2);
  printf("Casting using float_2_bit: %u\n", float_2_bit(num_1));
  printf("Casting using bit_2_float: %f\n", bit_2_float(num_2));
  return 0;
}