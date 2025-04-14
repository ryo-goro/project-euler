// 1000-digit Fibonacci Number

#include <stdio.h>

#define THRESHOLD 1000
#define MAX_DIGITS 1024

#define swap(type, x, y) do { type t = x; x = y; y = t; } while (0)

void add(int *dst, const int *src, int src_len)
{
    for (int i = 0; i < src_len; i++) {
        dst[i] += src[i];
    }
}

int carry(int *digits, int len)
{
    for (int i = 0; i < len; i++) {
        digits[i + 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    while (digits[len] > 0) {
        digits[len + 1] += digits[len] / 10;
        digits[len] %= 10;
        len++;
    }

    return len;
}

int main(void)
{
    int idx = 2;
    int digits1[MAX_DIGITS] = {1};
    int digits2[MAX_DIGITS] = {1};

    int *cur = digits1;
    int *prev = digits2;
    int num_of_digits = 1;

    while (num_of_digits < THRESHOLD) {
        add(prev, cur, num_of_digits);
        swap(int *, cur, prev);
        num_of_digits = carry(cur, num_of_digits);
        idx++;
    }

    printf("%d\n", idx);

    return 0;
}
