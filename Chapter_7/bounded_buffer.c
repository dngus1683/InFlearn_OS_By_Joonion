#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define true 1
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty, full;

int in = 0;
int out = 0;

void insert_item(int item)
{
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    printf("Producer: insert $%d\n", item);

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void remove_item(int *item)
{
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    printf("Consumer: removed $%d\n", *item);


    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

void* producer(void* param)
{
    int item;
    while(true)
    {
        usleep((1+rand() % 5) * 100000);
        item = 1000 + rand() % 1000;
        insert_item(item); // critical section
    }
}

void* consumer(void* param)
{
    int item;
    while(true)
    {
        usleep((1+rand() % 5) * 100000);
        remove_item(&item); // critical section
    }
}

int main(int argc, char* argv[])
{
    int numOfProducer = 5, numOfConsumer = 5;
    pthread_t tid;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    srand(time(0));

    // create the producers
    for(int i=0; i < numOfProducer; i++)
    {
        pthread_create(&tid, NULL, producer, NULL);
    }
    // create the consumer
    for(int i=0; i < numOfConsumer; i++)
    {
        pthread_create(&tid, NULL, consumer, NULL);
    }

    sleep(5); // 5초 뒤, 메인 스레드는 return에 의해 실행 종료. => 메인 스레드가 종료되면 producer, consumer 역시 종료.
    return 0;
}



// 위 코드에서, buffer의 크기와 producer, consumer의 크기를 바꿔 실행해도,
// 실행 결과, 동기화 문제는 발생하지 않는다. 
// semaphore의 empty, full과 하나의 mutex를 통해 producer-consumer 문제를 해결한다.