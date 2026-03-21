#include <stdio.h>
int sum(int *a, int n);

int array[2] = {1, 2};

int main(){
    int val = sum(array, 2);
    printf("Current value: %d\n", val);
    return 0;
}

// run with: gcc -Og -o src/Lecture13/example_program/prog_example src/Lecture13/example_program/main.c src/Lecture13/example_program/sum.c