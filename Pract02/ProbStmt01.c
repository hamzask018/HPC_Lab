#include <stdio.h>
#include <omp.h>

int main() {
    int n, scalar;
    printf("Enter vector size: ");
    scanf("%d", &n);
    printf("Enter scalar value: ");
    scanf("%d", &scalar);

    int a[n], result[n];

    // Initialize vector
    for(int i = 0; i < n; i++)
        a[i] = i;

    // Sequential addition
    double t1 = omp_get_wtime();
    for(int i = 0; i < n; i++)
        result[i] = a[i] + scalar;
    double t2 = omp_get_wtime();
    printf("Sequential Time: %lf seconds\n", t2 - t1);

    printf("Sequential Addition Result:\n");
    for(int i = 0; i < n; i++)
        printf("%d + %d = %d\n", a[i], scalar, result[i]);

    // Parallel addition
    double t3 = omp_get_wtime();
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
        result[i] = a[i] + scalar;
    double t4 = omp_get_wtime();
    printf("Parallel Time: %lf seconds\n", t4 - t3);

    printf("Parallel Addition Result:\n");
    for(int i = 0; i < n; i++)
        printf("%d + %d = %d\n", a[i], scalar, result[i]);
        
    return 0;
}