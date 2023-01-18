#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// This is a demo program to practice pipe function

int main(int argc, char *argv[]) {
    
    int fd[2];
    char msg[BUFSIZ];

    if(argc != 2) {
        printf("Usage: %s message \n", argv[0]);
    }


    if(pipe(fd) < 0) {
        printf("pipe failure.. \n");
        exit(1);
    }
    
    int rc = fork();
    if(rc < 0) {
        printf("fork failure.. \n");
        exit(1);
    } else if(rc == 0) {
        close(fd[1]);
        // child process, we make child process to read msg
        if(read(fd[0], msg, BUFSIZ) == -1) {
            printf("can not read in child process.. \n");
            exit(1);
        } else {
            printf("child process receive the message %s \n", msg);
        }
    } else {
        close(fd[0]);
        // parent process make parent process to write msg
        if(write(fd[1], argv[1], strlen(argv[1])) == -1) {
            printf("can not write in parent process.. \n");
            exit(1);
        } else {
            printf("parent process send the message %s \n", argv[1]);
        }
        // wait(NULL);
    }
    return 1;
}