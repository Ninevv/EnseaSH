#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 2
int main() {
    char outbuf[] = "/.enseash\nWelcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash %"; //
    char inbuf[BUFSIZE];
    int status = 0;
    write(STDOUT_FILENO, outbuf, strlen(outbuf));// STDOUT_FILENO
    //read(STDIN_FILENO, inbuf, BUFSIZE);
    //execlp("ls","ls",(char * )NULL);
    while(1){
        read(STDIN_FILENO, inbuf[:-2], BUFSIZE);//noooooon

        if(status = execlp(inbuf,inbuf,(char * )NULL)!=0){
            perror("execlp");
            sprintf(outbuf, "status:%d\n", status);
            write(STDOUT_FILENO, outbuf, strlen(outbuf));
        };
        exit(0);
    }
    return 0;
}


