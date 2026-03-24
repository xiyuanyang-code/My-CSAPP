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

void fork_2() {
  printf("L0\n");
  fork();
  printf("L1\n");
  fork();
  printf("L2\n");
  fork();
  printf("L3\n");
}

void fork_4() {
  printf("L0\n");
  if (fork() != 0) {
    // * 只对父进程进行
    printf("L1\n");
    if (fork() != 0) {
      // 只对父进程执行
      printf("L2\n");
    }
  }
  printf("L3\n");
}

void fork_5() {
  printf("L0\n");
  if (fork() == 0) {
    // * 只对子进程进行
    printf("L1\n");
    if (fork() == 0) {
      // * 只对子进程执行
      printf("L2\n");
    }
  }
  printf("L3\n");
}

void fork_9_nonwait() {
  if (fork() == 0) {
    printf("L0\n");
    exit(0);
  } else {
    printf("L1\n");
    printf("L2\n");
  }
  printf("L3\n");
}

void fork_9_wait() {
  int child_status;
  if (fork() == 0) {
    printf("L0\n");
    exit(0);
  } else {
    printf("L1\n");
    wait(&child_status);
    printf("L2\n");
  }
  printf("L3\n");
}

void fork10() {
  int N = 100;
  pid_t pid[N];
  int i, child_status;

  for (i = 0; i < N; i++)
    if ((pid[i] = fork()) == 0) {
      exit(100 + i); /* Child */
    }
  for (i = 0; i < N; i++) { /* Parent */
    pid_t wpid = wait(&child_status);
    if (WIFEXITED(child_status))
      printf("Child %d terminated with exit status %d\r", wpid,
             WEXITSTATUS(child_status));
    else
      printf("Child %d terminate abnormally\n", wpid);
  }
}

void fork_1() {
  pid_t pid;
  int x = 1;
  pid = Fork();
  if (pid == 0) {
    // child
    printf("Child : x=%d\n", ++x);
    exit(0);
  }

  // parent
  printf("Parent : x=%d\n", --x);
  exit(0);
}

int main() {
  // fork_1();
  // fork_2();
  // fork_4();
  // fork_5();
  // fork_9_nonwait();
  // fork_9_wait();
  // fork10();
  return 0;
}