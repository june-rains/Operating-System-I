#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(void) {
    int rc = fork();
    if(rc < 0) {
        printf("fork child process failed\n");
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("Hello from child process, pid: %d \n", getpid());
    } else {
        wait(NULL);
        printf("Goodbye from parent process, pid: %d \n", getpid());
    }
    return 0;
}