#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        execlp("/bin/ls", "ls", NULL);  // /bin/ls 경로에 있는 ls 프로그램을 해당 process에 덮어 씌운다. 기존의 프로그램은 실행하지 않는다.
        printf("LINE J\n");     // execlp()을 통해 child process의 프로그램은 ls로 덮어씌워져서, ls 프로그램이 실행되고 곧바로 종료되므로 "LINE J"를 출력하지 않는다.
    }
    else if(pid > 0)
    {
        wait(NULL);
        printf("Child Complete\n");
    }
    return 0;
}