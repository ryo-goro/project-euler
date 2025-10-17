// Goldbach's Other Conjecture
// 5777

#include <stdio.h>

int is_prime(long target)
{
    if (target < 2L) {
        return 0;
    }

    if (target == 2L) {
        return 1;
    }

    if (target % 2 == 0L) {
        return 0;
    }

    for (long d = 3; d * d <= target; d += 2) {
        if (target % d == 0L) {
            return 0;
        }
    }

    return 1;
}

// Returns 1 if odd_composite can be written as the sum of a prime and twice a square
// Returns 0 otherwise
// odd_composite should be a positive odd composite number
int is_goldbach_composite(long odd_composite)
{
    for (long i = 1; ; i++) {
        long square2 = 2 * i * i;

        if (square2 >= odd_composite) {
            return 0;
        }

        if (is_prime(odd_composite - square2)) {
            return 1;
        }
    }
}

int main(void)
{
    long n = 9; // The first composite odd number

    for (;; n += 2) {
        if (is_prime(n)) {
            continue;
        }

        if (!is_goldbach_composite(n)) {
            break;
        }
    }

    printf("%ld\n", n);

    return 0;
}
