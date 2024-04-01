#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char *argv[]) {
  struct timeval start_t, end_t;

  gettimeofday(&start_t, NULL);

  // system call
  char message[] = "Howdy!";
  syscall(SYS_write, 1, message, sizeof(message)-1);
 
  gettimeofday(&end_t, NULL);

  // Elapsed time in MS
  long seconds = end_t.tv_sec - start_t.tv_sec;
  long microseconds = end_t.tv_usec - start_t.tv_usec;

  double micros = (seconds * 1000000) + (microseconds);
  printf("Elapsed time is %.3f microseconds\n", micros);
  
  return EXIT_SUCCESS;
}

