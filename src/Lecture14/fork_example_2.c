#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

pid_t Fork(void) {
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        fprintf(stderr, "Fork error: %s\n", strerror(errno));
        exit(0);
    }
    
    return pid;
}

int main(){
  pid_t pid;
  int x = 1;
  pid = Fork();
  if (pid == 0){
    // child
    printf("Child : x=%d\n", ++x);
    exit(0);
  }

  // parent
  printf("Parent : x=%d\n", --x);
  exit(0);
}