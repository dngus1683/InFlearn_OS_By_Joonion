#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>

/*
    How many processes are created?
*/

int value = 5;
int main()
{
    // 한 번의 fork()는 parent, child 두 개의 process로 구분된다. 또한, child process는 본인이 fork()된 line 다음부터 실행되므로, 
    // 총 만들어지는 process의 개수는 fork()의 개수만큼 2의 제곱한 값이다.
    // 따라서, 아래의 경우 2^3 = 8이다.
    // value 출력의 경우, 시분할을 통해, fork()로 만들어지는 child process들과 각 parent process들이 순서대로 번갈아가며 실행된다.
    printf("hi %d\n",value);
    fork();
    value += 5;
    printf("hi %d\n",value);
    fork();
    value += 5;
    printf("hi %d\n",value);
    fork();
    value += 5;
    printf("hi %d\n",value);
    return 0;
}