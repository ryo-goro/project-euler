// Smallest Multiple
// 232792560

#include <stdio.h>

#define LIMIT 20

void make_sieve(char *sieve, int sieve_len)
{
    if (sieve_len <= 0) {
        return;
    }

    // sieve_len > 0
    // 0 is not a prime number
    sieve[0] = 0;

    if (sieve_len == 1) {
        return;
    }

    // sieve_len > 1
    // 1 is not a prime number
    sieve[1] = 0;

    for (int i = 2; i < sieve_len; i++) {
        sieve[i] = 1;
    }
    
    // All even numbers except 2 are not prime numbers
    for (int i = 4; i < sieve_len; i += 2) {
        sieve[i] = 0;
    }

    // Find odd prime numbers < sieve_len
    for (int i = 3; i * i < sieve_len; i += 2) {
        // If i is a prime number, mark 2 * i, 3 * i, ... as not prime
        // Note that 2 * i, 3 * i, ..., (i - 1) * i are already marked as not prime
        if (sieve[i]) {
            for (int j = i * i; j < sieve_len; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main(void)
{
    char sieve[LIMIT + 1];
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
