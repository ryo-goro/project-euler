// 10 001st Prime

#include <stdio.h>

#define LIMIT 10000

int main(void)
{
    long prime_numbers[LIMIT + 1];
    prime_numbers[0] = 2;

    int num = 1;

    for (long p = 3; num <= LIMIT; p += 2) {
        int found = 1;

        for (int i = 0; i < num; i++) {
            long prime_number = prime_numbers[i];

            if (prime_number * prime_number > p) {
                break;
            }

            if (p % prime_number == 0) {
                found = 0;
                break;
            }
        }

        if (found) {
            prime_numbers[num++] = p;
        }
    }

    printf("%ld\n", prime_numbers[LIMIT]);

    return 0;
}
