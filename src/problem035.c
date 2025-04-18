// Circular Primes

#include <stdio.h>

#define LIMIT 1000000L  // 1 million
#define DIGITS_LIMIT 6

int main(void)
{
    // Making a sieve of Eratosthenes
    int composite[LIMIT] = {0};
    composite[0] = composite[1] = 1;

    for (long i = 4; i < LIMIT; i += 2) {
        composite[i] = 1;
    }

    for (long i = 3; i * i < LIMIT; i += 2) {
        if (!composite[i]) {
            for (long j = i * i; j < LIMIT; j += i) {
                composite[j] = 1;
            }
        }
    }

    int res = 0;
    int checked[LIMIT] = {0};

    // Checking 1-digit numbers
    for (int i = 0; i < 10; i++) {
        checked[i] = 1;
        if (!composite[i]) {
            res++;
        }
    }

    long base = 1L;
    long targets[DIGITS_LIMIT];

    for (int num_of_digits = 2; num_of_digits <= DIGITS_LIMIT; num_of_digits++) {
        base *= 10L;

        for (long p = base; p < base * 10L; p++) {
            if (checked[p]) {
                continue;
            }
            checked[p] = 1;

            long target = p;
            targets[0] = target;

            int count = 1;

            for (int i = 1; i < num_of_digits; i++) {
                target = target % base * 10 + target / base;
                if (!checked[target]) {
                    count++;
                }
                checked[target] = 1;
                targets[i] = target;
            }

            int found = 1;
            for (int i = 0; i < num_of_digits; i++) {
                if (composite[targets[i]]) {
                    found = 0;
                    break;
                }
            }

            if (found) {
                res += count;
            }
        }
    }

    printf("%d\n", res);

    return 0;
}
