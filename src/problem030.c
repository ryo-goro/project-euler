// Digit Fifth Powers
// 443839

#include <stdio.h>

int main(void)
{
    long power5[10];
    for (int i = 0; i < 10; i++) {
        long p = i;
        power5[i] = p * p * p * p * p;
    }

    long total = 0;

    // Let x an n-digit integer which can be written as the sum of fifth powers of its digits
    // Then 10^(n-1) <= x <= n * 9^5 = 59049n
    // Only n = 1, 2, 3, 4, 5 and 6 hold this condition
    for (long target = 2; target < 1000000L /* 10^6 */; target++) {
        long p = target;
        long sum = 0;

        while (p > 0L) {
            sum += power5[p % 10];
            p /= 10;
        }

        if (sum == target) {
            total += target;
        }
    }

    printf("%ld\n", total);

    return 0;
}
