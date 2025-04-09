// Summation of Primes

#include <stdio.h>

#define LIMIT 2000000L // 2 million

void make_sieve(int *sieve, long n)
{
    if (n <= 0L) {
        return;
    }

    // n > 0
    // 0 is not a prime number
    sieve[0] = 0;

    if (n == 1L) {
        return;
    }

    // n > 1
    // 1 is not a prime number
    sieve[1] = 0;

    for (long i = 2L; i < n; i++) {
        sieve[i] = 1;
    }
    
    // All even numbers except 2 are not prime numbers
    for (long i = 4L; i < n; i += 2L) {
        sieve[i] = 0;
    }

    // Find odd prime numbers < n
    for (long i = 3L; i * i < n; i += 2L) {
        if (sieve[i]) { // i is a prime number
            // Mark 2 * i, 3 * i, ... as not prime
            // Note that 2 * i, 3 * i, ..., (i - 1) * i are already marked as not prime
            for (long j = i * i; j < n; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main(void)
{
    int sieve[LIMIT];
    make_sieve(sieve, LIMIT);

    long long res = 0LL;

    for (long i = 0L; i < LIMIT; i++) {
        if (sieve[i]) {
            res += i;
        }
    }

    printf("%lld\n", res);

    return 0;
}
