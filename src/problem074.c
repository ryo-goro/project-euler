// Digit Factorial Chains
// Solved. Needs refactoring a bit

#include <stdio.h>

#define LIMIT 1000000LU     // 1 million
#define MAX_CHAIN_LENGTH 60U

// 0! ~ 9!
unsigned long factorials[10] = {
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880,
};

unsigned long sum_of_digit_factorials(unsigned long n)
{
    unsigned long sum = 0;

    do {
        sum += factorials[n % 10];
        n /= 10;
    } while (n);

    return sum;
}

int main(void)
{
    unsigned length[LIMIT] = {0};

    // 169 -> 363601 -> 1454 (-> 169)
    length[169LU] = length[363601LU] = length[1454LU] = 3;
    // 871 -> 45361 (-> 871)
    length[871LU] = length[45361LU] = 2;
    // 872 -> 45362 (-> 872)
    length[872LU] = length[45362LU] = 2;

    unsigned long count = 0;

    unsigned long chain[MAX_CHAIN_LENGTH];

    for (unsigned long n = 1; n < LIMIT; n++) {
        if (length[n]) {
            continue;
        }

        unsigned long term = chain[0] = n;
        unsigned long next_term;
        unsigned chain_len = 1;
        unsigned trailing_len;

        while (1) {
            next_term = sum_of_digit_factorials(term);

            if (next_term == term) {
                trailing_len = 1;
                break;
            }

            chain[chain_len++] = term = next_term;

            if (term >= LIMIT) {
                continue;
            }

            if (length[term]) {
                trailing_len = length[term];
                break;
            }
        }

        unsigned base_len = chain_len + trailing_len - 1;

        if (base_len == MAX_CHAIN_LENGTH) {
            count++;
        }

        for (unsigned i = 0; i < chain_len; i++) {
            if (chain[i] < LIMIT) {
                length[chain[i]] = base_len - i;
            }
        }
    }

    printf("%lu\n", count);

    return 0;
}
