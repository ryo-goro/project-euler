// Consecutive Prime Sum

#include <stdio.h>
#include <stdlib.h>

#define LIMIT 1000000L  // 1 million

void make_sieve(int *sieve, long n)
{
    sieve[0] = sieve[1] = 0;

    for (long i = 2; i < n; i++) {
        sieve[i] = 1;
    }

    for (long i = 4; i < n; i += 2) {
        sieve[i] = 0;
    }

    for (long i = 3; i * i < n; i += 2) {
        if (sieve[i]) {
            for (long j = i * i; j < n; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

int main(void)
{
    int prime_sieve[LIMIT];
    make_sieve(prime_sieve, LIMIT);

    long num_of_primes = 1;
    for (long p = 3; p < LIMIT; p += 2) {
        if (prime_sieve[p]) {
            num_of_primes++;
        }
    }

    long *primes = calloc(num_of_primes + 1, sizeof(long));
    primes[1] = 2;
    for (long p = 3, i = 2; p < LIMIT; p += 2) {
        if (prime_sieve[p]) {
            primes[i++] = p;
        }
    }

    long res = 0;    
    long base_sum = 0;

    for (long from = 1, to = 1; to <= num_of_primes; from++, to++) {
        base_sum += primes[to] - primes[from - 1];  // base_sum = primes[from] + primes[from + 1] + ... + primes[to]
        if (base_sum >= LIMIT) {
            break;
        }
        if (prime_sieve[base_sum]) {
            res = base_sum;
        }

        long sum = base_sum;

        for (long i = to + 1; i <= num_of_primes; i++) {
            sum += primes[i];
            if (sum >= LIMIT) {
                break;
            }
            if (prime_sieve[sum]) {
                res = base_sum = sum;
                to = i;
            }
        }
    }

    printf("%ld\n", res);   // 7 + ... + 3931 = 997651 (sum of 543 consecutive primes)

    free(primes);

    return 0;
}
