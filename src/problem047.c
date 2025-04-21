// Distinct Primes Factors

#include <stdio.h>

#define NUM_OF_PRIME_FACTORS 4
#define COUNT 4

int num_of_prime_factors(long n)
{
    int count = 0;

    if (n % 2L == 0L) {
        count++;
        do {
            n /= 2L;
        } while (n % 2L == 0L);
    }

    for (long d = 3L; d * d <= n; d += 2L) {
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
    long n;
    int count = 0;

    for (n = 1L; ; n++) {
        if (num_of_prime_factors(n) == NUM_OF_PRIME_FACTORS) {
            if (++count == COUNT) {
                break;
            }
        } else {
            count = 0;
        }
    }

    printf("%ld\n", n - COUNT + 1);

    return 0;
}
