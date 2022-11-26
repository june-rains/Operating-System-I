#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

int main(void) {
    int status, pid;
    int rc = fork();
    if(rc < 0) {
        printf("fork child process failed\n");
    } else if (rc == 0) {
        int p = wait(NULL);
        printf("Hello from child (%d), p = %d\n", getpid(), p);
        exit(0);
    } else {
        pid = wait(&status); 
        if(WIFEXITED(status)) {
            printf("normal termination of child (%d), exit status = %d\n", pid, WEXITSTATUS(status));
        }
        printf("Goodbye from parent (%d)\n", getpid());
    }
    return 0;
}