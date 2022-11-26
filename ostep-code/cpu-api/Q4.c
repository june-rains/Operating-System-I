#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(void) {
    int rc = fork();
    char * argv[] = {"ls", "-l", NULL};
    char * envp[] = {NULL};
    if(rc < 0) {
        printf("failed to fork the child process");
    } else if(rc == 0){
        // execl("/bin/ls", "ls", "-l", (char  *) NULL);
        // execle("/bin/ls", "ls", "-l", (char *) NULL, envp);
        // execlp("ls", "ls", "-l", (char  *) NULL);
        // execv("/bin/ls", argv);
        execvp("ls", argv);
        // execvpe("ls", argv, envp);
    } else {
        sleep(2);
        printf("parent process: goodbye\n");
    }
    return 0;
}