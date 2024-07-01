#include <stdio.h>
#include <pthread.h>

#define true 1
#define false 0

int sum = 0;
int turn;
int flag[2];

void* producer(void* param)
{
    for(int k = 0; k<1000000; k++)
    {
        // entry section
        flag[0] = true;
        turn = 1;
        while(flag[1] && turn == 1);

        // critical section
        sum++;

        //exit section
        flag[0] = false;

        // remainder section
    }
}

void* consumer(void* param)
{
    for(int k = 0; k<1000000; k++)
    {
        // entry section
        flag[1] = true;
        turn = 0;
        while(flag[0] && turn == 0);

        // critical section
        sum --;

        // exit section
        flag[1] = false;

        //remainder section
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


// peterson algorithm을 적용하지 않은 결과와 비교하면, 오답을 출력하는 빈도가 줄어들었다.
// 하지만 아직도 오답을 출력한다.
// => peterson algorithm은 제대로 적용될 것이라는 보장을 하지 못함.
// flag와 turn의 값을 바꾸고 비교하는 entry section 에서의 과정에서
// 기계어 load, store가 다수 일어나면서, 해당 부분에서 context switch로 인해 race condition에 해당하게 된다.
// 때문에 기대했던 결과를 얻지 못하였다.