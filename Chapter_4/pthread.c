#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// the data shared by the threads
int sum;
// thread call this function
void* runner(void* param);

int main(int argc, char* argv[])
{
    pthread_t tid; // thread identifier
    pthread_attr_t attr; // thread attributes

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
}

void* runner(void* param)
{
    // param == argv[1]
    int i, upper = atoi(param);
    sum = 0;
    for(int i=1; i<=upper; i++)
    {
        sum += i;
    }

    pthread_exit(0);
}