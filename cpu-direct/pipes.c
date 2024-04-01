#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_ITER 1000000

int main() {
  int pipefd1[2], pipefd2[2];
  pid_t pid;
  cpu_set_t set;
  struct timespec start, end;

  if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
    perror("pipe");
    return EXIT_FAILURE;
  }

  pid = fork();

  if (pid == 0) {
    // Child actions
    close(pipefd1[1]);
    close(pipefd2[0]);
  } else {
    // Parent process
  }
  return EXIT_SUCCESS;
}
