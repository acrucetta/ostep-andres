
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("Parent (pid:%d)\n", (int)getpid());
  int fd = open("./q2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  if (fd == -1) {
    perror("open");
  }
  int rc = fork();
  if (rc == 0) {
    write(fd, "Child writes", 13);
  } else {
    write(fd, "Parent writes\n", 14);
  }
  close(fd);
  return 0;
}
