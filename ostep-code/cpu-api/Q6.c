#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(void) {
    int status, pid;
    int rc = fork();
    if(rc < 0) {
        printf("fork child process failed\n");
    } else if (rc == 0) {
        printf("Hello from child process(pid : %d)\n", getpid());
    } else {
        pid = waitpid(rc, &status, WUNTRACED);
        if(WIFEXITED(status)) {
            printf("normal termination of child (%d), exit status = %d\n", pid, WEXITSTATUS(status));
        }
        printf("Goodbye from parent process\n");
    }



}