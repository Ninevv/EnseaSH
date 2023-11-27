#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char outbuf[] = "/.enseash\nWelcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash %"; //
    write(STDOUT_FILENO, outbuf, strlen(outbuf));// STDOUT_FILENO
    return 0;
}


