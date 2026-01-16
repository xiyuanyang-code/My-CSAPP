#include <stdio.h>

void print_binary(unsigned char n) {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (n >> i) & 1);
  }
}

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
  print_binary(a);
  printf(")\n");
  printf("b:      0x%02X (Binary: ", b);
  print_binary(b);
  printf(")\n");
  printf("------------------------------------\n");

  printf("AND (&): 0x%02X (Binary: ", (unsigned char)(a & b));
  print_binary(a & b);
  printf(")\n");

  printf("OR  (|): 0x%02X (Binary: ", (unsigned char)(a | b));
  print_binary(a | b);
  printf(")\n");

  printf("XOR (^): 0x%02X (Binary: ", (unsigned char)(a ^ b));
  print_binary(a ^ b);
  printf(")\n");

  printf("NOT (~a):0x%02X (Binary: ", (unsigned char)~a);
  print_binary(~a);
  printf(")\n");
}

void show_shift_operations() {
  unsigned char a = 0x41;

  printf("--- Shift Operations (unsigned char) ---\n");
  printf("Original: 0x%02X (Binary: ", a);
  print_binary(a);
  printf(")\n");

  unsigned char left_shift_result = (unsigned char)(a << 3);
  printf("Left Shift 3 positions:  0x%02X (Binary: ", left_shift_result);
  print_binary(left_shift_result);
  printf(")\n");

  unsigned char right_shift_result = (unsigned char)(a >> 2);
  printf("Right Shift 2 positions: 0x%02X (Binary: ", right_shift_result);
  print_binary(right_shift_result);
  printf(")\n");
}

void show_signed_shift_dangers() {
  // ! Undefined behaviors
  signed char a = -0x41;  // -65 in decimal
  unsigned char b = 0x41; // 65 in decimal for comparison

  printf("\n--- Signed Shift Dangers (Arithmetic vs Logical Right Shift) ---\n");

  printf("\n[SIGNED CHAR - Arithmetic Right Shift]\n");
  printf("Original: %d (0x%02X) (Binary: ", a, (unsigned char)a);
  print_binary(a);
  printf(")\n");

  signed char right_shift_2 = (signed char)(a >> 2);
  printf("Right Shift 2 positions: %d (0x%02X) (Binary: ", right_shift_2, (unsigned char)right_shift_2);
  print_binary(right_shift_2);
  printf(")\n");
  signed char right_shift_4 = (signed char)(a >> 4);
  printf("Right Shift 4 positions: %d (0x%02X) (Binary: ", right_shift_4, (unsigned char)right_shift_4);
  print_binary(right_shift_4);
  printf(")\n");

  printf("\n[UNSIGNED CHAR - Logical Right Shift]\n");
  printf("Original: %d (0x%02X) (Binary: ", b, b);
  print_binary(b);
  printf(")\n");

  unsigned char right_shift_2_u = b >> 2;
  printf("Right Shift 2 positions: %d (0x%02X) (Binary: ", right_shift_2_u, right_shift_2_u);
  print_binary(right_shift_2_u);
  printf(")\n");
}

int main() {
  // show_bit_level_operations();
  // show_logic_level_operations();
  show_shift_operations();
  show_signed_shift_dangers();
  return 0;
}