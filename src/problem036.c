// Double-base Palindromes

#include <stdio.h>

#define LIMIT 1000000L  // 1 million
#define LEN 64

int is_palindromic(const int *a, int n)
{
    for (int i = 0, h = n / 2; i < h; i++) {
        if (a[i] != a[n - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int fill_digits(int *digits, long target, int base)
{
    int len = 0;

    while (target > 0L) {
        digits[len++] = (int)(target % base);
        target /= base;
    }

    return len;
}

int main(void)
{
    int digits[LEN];
    int len;

    long long res = 0LL;

    for (long x = 1L; x < LIMIT; x++) {
        len = fill_digits(digits, x, 10);
        if (!is_palindromic(digits, len)) {
            continue;
        }

        len = fill_digits(digits, x, 2);
        if (!is_palindromic(digits, len)) {
            continue;
        }

        res += x;
    }

    printf("%lld\n", res);

    return 0;
}
