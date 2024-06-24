#include <stdio.h>
#include <omp.h>

#define SIZE 100000000

int a[SIZE], b[SIZE], c[SIZE];

int main(int argc, char* argv[])
{
    int i;
    for(i=0; i<SIZE; i++)
    {
        a[i] = b[i] = i;
    }

    #pragma omp parallel for
    for(int i=0; i<SIZE; i++)
    {
        c[i] = a[i] + b[i];
    }
    return 0;
}

// 강의 기준. 실행 시간      
/*
 real: 0.442s
 user: 1.163s   // 병렬처리 시 대기 시간 등 때매 오래 걸림
 sys: 0.418s    // kernel thread가 병렬처리로 계산을 다 했기 때문에 real == sys 다.

 // 스레드를 사용하지 않았을 때 for문 계산 걸린 시간.
 real: 0.636s   // user + sys
 user: 0.378s
 sys: 0.259s
*/