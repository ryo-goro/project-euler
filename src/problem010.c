// Summation of Primes

#include <stdio.h>

#define LIMIT 2000000L // 2 million

void make_sieve(char *sieve, long sieve_len)
{
    if (sieve_len <= 0L) {
        return;
    }

    sieve[0] = 0;

    if (sieve_len == 1L) {
        return;
    }

    sieve[1] = 0;

    for (long i = 2L; i < sieve_len; i++) {
        sieve[i] = 1;
    }
    
    for (long i = 4L; i < sieve_len; i += 2L) {
        sieve[i] = 0;
    }

    for (long i = 3L; i * i < sieve_len; i += 2L) {
        if (sieve[i]) {
            for (long j = i * i; j < sieve_len; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main(void)
{
    char sieve[LIMIT];
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
