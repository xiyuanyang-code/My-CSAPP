#include <stddef.h>
#include <stdio.h>
#define WSIZE 8 * sizeof(int)

long pcount_for(unsigned long x) {
  size_t i;
  long result = 0;
  for (i = 0; i < WSIZE; i++) {
    unsigned bit = (x >> i) & 0x1;
    result += bit;
  }
  return result;
}

long pcount_while(unsigned long x) {
  // do init
  size_t i;
  long result = 0;
  i = 0;
  while (i < WSIZE) {
    unsigned bit = (x >> i) & 0x1;
    result += bit;

    // update
    i++;
  }
  return result;
}