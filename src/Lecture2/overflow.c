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

void print_uint_binary(unsigned int num) {
  printf("Decimal: %10u | Hex: 0x%08X | Binary: ", num, num);

  for (int i = 31; i >= 0; i--) {
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
  }
  printf("\n");
}

void show_uadd_overflow() {
  printf("\n========== Unsigned Addition Overflow ==========\n");
  printf("Using unsigned short (16 bits), Max value: %u\n\n", USHRT_MAX);

  unsigned short a = 0xFFFF;
  unsigned short b = 0x0001;
  unsigned short result = a + b;

  printf("Adding: %u + %u\n", a, b);
  printf("\nOperand a:\n");
  print_ushort_binary(a);
  printf("\nOperand b:\n");
  print_ushort_binary(b);
  printf("\nResult (wrapped around to 0):\n");
  print_ushort_binary(result);

  printf("\nExplanation: 0xFFFF + 0x0001 = 0x10000, but only lower 16 bits are "
         "kept\n");
}

void show_tadd_overflow() {
  printf("\n========== Signed Addition Overflow ==========\n");
  printf("Using short (16 bits), Range: [%d, %d]\n\n", SHRT_MIN, SHRT_MAX);

  short pos1 = 0x7FFF;
  short pos2 = 0x7FFE;
  short result1 = pos1 + pos2;

  printf("Case 1: Positive + Positive (Positive Overflow)\n");
  printf("Adding: %d + %d\n", pos1, pos2);
  printf("\nOperand a:\n");
  print_short_binary(pos1);
  printf("\nOperand b:\n");
  print_short_binary(pos2);
  printf("\nResult (overflow to negative):\n");
  print_short_binary(result1);
  printf("\n");

  short neg1 = 0x8000;
  short neg2 = 0x800E;
  short result2 = neg1 + neg2;

  printf("Case 2: Negative + Negative (Negative Overflow)\n");
  printf("Adding: %d + %d\n", neg1, neg2);
  printf("\nOperand a:\n");
  print_short_binary(neg1);
  printf("\nOperand b:\n");
  print_short_binary(neg2);
  printf("\nResult (overflow to positive):\n");
  print_short_binary(result2);
  printf("\n");
}

void show_umul_overflow() {
  printf("\n========== Unsigned Multiplication Overflow ==========\n");
  printf("Using unsigned short (16 bits), Max value: %u\n\n", USHRT_MAX);
  unsigned short a2 = 544;
  unsigned short b2 = 566;
  unsigned short result2 = a2 * b2;
  unsigned int full_result2 = (unsigned int)a2 * b2;

  printf("Multiplying: %u * %u = %u (truncated from %u)\n", a2, b2, result2,
         full_result2);
  printf("\nOperand a:\n");
  print_ushort_binary(a2);
  printf("\nOperand b:\n");
  print_ushort_binary(b2);
  printf("\nFull 32-bit product:\n");
  print_uint_binary(full_result2);
  printf("\n");
  printf("Truncated to 16 bits (only lower half):\n");
  print_ushort_binary(result2);
  printf("\n");
}

void show_tmul_overflow() {
  printf("\n========== Signed Multiplication Overflow ==========\n");
  printf("Using short (16 bits), Range: [%d, %d]\n\n", SHRT_MIN, SHRT_MAX);

  short a2 = 0x0200;
  short b2 = 0x0200;
  short result2 = a2 * b2;
  int full_result2 = (int)a2 * b2;

  printf("Case 1: Positive Overflow (Large positive numbers)\n");
  printf("Multiplying: %d * %d = %d (truncated from %d)\n", a2, b2, result2,
         full_result2);
  printf("\nOperand a:\n");
  print_short_binary(a2);
  printf("\nOperand b:\n");
  print_short_binary(b2);
  printf("\nFull 32-bit product:\n");
  print_int_binary(full_result2);
  printf("\n");
  printf("Truncated to 16 bits (only lower half):\n");
  print_short_binary(result2);
  printf("\n");

  short a3 = 0x8000;
  short b3 = 0x0002;
  short result3 = a3 * b3;
  int full_result3 = (int)a3 * b3;

  printf("Case 2: Negative Overflow (Large magnitude negative numbers)\n");
  printf("Multiplying: %d * %d = %d (truncated from %d)\n", a3, b3, result3,
         full_result3);
  printf("\nOperand a:\n");
  print_short_binary(a3);
  printf("\nOperand b:\n");
  print_short_binary(b3);
  printf("\nFull 32-bit product:\n");
  print_int_binary(full_result3);
  printf("\n");
  printf("Truncated to 16 bits (only lower half):\n");
  print_short_binary(result3);
  printf("\n");
}

int main() {
  show_uadd_overflow();
  show_tadd_overflow();
  show_umul_overflow();
  show_tmul_overflow();
  return 0;
}