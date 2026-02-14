#include <stdio.h>

void paradox() {
  double x = 0.1f;
  double y = 0.2f;
  double z = 0.3f;

  printf("The sum of 0.1 + 0.2:\t%.20f\n", x + y);
  printf("The value of 0.3:\t%.20f\n", z);
  printf("Are they the same? ");
  printf((x + y == z ? "True" : "False"));
  printf("\n");
}

int main(){
    paradox();
}