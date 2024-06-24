#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    omp_set_num_threads(4);     // thread 생성 개수 지정.

    #pragma omp parallel // compiler directive
    {
        printf("OpenMP thread: %d\n", omp_get_thread_num());
    }
    return 0;
}

// 컴파일 시, -fopenmp 옵션 추가

// 실행하면 스레드 실행 순서는 정해져 있지 않기 때문에 실행할 때마다 출력 순서가 다르다.