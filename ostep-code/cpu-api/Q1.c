# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>


int main(void) {
    int x = 100;
    int rc = fork();
    if(rc < 0) {
        printf("failed to fork child process\n");
    }  else if (rc == 0) {
        printf("child process's x before changing = %d \n", x);
        x = 99;
        printf("child process's x after changing = %d \n", x);
    } else {
        x = 9;
        printf("parent process's x = %d \n", x);
    }
    return -1;
}