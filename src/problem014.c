// Longest Collatz Sequence
// 837799

#include <stdio.h>

#define LIMIT 1000000L  // 1 million
#define CACHE_LEN LIMIT
#define BUF_LEN 1000

int collatz_length(long long n)
{
    static int cache[CACHE_LEN] = {0, 1};

    long long buf[BUF_LEN];
    int idx = 0;

    while (n >= CACHE_LEN || cache[n] == 0) {
        buf[idx++] = n;

        if (n % 2 == 0LL) {
            n /= 2;
        } else {
            n = n * 3 + 1;
        }
    }

    int len = cache[n];

    while (idx > 0) {
        len++;
        idx--;
        if (buf[idx] < CACHE_LEN) {
            cache[buf[idx]] = len;
        }
    }

    return len;
}

int main(void)
{
    long res = 1;
    int max_len = 1;

    for (long n = 2; n < LIMIT; n++) {
        int len = collatz_length(n);

        if (len > max_len) {
            res = n;
            max_len = len;
        }
    }

    printf("%ld\n", res);

    return 0;
}
