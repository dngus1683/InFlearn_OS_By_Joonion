#include <stdio.h>
#include <pthread.h>

int sum = 0;

pthread_mutex_t mutex;

void* producer(void* param)
{
    for(int i=0; i<1000000; i++)
    {
        // entry section
        pthread_mutex_lock(&mutex);

        // critical section
        sum++;

        // exit section
        pthread_mutex_unlock(&mutex);
        pthread_exit(0);   
    }
}

void* consumer(void* param)
{
    for(int i=0; i<1000000; i++)
    {
        // entry section
        pthread_mutex_lock(&mutex);

        // critical section
        sum--;

        // exit section
        pthread_mutex_unlock(&mutex);
        pthread_exit(0);
    }
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("sum = %d\n", sum);
}




// 해당 코드의 결과로, for문의 반복 수를 늘려도 sum = 0이 출력된다. 
// peterson algorithm에서 entry, exit section 구현을 mutex lock으로 구현했는데,
// mutex lock은 hardware 구성을 통해 해당 부분을 하나의 instruction으로 구현하여
// 해당 구간에서는 중간에 context switch가 일어나지 않는다.
// 이로 인해 동기화가 이뤄지게 된다.