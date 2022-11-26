#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(void) {
    int rc = fork();
    if(rc < 0) {
        printf("failed to fork the child process\n");
    } else if (rc == 0) {
        printf("child process: hello\n");
    } else {
        sleep(3);
        printf("parent process: goodbye\n");
    }
}
