#include <stdio.h>
#include <limits.h>
#include <math.h>

void show_casting(){
    // Casting between `int`, `float`, and `double` changes bit representation.

    // 1. double/float into int: truncate fractional part (rounding towards zero)
    printf("1. double/float to int (truncate towards zero):\n");
    double d1 = 3.7;
    double d2 = -3.7;
    float f1 = 2.9f;
    float f2 = -2.9f;

    printf("   double 3.7 -> int: %d\n", (int)d1);
    printf("   double -3.7 -> int: %d\n", (int)d2);
    printf("   float 2.9 -> int: %d\n", (int)f1);
    printf("   float -2.9 -> int: %d\n", (int)f2);

    // Overflow case: out of range sets to INT_MIN (undefined behavior)
    double d_overflow = 1.0e100;
    int i_overflow = (int)d_overflow;
    printf("   double 1e100 -> int: %d (overflow, UB)\n", i_overflow);

    // NaN case: NaN sets to INT_MIN (undefined behavior)
    double d_nan = NAN;
    int i_nan = (int)d_nan;
    printf("   double NaN -> int: %d (0, UB)\n\n", i_nan);

    // 2. int into double: works as long as int has less than 53 bit word size
    printf("2. int to double (works for < 53 bits):\n");
    int i1 = 123456789;
    long long ll_large = 9007199254740992LL;  // 2^53, boundary case

    double d_from_int = (double)i1;
    double d_from_ll = (double)ll_large;

    printf("   int 123456789 -> double: %.0f (exact)\n", d_from_int);
    printf("   int64 2^53 -> double: %.0f\n", d_from_ll);

    long long ll_very_large = 9007199254740993LL;  // 2^53 + 1
    double d_very_large = (double)ll_very_large;
    printf("   int64 (2^53+1) -> double: %.0f\n\n", d_very_large);

    // 3. int into float: works as long as int has less than 23 bit word size
    printf("3. int to float (works for < 23 bits):\n");
    int i2 = 1000000;  // < 2^23, should work exactly
    int i_large = 16777216;  // 2^24, exceeds precision

    float f_from_int = (float)i2;
    float f_from_large = (float)i_large;

    printf("   int 1000000 -> float: %.0f (exact)\n", f_from_int);
    printf("   int 16777216 (2^24) -> float: %.0f\n", f_from_large);

    int i_very_large = 16777217;  // 2^24 + 1
    float f_very_large = (float)i_very_large;
    printf("   int 16777217 (2^24+1) -> float: %.0f\n", f_very_large);
}

int main() {
    show_casting();
    return 0;
}
