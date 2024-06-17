#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid, pid1;
    pid = fork();

    if(pid == 0)
    {
        pid1 = getpid();    // getpid()는 현재 실행 중인 process의 pid를 가져온다. 따라서 child process 본인의 pid값을 갖는다.
        printf("child: pid = %d\n", pid);   // 다음 child process가 없으므로 0
        printf("child: pid1 = %d\n", pid1); // child process pid
    }
    else if(pid > 0)
    {
        pid1 = getpid();
        printf("parent: pid = %d\n", pid);  // child process pid
        printf("parent: pid1 = %d\n", pid1); // parent process pid
        wait(NULL);
    }

    return 0;
}