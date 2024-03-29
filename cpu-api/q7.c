#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Let my son cook\n");
  int status;
  pid_t pid = fork();
  if (pid) {
    printf("Child closing...\n");
    if (fclose(stdout) != 0) { // Close stdout
      perror("Error closing stdout");
      return 1;
    }
  }
  printf("No printing!");
  return 0;
}
