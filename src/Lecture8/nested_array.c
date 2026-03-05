#include <stddef.h>
#include <stdio.h>
#define PCOUNT 4
#define ZLEN 6
#define UCOUNT 3
typedef int zip_dig[ZLEN];

zip_dig pgh[PCOUNT] = {
    {1, 5, 2, 0, 6}, {1, 5, 2, 1, 3}, {1, 5, 2, 1, 7}, {1, 5, 2, 2, 1}};

zip_dig cmu = {1, 5, 2, 1, 3};
zip_dig mit = {0, 2, 1, 3, 9};
zip_dig ucb = {9, 4, 5, 2, 0};

int *univ[UCOUNT] = {mit, cmu, ucb};
// univ 也是一个二维数组（二维指针），在这里表示成一个一维指针的数组

int *get_pgh_zip(int index) { return pgh[index]; }

int get_pgh_digit(int index, int dig) { return pgh[index][dig]; }

int get_univ_digit(size_t index, size_t digit) { return univ[index][digit]; }