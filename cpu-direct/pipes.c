#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_ITER 1000000

/*
 * Pipe notes:
 * - A pipe is a one-way communication channel that is established between two
 * processes.
 */

int main() {
    int pipefd1[2], pipefd2[2];
    pid_t pid;
    struct timespec start, end;

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid = fork();

    if (pid == 0) {
        // Child actions
        close(pipefd1[1]); // Close write end of pipe 1
        close(pipefd2[0]); // Close read end of pipe 2

        for (int i = 0; i < MAX_ITER; i++) {
            int counter;
            read(pipefd1[0], &counter, sizeof(int));
            counter++;
            write(pipefd2[1], &counter, sizeof(int));
        }

        close(pipefd1[0]); // Close read end of pipe 1
        close(pipefd2[1]); // Close write end of pipe 2
    } else {
        // Parent process
        close(pipefd1[0]); // Close read end of pipe 1
        close(pipefd2[1]); // Close write end of pipe 2

        int counter = 0;
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < MAX_ITER; i++) {
            write(pipefd1[1], &counter, sizeof(int));
            read(pipefd2[0], &counter, sizeof(int));
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
        time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        printf("Time taken: %f seconds\n", time_taken);
        
        // Now we divide the time taken by the number of iterations to get the time taken per
        // context switch
        double context_switch_seconds = time_taken / MAX_ITER;
        double context_switch_micros = context_switch_seconds * 1000000;
        printf("Time taken per context switch: %f ms\n", context_switch_micros);

        close(pipefd1[1]); // Close write end of pipe 1
        close(pipefd2[0]); // Close read end of pipe 2
    }

    return EXIT_SUCCESS;
}