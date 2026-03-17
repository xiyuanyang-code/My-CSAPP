#include <stdio.h>

void printBinaryAndHex16(unsigned int num) {
  for (int i = 15; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 4 == 0 && i != 0) {
      printf(" "); // 每4位加空格
    }
  }

  printf("  |  %04X\n", num & 0xFFFF);
}

void question_2() {
  unsigned char a = 0x69;
  unsigned char b = 0x55;
  printBinaryAndHex16(a);
  printBinaryAndHex16(b);
  printBinaryAndHex16(a & b);
  printBinaryAndHex16(a | b);
  printBinaryAndHex16(a ^ b);
  printBinaryAndHex16(~a);
}

int main() {
  question_2();
  return 0;
}