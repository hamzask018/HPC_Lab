#include <stdio.h>
#include <omp.h>

#define SIZE 200

void vector_scalar_add_static(int *a, int *result, int scalar, int chunk, int num_threads) {
    omp_set_num_threads(num_threads);
    double start = omp_get_wtime();
    #pragma omp parallel for schedule(static,chunk)
    for(int i = 0; i < SIZE; i++)
        result[i] = a[i] + scalar;
    double end = omp_get_wtime();
    printf("STATIC schedule, chunk %d, threads %d, time: %lf seconds\n", chunk, num_threads, end-start);
}

void vector_scalar_add_dynamic(int *a, int *result, int scalar, int chunk, int num_threads) {
    omp_set_num_threads(num_threads);
    double start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic,chunk)
    for(int i = 0; i < SIZE; i++)
        result[i] = a[i] + scalar;
    double end = omp_get_wtime();
    printf("DYNAMIC schedule, chunk %d, threads %d, time: %lf seconds\n", chunk, num_threads, end-start);
}

void nowait_demo(int *a, int *result, int scalar) {
    #pragma omp parallel
    {
        #pragma omp for schedule(static,10) nowait
        for(int i = 0; i < SIZE/2; i++)
            result[i] = a[i] + scalar;

        // Other work can be done here without waiting for the above loop to finish
        #pragma omp for schedule(static,10)
        for(int i = SIZE/2; i < SIZE; i++)
            result[i] = a[i] + scalar;
    }
    printf("nowait clause demo completed.\n");
}

int main() {
    int a[SIZE], result[SIZE];
    int scalar = 5;
    for(int i = 0; i < SIZE; i++)
        a[i] = i;

    int chunks[] = {1, 5, 10, 20, 50, 100};
    int threads[] = {2, 4, 8};

    // STATIC schedule analysis
    for(int t = 0; t < 3; t++)
        for(int c = 0; c < 6; c++)
            vector_scalar_add_static(a, result, scalar, chunks[c], threads[t]);

    // DYNAMIC schedule analysis
    for(int t = 0; t < 3; t++)
        for(int c = 0; c < 6; c++)
            vector_scalar_add_dynamic(a, result, scalar, chunks[c], threads[t]);

    // nowait clause demonstration
    nowait_demo(a, result, scalar);

    return 0;
}