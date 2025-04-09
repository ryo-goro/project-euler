// Smallest Multiple

#include <stdio.h>

#define LIMIT 20

void make_sieve(int *sieve, int n)
{
    if (n <= 0) {
        return;
    }

    // n > 0
    // 0 is not a prime number
    sieve[0] = 0;

    if (n == 1) {
        return;
    }

    // n > 1
    // 1 is not a prime number
    sieve[1] = 0;

    for (int i = 2; i < n; i++) {
        sieve[i] = 1;
    }
    
    // All even numbers except 2 are not prime numbers
    for (int i = 4; i < n; i += 2) {
        sieve[i] = 0;
    }

    // Find odd prime numbers < n
    for (int i = 3; i * i < n; i += 2) {
        if (sieve[i]) { // i is a prime number

            // Mark 2 * i, 3 * i, ... as not prime
            // Note that 2 * i, 3 * i, ..., (i - 1) * i are already marked as not prime
            for (int j = i * i; j < n; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main(void)
{
    int sieve[LIMIT + 1];
    make_sieve(sieve, LIMIT + 1);

    long long res = 1LL;
    
    for (int p = 2; p <= LIMIT; p++) {
        if (sieve[p]) {
            int power = p;
            while (power * p <= LIMIT) {
                power *= p;
            }
            res *= power;
        }
    }

    printf("%lld\n", res);

    return 0;
}
