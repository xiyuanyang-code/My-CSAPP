#include <limits.h>
#include <stdio.h>

void print_short_binary(short num) {
  printf("Decimal: %6d | Hex: 0x%04X | Binary: ", num, (unsigned short)num);

  for (int i = 15; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 4 == 0 && i != 0) {
      printf(" ");
    }
  }
  printf("\n");
}

void print_ushort_binary(unsigned short num) {
  printf("Decimal: %6u | Hex: 0x%04X | Binary: ", num, num);

  for (int i = 15; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 4 == 0 && i != 0) {
      printf(" ");
    }
  }
  printf("\n");
}

void print_int_binary(int num) {
  printf("Decimal: %11d | Hex: 0x%08X | Binary: ", num, (unsigned int)num);

  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 4 == 0 && i != 0) {
      printf(" ");
    }
    if (i == 16) {
      printf(" | ");
    }
  }
  printf("\n");
}

void print_uint_binary(unsigned int num) {
  printf("Decimal: %10u | Hex: 0x%08X | Binary: ", num, num);

  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 4 == 0 && i != 0) {
      printf(" ");
    }
    if (i == 16) {
      printf(" | ");
    }
  }
  printf("\n");
}

void show_signed_vs_unsigned_multiplication() {
  unsigned short us_a = 0xEA61;
  unsigned short us_b = 0xD430;
  unsigned int us_result = (unsigned int)us_a * us_b;

  // 实际会产生溢出行为 但是使用十六进制的字面量来避免编译器警告
  short s_a = 0xEA61;
  short s_b = 0xD430;
  int s_result = (int)s_a * s_b;

  printf("UNSIGNED INTERPRETATION:\n");
  printf("Operand a (as unsigned):\n");
  print_ushort_binary(us_a);
  printf("\nOperand b (as unsigned):\n");
  print_ushort_binary(us_b);
  printf("\nExtended to 32-bit (zero extension):\n");
  print_uint_binary((unsigned int)us_a);
  printf("\nFull 32-bit product:\n");
  print_uint_binary(us_result);
  printf("\n");

  printf("SIGNED INTERPRETATION:\n");
  printf("Operand a (as signed):\n");
  print_short_binary(s_a);
  printf("\nOperand b (as signed):\n");
  print_short_binary(s_b);
  printf("\nExtended to 32-bit (SIGN extension):\n");
  print_int_binary((int)s_a);
  printf("\nFull 32-bit product:\n");
  print_int_binary(s_result);
  printf("\n");

  printf("The sum value of two original unsigned values:\n");
  unsigned short us_add_result = us_a + us_b;
  print_ushort_binary(us_add_result);
  printf("The diff of multiplication result (Full 32-bit product):\n");
  unsigned int diff = us_result - s_result;
  for (int i = 31; i >= 0; i--) {
    printf("%d", (diff >> i) & 1);
    if (i % 4 == 0 && i != 0) {
      printf(" ");
    }
    if (i % 16 == 0 && i != 0) {
      printf("| ");
    }
  }
  printf("\n");
}

int main() {
  show_signed_vs_unsigned_multiplication();
  return 0;
}
