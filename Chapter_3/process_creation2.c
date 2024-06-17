#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    printf("Hello Process! %d\n", pid); // parent process먼저 출력되며, child process의 id값을 출력한다.
                                        // child process는 child가 없으므로 0을 출력한다.

    return 0;
} 