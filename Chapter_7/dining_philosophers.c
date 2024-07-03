#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define true 1
#define NUM_PHILS 5

enum {THINGING, HUNGRY, EATING} state[NUM_PHILS];

pthread_mutex_t mutex_lock;
pthread_cond_t cond_vars[NUM_PHILS];

void init()
{
    for(int i=0; i<NUM_PHILS; i++)
    {
        state[i] = THINGING;
        pthread_cond_init(&cond_vars[i], NULL);
    }
    pthread_mutex_init(&mutex_lock, NULL);
    srand(time(0));
}
int leftOf(int i)
{
    return (i+NUM_PHILS - 1) % NUM_PHILS;
}
int rightOf(int i)
{
    return (i+1) % NUM_PHILS;
}
void think(int id)
{
    printf("%d: Now, I'm thinking...\n", id);
    usleep((1+rand()%50) * 10000);
}
void eating(int id)
{
    printf("%d: Now, I'm eating...\n", id);
    usleep((1+rand()%50) * 10000);
}
void test(int i)
{
    // If I'm hungry and my neighbors are not eating
    // then let me eat.
    if(state[i] == HUNGRY && state[leftOf(i)] != EATING && state[rightOf(i)] != EATING)
    {
        state[i] = EATING;
        pthread_cond_signal(&cond_vars[i]);
    }
}
void pickup(int i)
{
    pthread_mutex_lock(&mutex_lock);

    // critical section
    state[i] = HUNGRY;
    test(i);
    while(state[i] != EATING)
    {
        pthread_cond_wait(&cond_vars[i], &mutex_lock);
    }
    // ----------------

    pthread_mutex_unlock(&mutex_lock);
}
void putdown(int i)
{
    pthread_mutex_lock(&mutex_lock);

    state[i] = THINGING;
    test(leftOf(i));
    test(rightOf(i));

    pthread_mutex_unlock(&mutex_lock);
}
void* philosopher(void* param)
{
    int id = *((int* )param);
    while(true)
    {
        think(id);
        pickup(id);
        eating(id);
        putdown(id);
    }
}

int main()
{
    pthread_t tid;  
    init();
    for(int i=0; i<NUM_PHILS; i++)
    {
        pthread_create(&tid, NULL, philosopher, (void* )&i);
    }
    for(int i=0; i<NUM_PHILS; i++)
    {
        pthread_join(tid, NULL);
    }
    return 0;
}