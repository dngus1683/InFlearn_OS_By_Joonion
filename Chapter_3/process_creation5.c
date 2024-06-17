#define _XOPEN_SOURE 700
#include <stdio.h>
#include <unistd.h>

int main()
{
    // fork 네번 => 총 process 수 = 2^4
    for(int i=0; i<4; i++)
    {
        fork();
    }

    printf("hi\n");
    return 0;
}