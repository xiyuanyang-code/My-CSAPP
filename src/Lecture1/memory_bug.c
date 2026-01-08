#include <stdio.h>

typedef struct {
  int a[2];
  double d;
} struct_t;

double fun(int i) {
  volatile struct_t s;
  s.d = 3.14;
  printf("The Size of struct_t: %lu\n", sizeof(struct_t));
  s.a[i] = 1073741824;
  return s.d;
}

int main() {
  for (int i = 0; i <= 6; i++) {
    printf("Result with i=%d: %f\n\n\n", i, fun(i));
  }
  return 0;
}

// Before: s.d = 3.140000
// Address of a[0]: 0x16fa16548
// Address of a[1]: 0x16fa1654c
// Address of d:    0x16fa16550
// Result with i=0: 3.140000


// Before: s.d = 3.140000
// Address of a[0]: 0x16fa16548
// Address of a[1]: 0x16fa1654c
// Address of d:    0x16fa16550
// Result with i=1: 3.140000


// Before: s.d = 3.140000
// Address of a[0]: 0x16fa16548
// Address of a[1]: 0x16fa1654c
// Address of d:    0x16fa16550
// Result with i=2: 3.140000


// Before: s.d = 3.140000
// Address of a[0]: 0x16fa16548
// Address of a[1]: 0x16fa1654c
// Address of d:    0x16fa16550
// Result with i=3: 2.000001


// Before: s.d = 3.140000
// Address of a[0]: 0x16fa16548
// Address of a[1]: 0x16fa1654c
// Address of d:    0x16fa16550
// Result with i=4: 3.140000


// Before: s.d = 3.140000
// Address of a[0]: 0x16fa16548
// Address of a[1]: 0x16fa1654c
// Address of d:    0x16fa16550
// Result with i=5: 3.140000


// Before: s.d = 3.140000
// Address of a[0]: 0x16fa16548
// Address of a[1]: 0x16fa1654c
// Address of d:    0x16fa16550
// Result with i=6: 3.140000


// [1]    50760 segmentation fault  "/Users/xiyuanyang/Desktop/Dev/CSAPP/Lecture1/"memory_bug