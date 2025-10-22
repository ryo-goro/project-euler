// Permuted Multiples
// 142857

#include <stdio.h>

#define N 6

void count_digits(int *counts, long x)
{
    for (int i = 0; i < 10; i++) {
        counts[i] = 0;
    }

    while (x > 0L) {
        counts[x % 10]++;
        x /= 10;
    }
}

int compare_arr(const int *arr1, const int *arr2, int n)
{
    for (int i = 0; i < n; i++) {
        if (arr1[i] > arr2[i]) {
            return 1;
        }
        if (arr1[i] < arr2[i]) {
            return -1;
        }
    }

    return 0;
}

// Returns a^n
long power(long a, int n)
{
    long res = 1;

    for (int i = 0; i < n; i++) {
        res *= a;
    }

    return res;
}

int main(void)
{
    int x_counts[10];
    int nx_counts[10];

    for (int num_of_digits = 1; ; num_of_digits++) {
        // For all nx (n = 1, 2, ..., N) to be `num_of_digits`-digit,
        // Both x >= 10^{num_of_digits - 1} and Nx < 10^{num_of_digit} should hold

        long min = power(10, num_of_digits - 1);
        long max = min * 10 / N;

        for (long x = min; x <= max; x++) {
            count_digits(x_counts, x);

            int n;

            for (n = 2; n <= N; n++) {
                count_digits(nx_counts, n * x);

                if (compare_arr(x_counts, nx_counts, 10) != 0) {
                    break;
                }
            }

            if (n > N) {
                printf("%ld\n", x);
                return 0;
            }
        }
    }
    
    return 1;   // Will not reach here
}
