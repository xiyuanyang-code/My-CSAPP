#include <stddef.h>
#define ZLEN 6
typedef int zip_dig[ZLEN];

int get_digit(zip_dig z, int digit) { return z[digit]; }

void zincr(zip_dig z) {
  size_t i;
  for (i = 0; i < ZLEN; i++) {
    z[i]++;
  }
}

void zincr_2(zip_dig z) {
  size_t i;
  for (i = 0; i < ZLEN; i++) {
    ++z[i];
  }
}