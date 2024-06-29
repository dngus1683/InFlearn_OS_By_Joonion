#include <stdio.h>
#include <pthread.h>

int sum = 0;

void* run1(void* param)
{
    int i =0;
    for(i=0; i<50000; i++)
    {
        sum ++;
    }
    pthread_exit(0);
}

void* run2(void* param)
{
    int i =0;
    for(i=0; i<50000; i++)
    {
        sum --;
    }
    pthread_exit(0);
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, run1, NULL);
    pthread_create(&tid2, NULL, run2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("%d\n", sum);
}

// 예상으로는 sum값이 0이 나와야 한다.
// 결과) 0이 출력되지만 간혹 다른 값이 출력된다.
// for문의 반복수가 증가하면 예상 외 값이 나오는 빈도가 증가한다.