#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Let my son cook\n");
  pid_t pid = fork();
  if (pid) {
    printf("Child cooking...\n");
  } else {
    int rc_wait = wait(&pid);
    printf("Great\n");
  }
  return 0;
}
