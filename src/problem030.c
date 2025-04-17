// Digit Fifth Powers

#include <stdio.h>

int main(void)
{
    long power5[10];
    for (int i = 0; i < 10; i++) {
        long p = i;
        power5[i] = p * p * p * p * p;
    }

    long total = 0L;

    // Let x an n-digit integer which can be written as the sum of fifth powers of its digits
    // Then 10^(n-1) <= x <= n * 9^5 = 59049n
    // Only n = 1, 2, 3, 4, 5, 6 hold this condition
    for (long i = 2L; i < 1000000L /* 10^6 */; i++) {
        long p = i;
        long sum = 0L;
        while (p > 0L) {
            sum += power5[p % 10L];
            p /= 10L;
        }
        if (sum == i) {
            total += i;
        }
    }

    printf("%ld\n", total);

    return 0;
}
