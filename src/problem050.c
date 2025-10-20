// Consecutive Prime Sum
// 997651
// 7 + ... + 3931 = 997651 (sum of 543 consecutive primes)

#include <stdio.h>
#include <stdlib.h>

#define LIMIT 1000000L  // 1 million

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
    char prime[LIMIT];
    make_sieve(prime, LIMIT);

    // Count prime numbers below LIMIT
    long num_of_primes = 1; // 2 is the only even prime number
    for (long p = 3; p < LIMIT; p += 2) {
        if (prime[p]) {
            num_of_primes++;
        }
    }

    // prime_nums[0] = 0, prime_nums[i] = the i-th prime number (i > 0)
    long *prime_nums = calloc(num_of_primes + 1, sizeof(long));

    // Pack prime numbers below LIMIT into an array
    prime_nums[1] = 2;
    for (long p = 3, i = 2; p < LIMIT; p += 2) {
        if (prime[p]) {
            prime_nums[i++] = p;
        }
    }

    long res = 2;   // 2 is prime, and can be written as the sum of 1 consecutive prime number
    long least_sum = 0;

    for (long first = 1, last = 1; last <= num_of_primes; first++, last++) {
        least_sum += prime_nums[last] - prime_nums[first - 1];  // least_sum = primes[first] + primes[first + 1] + ... + primes[last]

        if (least_sum >= LIMIT) {
            break;
        }

        long trial_sum = least_sum;

        for (long i = last + 1; i <= num_of_primes; i++) {
            trial_sum += prime_nums[i];

            if (trial_sum >= LIMIT) {
                break;
            }

            if (prime[trial_sum]) {
                res = least_sum = trial_sum;
                last = i;
            }
        }
    }

    printf("%ld\n", res);

    free(prime_nums);

    return 0;
}
