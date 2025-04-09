// Largest Palindrome Product

#include <stdio.h>

#define STR_LEN 8

int long_to_str_rev(long target, char *dest)
{
    int len = 0;

    do {
        dest[len++] = target % 10L + '0';
        target /= 10L;
    } while (target > 0L);

    dest[len] = '\0';

    return len;
}

int is_palindromic(const char *str, int len)
{
    for (int i = 0, h = len / 2; i < h; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    long res = 0L;
    char str[STR_LEN];

    for (long x = 100L; x < 1000L; x++) {
        for (long y = 100L; y < 1000L; y++) {
            long target = x * y;
            int len = long_to_str_rev(target, str);

            if (is_palindromic(str, len) && target > res) {
                res = target;
            }
        }
    }

    printf("%ld\n", res);

    return 0;
}
