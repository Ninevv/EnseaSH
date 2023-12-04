#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

#define BUFSIZE 128
#define NSECTOMSEC 1000000
#define SECTOMSEC 1000

int main(int argc, char **argv __attribute__((unused))) {

    char outbuf[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash% "; //

    char inbuf[BUFSIZE];
    int status ;
    ssize_t inlength;

    pid_t childPID;
    pid_t childtermination;
    int terminatedstatus;
    const int waitpidoption = 0;

    char* exitstr = "exit";

    struct timespec starttime;
    struct timespec finishtime;
    int clockstatus;

    write(STDOUT_FILENO, outbuf, strlen(outbuf));

    while(1){

        inlength = read(STDIN_FILENO, inbuf, BUFSIZE);
        inbuf[inlength-1] = '\0'; //replaces the end of line symbol by end of string symbol

        if(strcmp(inbuf,exitstr)==0||inlength ==0){ // exit when the input is "exit" or if ctrl+D is pressed
            sprintf(outbuf, "Bye bye...\n");
            write(STDOUT_FILENO, outbuf, strlen(outbuf));
            exit(status);
        }
        clockstatus = clock_gettime(CLOCK_REALTIME, &starttime);
        childPID = fork();
        if(childPID == 0) {

            if ((status = execlp(inbuf, inbuf, (char *) NULL)) != 0) {
                perror("execlp");
                sprintf(outbuf, "status:%d\n", status);
                write(STDOUT_FILENO, outbuf, strlen(outbuf));
                exit(status);
            }
        }

        else {
        	while((childtermination = waitpid(childPID,&terminatedstatus,waitpidoption)) ==0){};
        	clockstatus = clock_gettime(CLOCK_REALTIME, &finishtime);
        	if(WIFEXITED(terminatedstatus)){
                sprintf(outbuf, "enseash [exit:%d|%ld ms] %% ", WEXITSTATUS(terminatedstatus), ((finishtime.tv_nsec-starttime.tv_nsec)/NSECTOMSEC) + ((finishtime.tv_sec-starttime.tv_sec)*SECTOMSEC));
            }
            else{if(WIFSIGNALED(terminatedstatus)){
                    sprintf(outbuf, "enseash [sign:%d|%ld ms] %% ", WTERMSIG(terminatedstatus), ((finishtime.tv_nsec-starttime.tv_nsec)/NSECTOMSEC) + ((finishtime.tv_sec-starttime.tv_sec)*SECTOMSEC));
            }else{

            }}
        	write(STDOUT_FILENO, outbuf, strlen(outbuf));
        }
    }
    return status;
}


