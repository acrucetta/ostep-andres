
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_or_die() {
  int rc = wait(NULL);
  assert(rc > 0);
}

int fork_or_die() {
  int rc = fork();
  assert(rc > 0);
  return rc;
}

int main(int argc, char *argv[]) {
  int x = 0;
  x = 100;
  printf("Parent (pid:%d)\n", (int)getpid());
  printf("Parent X:%i\n", x);
  int rc = fork();
  if (rc == 0) {
    printf("Child (pid:%d)\n", (int)getpid());
    x = 200;
    printf("Child Process: %i\n", x);
  }
  printf("Post Child: %i\n", x);
  return 0;
}
