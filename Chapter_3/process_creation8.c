#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#define SIZE 5

int nums[SIZE] = {0, 1, 2, 3, 4};

int main()
{
    pid_t pid;
    pid = fork();


    // fork()로 주소공간을 전부 복사하면, 해당 process의 형태만 같을 뿐, 주소는 모두 다른 값을 가지므로, parent process의 전역변수와 child process의 전역변수는 같은 대상이 아니다.
    // 따라서 child 에서 값을 바꿔도 parent에는 변화가 없다.
    if(pid == 0)
    {
        for(int i=0; i<SIZE; i++)
        {
            nums[i] *= i;
            printf("CHILD: %d \n", nums[i]);
        }
    }
    else if(pid > 0)
    {
        wait(NULL);
        for(int i=0; i<SIZE; i++)
        {
            printf("PARENT: %d \n", nums[i]);
        }
    }

    return 0;
}