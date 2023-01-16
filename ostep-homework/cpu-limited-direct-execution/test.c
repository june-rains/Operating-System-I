#define _GNU_SOURCE 
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>


// This is a program to test systemctl cost and context switch cost
int main() {
    /***** Test Systemctl Cost *****/
    
    // first, we need start and end time before calling system call
    struct timeval time_before, time_after;
    int fd, loops = 10000;
    fd = open("./data.input", O_RDONLY, O_CREAT);
    
    // we open a file, and assign a file descriptor to fd, now we call "read" systemctl to help us measure the cost of systemctl
    
    gettimeofday(&time_before, NULL);
    for(int i = 0; i < loops; i++) {
        // we do not really need to read, we just call, it's okay
        read(fd, NULL, 0);
    }
    gettimeofday(&time_after, NULL);

    printf("The total time cost of systemctl is %f microseconds \n", (time_after.tv_sec * 1000000 + time_after.tv_usec - time_before.tv_sec * 1000000 - time_before.tv_usec) / (float) loops); 

    /***** Test Context Switch Cost ******/

    // We need to simulate 2 process read from and write to pipe back-and-forth

    // declare 2 pipefd, note that pipefd[0] is the read end of the pipe, and pipefd[1] is the write end of the pipe
    int pipefd1[2];
    int pipefd2[2];

    // pipe method return < 0 is failure
    if(pipe(pipefd1) < 0) {
        printf("pipe 1 error \n");
        exit(1);
    }

    if(pipe(pipefd2) < 0) {
        printf("pipe 2 error \n");
        exit(1);
    }

    // when we consider context switch cost, we need restrict to a single cpu that run multiple(in this case is 2) processes
    // we can use sched_setaffinity method to realize this goal
    cpu_set_t cpu_set;

    // clear cpu_set
    CPU_ZERO(&cpu_set);
    
    // add cpu to cpu_set
    CPU_SET(0, &cpu_set);

    int rc = fork(); // rc means release-condidates
    if(rc < 0) {
        printf("fork failure \n");
        exit(1);
    } else if (rc == 0) {
        // child process
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);

        for(int i = 0; i < loops; i++) {
            // child process(1st process) write to pipefd1, and wait read from pipefd2
            write(pipefd1[0], NULL, 0);
            read(pipefd2[1], NULL, 0);
        }
    } else {
        // parent process
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);

        gettimeofday(&time_before, NULL);
        for(int i = 0; i < loops; i++) {
            // parent process(2nd process) try to read from the pipefd1, and write to the pipefd2
            read(pipefd1[1], NULL, 0);
            write(pipefd2[0], NULL, 0);
        }
        gettimeofday(&time_after, NULL);
        printf("The total time cost of context switch is %f microseconds", (time_after.tv_sec * 1000000 + time_after.tv_usec - time_before.tv_sec * 1000000 - time_before.tv_usec) / (float) loops); 
    }
    return 0;
}