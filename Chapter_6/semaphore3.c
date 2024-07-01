#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sum = 0;

sem_t sem; 

void* count(void* param)
{
    for(int k = 0; k<1000000; k++)
    {
        // entry section
        sem_wait(&sem);

        // critical section
        sum++;

        // exit section
        sem_post(&sem);
    }

    pthread_exit(0);
}

int main()
{
    pthread_t tid[5];
    sem_init(&sem, 0, 1);
    for(int i=0; i<5; i++)
    {
        pthread_create(tid+i, NULL, count, NULL);
    }
    for(int i=0; i<5; i++)
    {
        pthread_join(tid[i], NULL);
    }
    printf("sum = %d\n", sum);
}

// semaphore2.c 코드에서, S를 1로 하면, 5개의 스레드가 한 번에 한 스레드 씩 공용 변수 sum에 접근한다.
// 이때, 나머지 4개의 스레드는 s의 linked list에서 wait() 중이고, signal()에 의해 순차적으로 sum에 접근하면서 동기화를 구성하게 된다.