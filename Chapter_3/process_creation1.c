#define _XOPEN_SOURCE 700
/*
pid_t는 POSIX 표존에 정의된 데이터 타입이다. 이는 POSIX.1-2001(issue 7) 이후부터 <unistd.h>에 정의되어있는데, 만약 pid_t가 unidentified 오류가 뜬다면, unistd.h 이전 헤더인
<sys/types.h>에 정의되어있는 것이다. 따라서 해당 오류를 해결하기 위해서는 <sys/types.h> 헤더를 선언하거나 POSIX.1-2001 정의를 활성화하기 위해, 위와 같은 매크로를 define 한다.
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    printf("Hello, Process!\n");    // parent process와 child process에 의해 두 번 출력된다.

    return 0;
}