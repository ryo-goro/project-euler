// Permuted Multiples

#include <stdio.h>

#define MAX_NUM_OF_DIGITS 7

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

int equal(const int *a, const int *b, int n)
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int x_counts[10];
    int nx_counts[10];

    long power10 = 1;

    for (int num_of_digits = 1; num_of_digits <= MAX_NUM_OF_DIGITS; num_of_digits++) {
        for (long x = power10, end = power10 * 10 / 6; x <= end; x++) {
            count_digits(x_counts, x);

            int n;
            for (n = 2; n <= 6; n++) {
                count_digits(nx_counts, n * x);
                if (!equal(x_counts, nx_counts, 10)) {
                    break;
                }
            }

            if (n > 6) {
                printf("%ld\n", x);
                return 0;
            }
        }
        power10 *= 10;
    }
    
    return 1;
}
