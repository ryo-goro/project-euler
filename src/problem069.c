// Totient Maximum

#include <stdio.h>
#include <stdlib.h>

#define N 1000000L
#define SIEVE_SIZE (N + 1)

char sieve[SIEVE_SIZE]; // The sieve of Eratosthenes

void init_sieve(void)
{
    sieve[0] = sieve[1] = 0;
    sieve[2] = 1;

    for (long i = 3; i < SIEVE_SIZE; i += 2) {
        sieve[i] = 1;
    }

    for (long i = 4; i < SIEVE_SIZE; i += 2) {
        sieve[i] = 0;
    }

    for (long i = 3; i * i < SIEVE_SIZE; i += 2) {
        if (sieve[i]) {
            for (long j = i * i; j < SIEVE_SIZE; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

long count_primes(void)
{
    long count = 1; // 2 is prime

    // All primes other than 2 are odd
    for (long i = 3; i < SIEVE_SIZE; i += 2) {
        if (sieve[i]) {
            count++;
        }
    }

    return count;
}

void fill_primes(long *primes)
{
    primes[0] = 2;  // 2 is the first prime number

    long idx = 1;

    // All primes other than 2 are odd
    for (long i = 3; i < SIEVE_SIZE; i += 2) {
        if (sieve[i]) {
            primes[idx++] = i;
        }
    }
}

long totient(long n, const long *primes, long prime_count)
{
    if (sieve[n]) {
        return n - 1;
    }

    long res = 1;

    for (long i = 0; n > 1L; i++) {
        long prime = primes[i];

        if (n % prime == 0L) {
            int count = 0;

            do {
                n /= prime;
                count++;
            } while (n % prime == 0L);

            long power = 1;

            for (int i = 1; i < count; i++) {
                power *= prime;
            }

            res *= power * (prime - 1);
        }
    }

    return res;
}

int main(void)
{
    init_sieve();

    long prime_count = count_primes();

    long *primes = calloc(prime_count, sizeof(long));
    if (primes == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    fill_primes(primes);

    long res_n = 2;
    long res_phi = 1;

    for (long n = 3; n <= N; n++) {
        long phi = totient(n, primes, prime_count);

        // n / phi > res_n / res_phi
        if ((long long)n * res_phi > (long long)res_n * phi) {
            res_n = n;
            res_phi = phi;
        }
    }

    printf("%ld\n", res_n);

    free(primes);

    return 0;
}
