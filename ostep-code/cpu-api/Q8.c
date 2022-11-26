#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#define MSGLENGTH 100

int main(void) {
    char msg[] = "Hello child2!";
    char inBuff[MSGLENGTH];
    int fd[2];
    int pid1, pid2;

    // creat pipe to help communicate
    if(pipe(fd) < 0) {
        printf("failed to set up pipe");
    }

    pid1 = fork(); // fork the first child process
    if(pid1 > 0) {
        // in the parent process
        // fork the second child process
        pid2 = fork();
        if(pid2 > 0) {
            // in the parent process
            wait(NULL);
        } else if (pid2 == 0) {
            // in the second child process
            printf("Receiving message from child process1...\n");
            read(fd[0], inBuff, MSGLENGTH);
            printf("Received message from child process1! The message is : %s\n", inBuff);
        } else {
            printf("fork second child process failed\n");
        }
    } else if(pid1 == 0) {
        // in the first child process
        printf("Sending message to child process2...\n");
        write(fd[1], msg, strlen(msg));
    } else {
        printf("fork first child process failed\n");
    }
    return 0;
}