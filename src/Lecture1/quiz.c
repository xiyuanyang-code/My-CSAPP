#include <stdio.h>
int main(){
    int a = -10;
    unsigned int b = (unsigned) a;
    printf("%u", b);
    // will print 4294967286
    return 0;
}