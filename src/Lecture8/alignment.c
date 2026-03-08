#include <stdio.h>

struct a {
  short i;
  float v;
  short j;
} a_va;

struct b {
  short i;
  short j;
  float v;
} b_va;

struct c {
  char c;
  int i;
  char d;
} c_va;

struct d {
  int i;
  char c;
  char d;
} d_va;

int main() {
  printf("The length of structure a: %ld\n", sizeof(a_va));
  printf("The length of structure b: %ld\n", sizeof(b_va));
  printf("The length of structure c: %ld\n", sizeof(c_va));
  printf("The length of structure d: %ld\n", sizeof(d_va));
}