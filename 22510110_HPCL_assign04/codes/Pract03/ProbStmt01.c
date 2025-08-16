#include <stdio.h>
#include <omp.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter vector size: ");
    scanf("%d", &n);

    int a[n], b[n];
    printf("Enter elements of vector A:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("Enter elements of vector B:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    // Sort vector A in ascending order
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++)
            if(a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

    // Sort vector B in descending order
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++)
            if(b[i] < b[j]) {
                int temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }

    int min_scalar_product = 0;

    // Parallel dot product using OpenMP reduction clause
    double t1 = omp_get_wtime();
    #pragma omp parallel for reduction(+:min_scalar_product) schedule(static)
    for(int i = 0; i < n; i++) {
        min_scalar_product += a[i] * b[i];
    }
    double t2 = omp_get_wtime();

    printf("Minimum Scalar Product: %d\n", min_scalar_product);
    printf("Parallel Time: %lf seconds\n", t2 - t1);

    return 0;
}