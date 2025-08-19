#include <iostream>
#include <omp.h>
using namespace std;
int main() {
    long long n, scalar;
    cout << "Enter vector size: ";
    cin >> n;
    cout << "Enter scalar value: ";
    cin >> scalar;

    long long *a = new long long[n];
    long long *result = new long long[n];

    // Initialize vector
    for(long long i = 0; i < n; i++)
        a[i] = i;

    // Sequential addition
    double t1 = omp_get_wtime();
    for(long long i = 0; i < n; i++)
        result[i] = a[i] + scalar;
    double t2 = omp_get_wtime();
    cout << "Sequential Time: " << (t2 - t1) << " seconds\n";

    // cout << "Sequential Addition Result:\n";
    // for(long long i = 0; i < n; i++)
    //     // cout << result[i] << " ";
    // // cout << endl;

    // Parallel addition
    double t3 = omp_get_wtime();
    #pragma omp parallel for
    for(long long i = 0; i < n; i++)
        result[i] = a[i] + scalar;
    double t4 = omp_get_wtime();
    cout << "Parallel Time: " << (t4 - t3) << " seconds\n";

    // cout << "Parallel Addition Result:\n";
    // for(long long i = 0; i < n; i++)
    //     // cout << result[i] << " ";
    // // cout << endl;

    delete[] a;
    delete[] result;

    return 0;
}