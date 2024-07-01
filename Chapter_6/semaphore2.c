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
    sem_init(&sem, 0, 5);
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

// 이 코드는 semaphore의 장점을 살리고자 S의 값을 2개 이상으로 설정하였다.
// 예상 결과로는 sum = 5000000이 출력되어야 하지만, 다른 값들을 출력한다.
// 그 이유는, semaphore에서 critical section에 진입을 허용한 숫자는 5이며 총 스레드의 개수도 5다.
// 때문에 모든 스레드가 동시에 critical section에 진입하게 된다. 
// 이때, 모든 스레드가 critical section에서 접근하는 변수(객체)는 동일한 대상이기 때문에,
// 동기화를 하지 않은 것과 마찬가지의 상황이 발생한다. (== race condition 문제가 해결이 안됨)