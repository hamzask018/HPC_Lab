#include <stdio.h>
#include <omp.h>

int main(void)
{
    int n_threads;
    printf("Enter number of threads: ");
    scanf("%d", &n_threads);

    // Sequential printing
    printf("\nSequential Output:\n");
    for(int i = 0; i < n_threads; i++) {
        printf("Hello, World\n");
    }

    // Parallel printing
    printf("\nParallel Output:\n");
    omp_set_num_threads(n_threads);
    #pragma omp parallel
    {
        printf("Hello, World from thread %d\n", omp_get_thread_num());
    }

    return 0;
}