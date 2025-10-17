// Distinct Primes Factors
// 134043

#include <stdio.h>

#define NUM_OF_PRIME_FACTORS 4
#define COUNT 4

int num_of_prime_factors(long n)
{
    int count = 0;

    if (n % 2 == 0L) {
        count++;

        do {
            n /= 2;
        } while (n % 2 == 0L);
    }

    for (long d = 3; d * d <= n; d += 2) {
        if (n % d == 0L) {
            count++;

            do {
                n /= d;
            } while (n % d == 0L);
        }
    }

    if (n > 1L) {
        count++;
    }

    return count;
}

int main(void)
{
    long n = 1;
    int count = 0;

    for (;; n++) {
        if (num_of_prime_factors(n) == NUM_OF_PRIME_FACTORS) {
            count++;

            if (count == COUNT) {
                break;
            }
        } else {
            count = 0;
        }
    }

    printf("%ld\n", n - COUNT + 1);

    return 0;
}
