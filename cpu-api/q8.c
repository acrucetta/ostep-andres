#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int pipefd[2];
  char buf[20];
  pipe(pipefd);

  pid_t pid = fork();
  if (pid) {
    close(pipefd[1]);
    read(pipefd[0], buf, sizeof(buf));
    printf("Child reading pipe: %s\n", buf);
    close(pipefd[0]);
  }
  pid_t pid2 = fork();
  if (pid2) {
    // Child 2 process
    close(pipefd[0]); // Close the read end of the pipe
    write(pipefd[1], "Hello, brother!", 14);
    close(pipefd[1]);
    return 0;
  }
  return 0;
}
