// 10 001st Prime
// 104743

#include <stdio.h>

#define LIMIT 10000

int main(void)
{
    long primes[LIMIT + 1];
    primes[0] = 2;

    int num_of_primes = 1;

    for (long prime_candidate = 3; num_of_primes <= LIMIT; prime_candidate += 2) {
        int found = 1;

        for (int i = 0; i < num_of_primes; i++) {
            long prime_number = primes[i];

            if (prime_number * prime_number > prime_candidate) {
                break;
            }

            if (prime_candidate % prime_number == 0) {
                found = 0;
                break;
            }
        }

        if (found) {
            primes[num_of_primes++] = prime_candidate;
        }
    }

    printf("%ld\n", primes[LIMIT]);

    return 0;
}
