#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_add(int **A, int **B, int **C, int n, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};

    for(int s = 0; s < 5; s++) {
        int n = sizes[s];
        printf("\nMatrix size: %d x %d\n", n, n);

        // Allocate matrices
        int **A = (int **)malloc(n * sizeof(int *));
        int **B = (int **)malloc(n * sizeof(int *));
        int **C = (int **)malloc(n * sizeof(int *));
        for(int i = 0; i < n; i++) {
            A[i] = (int *)malloc(n * sizeof(int));
            B[i] = (int *)malloc(n * sizeof(int));
            C[i] = (int *)malloc(n * sizeof(int));
        }

        // Initialize matrices
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }

        for(int t = 0; t < 4; t++) {
            int num_threads = threads[t];
            double start = omp_get_wtime();
            matrix_add(A, B, C, n, num_threads);
            double end = omp_get_wtime();
            printf("Threads: %d, Time: %lf seconds\n", num_threads, end - start);
        }

        // Free memory
        for(int i = 0; i < n; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A); free(B); free(C);
    }
    return 0;
}