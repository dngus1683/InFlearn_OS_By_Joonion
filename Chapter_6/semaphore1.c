#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int sum = 0;

sem_t sem; 

void* producer(void* param)
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

void* consumer(void* param)
{
    for(int k = 0; k<1000000; k++)
    {
        // entry section
        sem_wait(&sem);

        // critical section
        sum--;

        // exit section
        sem_post(&sem);
    }

    pthread_exit(0);
}

int main()
{
    pthread_t tid1, tid2;
    sem_init(&sem, 0, 1);
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("sum = %d\n", sum);
}

// mutex lock은 2개의 process || thread 에 대해서 관리를 해준다면 
// semaphore는 다수의 것들도 처리해준다.
// 이 코드에서는 S = 1로, binary semaphore이며 이는 mutex lock과 같다.