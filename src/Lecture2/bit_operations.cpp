#include "limits.h"
#include "stdio.h"

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

void show_logic_level_operations() {
  unsigned char a = 0x41;
  unsigned char b = 0x00;
  unsigned char c = 0x69;
  unsigned char d = 0x55;

  printf("--- Logic Level Operations (char) ---\n");

  printf("!0x%02X to 0x%02X\n", a, !a);
  printf("!0x%02X to 0x%02X\n", b, !b);

  printf("!!0x%02X ➙  0x%02X\n", a, !!a);

  printf("0x%02X && 0x%02X is 0x%02X\n", c, d, (unsigned char)(c && d));
  printf("0x%02X || 0x%02X is 0x%02X\n", c, d, (unsigned char)(c || d));

  // * early terminations
  int val = 100;
  int *p = &val;
  int *null_ptr = NULL;

  if (p && *p) {
    printf("p is safe to access: *p = %d\n", *p);
  }

  if (null_ptr && *null_ptr) {
    printf("This will not print.\n");
  } else {
    printf("null_ptr detected! Short-circuit prevented a crash.\n");
  }
}

void show_bit_level_operations() {
  unsigned char a = 0x41;
  unsigned char b = 0x55;

  printf("Inputs:\n");
  printf("a:      0x%02X (Binary: ", a);
  SHOW_BINARY(a);
  printf(")\n");
  printf("b:      0x%02X (Binary: ", b);
  SHOW_BINARY(b);
  printf(")\n");
  printf("------------------------------------\n");

  printf("AND (&): 0x%02X (Binary: ", (unsigned char)(a & b));
  SHOW_BINARY(a & b);
  printf(")\n");

  printf("OR  (|): 0x%02X (Binary: ", (unsigned char)(a | b));
  SHOW_BINARY(a | b);
  printf(")\n");

  printf("XOR (^): 0x%02X (Binary: ", (unsigned char)(a ^ b));
  SHOW_BINARY(a ^ b);
  printf(")\n");

  printf("NOT (~a):0x%02X (Binary: ", (unsigned char)~a);
  SHOW_BINARY(~a);
  printf(")\n");
}

void show_shift_operations(char number = 0x41, int left_shift_size = 0,
                           int right_shift_size = 0) {
  printf("--- Shift Operations (unsigned char) ---\n");
  printf("Original: 0x%02X (Binary: ", number);
  SHOW_BINARY(number);
  printf(")\n");

  unsigned char left_shift_result = (unsigned char)(number << left_shift_size);
  printf("Left Shift %d positions:  0x%02X (Binary: ", left_shift_size,
         left_shift_result);
  SHOW_BINARY(left_shift_result);
  printf(")\n");

  unsigned char right_shift_result =
      (unsigned char)(number >> right_shift_size);
  printf("Right Shift %d positions: 0x%02X (Binary: ", right_shift_size,
         right_shift_result);
  SHOW_BINARY(right_shift_result);
  printf(")\n");
}

void show_signed_shift_dangers() {
  // ! Undefined behaviors
  signed char a = -0x41;  // -65 in decimal
  unsigned char b = 0x41; // 65 in decimal for comparison

  printf(
      "\n--- Signed Shift Dangers (Arithmetic vs Logical Right Shift) ---\n");

  printf("\n[SIGNED CHAR - Arithmetic Right Shift]\n");
  printf("Original: %d (0x%02X) (Binary: ", a, (unsigned char)a);
  SHOW_BINARY(a);
  printf(")\n");

  signed char right_shift_2 = (signed char)(a >> 2);
  printf("Right Shift 2 positions: %d (0x%02X) (Binary: ", right_shift_2,
         (unsigned char)right_shift_2);
  SHOW_BINARY(right_shift_2);
  printf(")\n");
  signed char right_shift_4 = (signed char)(a >> 4);
  printf("Right Shift 4 positions: %d (0x%02X) (Binary: ", right_shift_4,
         (unsigned char)right_shift_4);
  SHOW_BINARY(right_shift_4);
  printf(")\n");

  printf("\n[UNSIGNED CHAR - Logical Right Shift]\n");
  printf("Original: %d (0x%02X) (Binary: ", b, b);
  SHOW_BINARY(b);
  printf(")\n");

  unsigned char right_shift_2_u = b >> 2;
  printf("Right Shift 2 positions: %d (0x%02X) (Binary: ", right_shift_2_u,
         right_shift_2_u);
  SHOW_BINARY(right_shift_2_u);
  printf(")\n");
}

void show_integers(short number) {
  printf("\n--- Integer Representations (short: 16 bits) ---\n");

  printf("\n[Input Number]\n");
  printf("Value: %d (0x%04hX) (Binary: ", number, number);
  SHOW_BINARY(number);
  printf(")\n");

  printf("\n[Special Values]\n");

  unsigned short max_unsigned_short = 0xFFFF;
  printf("Max unsigned short: %6hu (0x%04hX) (Binary: ", max_unsigned_short,
         max_unsigned_short);
  SHOW_BINARY(max_unsigned_short);
  printf(")\n");

  short max_short = 0x7FFF;
  printf("Max signed short:   %6hd (0x%04hX) (Binary: ", max_short, max_short);
  SHOW_BINARY(max_short);
  printf(")\n");

  short min_short = 0x8000;
  printf("Min signed short:   %6hd (0x%04hX) (Binary: ", min_short, min_short);
  SHOW_BINARY(min_short);
  printf(")\n");

  short minus_1 = -1;
  printf("Minus one for short (-1):     %6hd (0x%04hX) (Binary: ", minus_1,
         (unsigned short)minus_1);
  SHOW_BINARY(minus_1);
  printf(")\n");

  short zero = 0;
  printf("Zero (0):           %6hd (0x%04hX) (Binary: ", zero, zero);
  SHOW_BINARY(zero);
  printf(")\n");
}

int main() {
  // show_bit_level_operations();
  // show_logic_level_operations();
  show_shift_operations();
  // 0 for shifting 8
  show_shift_operations(0x41, 8, 8);

  // attention it is UB
  show_shift_operations(-0x41, 8, 8);
  show_signed_shift_dangers();

  show_integers(32);
  printf("Int max: %d\n", INT_MAX);
  printf("Int min: %d\n", INT_MIN);

  return 0;
}