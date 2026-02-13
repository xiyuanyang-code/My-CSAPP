#include <stddef.h>
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void show_bytes_2(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    printf("%p\t0x%.2x\n", start + i, start[i]);
  }
}

void show_int(int x) { show_bytes((byte_pointer)&x, sizeof(int)); }

void show_float(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }

void show_pointer(void *x) { show_bytes((byte_pointer)&x, sizeof(void *)); }

void show_int_2(int x) { show_bytes_2((byte_pointer)&x, sizeof(int)); }

void show_float_2(float x) { show_bytes_2((byte_pointer)&x, sizeof(float)); }

void show_pointer_2(void *x) { show_bytes_2((byte_pointer)&x, sizeof(void *)); }

int demo_1() {
  show_int(10);
  show_int(10000000);
  int a = 100;
  show_pointer(&a);
  show_float(100);
  show_float(100.0);
  return 0;
}

int demo_2() {
  show_int_2(10);
  show_int_2(10000000);
  int a = 100;
  show_pointer_2(&a);
  show_float_2(100);
  show_float_2(100.0);
  return 0;
}

int main() {
  demo_1();
  demo_2();
  return 0;
}