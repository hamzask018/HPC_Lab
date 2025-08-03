#include <stdio.h>
#include <omp.h>

int main() {
    long num_steps;
    double step, pi = 0.0;
    printf("Enter number of steps: ");
    scanf("%ld", &num_steps);

    step = 1.0 / (double) num_steps;

    // Sequential calculation
    double t1 = omp_get_wtime();
    for(long i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= step;
    double t2 = omp_get_wtime();
    printf("Sequential Pi: %.15f, Time: %lf seconds\n", pi, t2 - t1);

    // Parallel calculation
    pi = 0.0;
    double t3 = omp_get_wtime();
    #pragma omp parallel for reduction(+:pi)
    for(long i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= step;
    double t4 = omp_get_wtime();
    printf("Parallel Pi: %.15f, Time: %lf seconds\n", pi, t4 - t3);

    return 0;
}