#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFSIZE 128

int main(int argc, char **argv __attribute__((unused))) {
    char outbuf[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash% "; //
    char inbuf[BUFSIZE];
    char res[BUFSIZE];
    int status ;
    ssize_t inlength;
    pid_t childPID;
    pid_t childtermination;
    char* terminatedstatus;
    const int witpidoption = 0;

    write(STDOUT_FILENO, outbuf, strlen(outbuf));
    //read(STDIN_FILENO, inbuf, BUFSIZE);
    //execlp("ls","ls",(char * )NULL);

    while(1){
        inlength = read(STDIN_FILENO, inbuf, BUFSIZE);
        inbuf[inlength-1] = '\0';

        /*char debug1[BUFSIZE];
        sprintf(debug1,"length: %d\n", inlength);
        write(STDOUT_FILENO, debug1, strlen(debug1));*/

        childPID = fork();
        if(childPID == 0) { // child process
            if ((status = execlp(inbuf, inbuf, (char *) NULL)) != 0) {
                perror("execlp");
                sprintf(outbuf, "status:%d\n", status);
                write(STDOUT_FILENO, outbuf, strlen(outbuf));
            };
        }
        else { //parent process
            while((childtermination = waitpid(childPID,terminatedstatus,witpidoption)) ==0){};
            sprintf(outbuf, "enseash%% ");
            write(STDOUT_FILENO, outbuf, strlen(outbuf));
        }
    }
    return 0;
}


