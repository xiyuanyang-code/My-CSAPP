#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void unix_error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main() {
  pid_t pid;

  if ((pid = fork()) < 0) {
    // fork 失败
    char * error_message = "fork error";
    unix_error(error_message);
  } else if (pid == 0) {
    printf("Hello from CHILD process!\n");
    printf("Child PID: %d\n", getpid());
    printf("Parent PID: %d\n", getppid());
    exit(0);
  } else {
    printf("Hello from PARENT process!\n");
    printf("Parent PID: %d\n", getpid());
    printf("Child PID: %d\n", pid);

    wait(NULL);
    printf("Child process finished.\n");
  }

  return 0;
}