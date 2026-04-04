#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int sig) {
  printf("Custom defined signal handler");
  exit(0);
}

int main() {
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    printf("Signal Error");
  }

  pause();
  return 0;
}