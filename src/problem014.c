// Longest Collatz Sequence

#include <stdio.h>

#define LIMIT 1000000L  // 1 million
#define SEQUENCE_LEN 1000

int main(void)
{
    int lens[LIMIT] = {0};

    long res = 1L;
    int max_len = 0;

    for (; res < LIMIT; res *= 2L) {
        lens[res] = ++max_len;
    }

    res /= 2L;

    long long sequence[SEQUENCE_LEN];

    for (long n = 2L; n < LIMIT; n++) {
        if (lens[n] > 0) {
            continue;
        }

        int idx = 0;
        long long collatz = (long long)n;

        do {
            sequence[idx++] = collatz;

            if (collatz % 2LL == 0LL) {
                collatz /= 2LL;
            } else {
                collatz = collatz * 3LL + 1LL;
            }

        } while (collatz >= LIMIT || lens[collatz] == 0);

        int len = lens[collatz];
        while (idx > 0) {
            len++;
            idx--;
            if (sequence[idx] < LIMIT) {
                lens[sequence[idx]] = len;
            }
        }

        if (len > max_len) {
            res = n;
            max_len = len;
        }
    }

    printf("%ld\n", res);

    return 0;
}
