#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>

int value = 0;
void* runner(void* param);

int main(int argc, char* argv[])
{
    pid_t pid;
    pthread_t tid;
    pthread_attr_t attr;
    pid = fork();

    if(pid == 0) // child process
    {
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid, NULL);
        printf("CHILD: value = %d\n", value);   // 한 process 내에서 thread끼리는 데이터를 공유하기 때문에, 위에서 생산된 thread를 통해 value 값이 변형된 것은 메인 thread에도 적용된다.
    }
    else if(pid > 0) // parent process
    {
        wait(NULL);
        printf("PARENT: value = %d\n", value);  // 자식 process에서의 value 값 변형은 부모 process에는 영향이 없으므로 value 값이 변하지 않는다.
    }
}

void* runner(void* param)
{
    value = 5;
    pthread_exit(0);
}