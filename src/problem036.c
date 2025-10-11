// Double-base Palindromes
// 872187

#include <stdio.h>

#define LIMIT 1000000L  // 1 million
#define MAX_NUM_OF_DIGITS 64

int is_palindromic(const int *arr, int n)
{
    for (int i = 0, h = n / 2; i < h; i++) {
        if (arr[i] != arr[n - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

// Example: target = 123, base = 10 -> digits = {3, 2, 1} and the function returns 3
// Example: target = 31,  base = 2  -> digits = {1, 1, 1, 1, 1} and the function returns 5
// base should be > 1
int long_to_arr(int *digits, long target, int base)
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
    int digits[MAX_NUM_OF_DIGITS];
    long long res = 0;

    for (long x = 1; x < LIMIT; x++) {
        int len = long_to_arr(digits, x, 10);
        if (!is_palindromic(digits, len)) {
            continue;
        }

        len = long_to_arr(digits, x, 2);
        if (!is_palindromic(digits, len)) {
            continue;
        }

        res += x;
    }

    printf("%lld\n", res);

    return 0;
}
