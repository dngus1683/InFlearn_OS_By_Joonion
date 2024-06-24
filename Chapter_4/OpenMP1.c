#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    #pragma omp parallel // compiler directive
    {
        printf("I am a paraller region.\n");
    }
    return 0;
}

// 컴파일 시, -fopenmp 옵션 추가

// 실행하면 print가 병렬로 실행되므로 여려 개 출력됨.
