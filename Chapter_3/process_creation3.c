#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid > 0)  // pid가 0이면 childe process이므로, 0보다 크면 parent process
        wait(NULL);     // parent process 일 때, 해당 process를 wait queue로 이동. child process를 먼저 실행시킨 후 다시 돌아와 parent process를 마저 실행시킨다.
    printf("Hello Process! %d\n", pid);
}