#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("./Q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    char buff1[] = "contentChild\n";
    char buff2[] = "contentParent\n";
    int rc = fork();
    if(rc < 0) {
        printf("fork child process failed\n");
    } else if(rc == 0) {
        write(fd, buff1, sizeof(buff1) - 1); // remove '\0'
    } else {
        write(fd, buff2, sizeof(buff2) - 1); // remove '\0'
    }
    return 0;
}