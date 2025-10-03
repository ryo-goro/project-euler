// 1000-digit Fibonacci Number
// 4782

#include <stdio.h>

#define THRESHOLD 1000
#define MAX_DIGITS 1024

#define swap(type, x, y) do { type t = x; x = y; y = t; } while (0)

void add_arr(int *dst, const int *src, int n)
{
    for (int i = 0; i < n; i++) {
        dst[i] += src[i];
    }
}

int carry_digits(int *digits, int len)
{
    if (len <= 0) {
        return 0;
    }

    for (int i = 0; i < len - 1; i++) {
        digits[i + 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    int head = len - 1;

    while (digits[head] >= 10) {
        digits[head + 1] = digits[head] / 10;
        digits[head] %= 10;
        head++;
    }

    return head + 1;
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
        add_arr(prev, cur, num_of_digits);
        swap(int *, cur, prev);
        num_of_digits = carry_digits(cur, num_of_digits);
        idx++;
    }

    printf("%d\n", idx);

    return 0;
}
