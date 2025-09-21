// Power Digit Sum
// 1366

#include <stdio.h>

#define N 1000

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

int sumof(const int *arr, int n)
{
    int res = 0;
    
    for (int i = 0; i < n; i++) {
        res += arr[i];
    }

    return res;
}

void multiply_arr(int *arr, int n, int multiplier)
{
    for (int i = 0; i < n; i++) {
        arr[i] *= multiplier;
    }
}

int main(void)
{
    // `digits` should hold all the digits of 2^1000
    // In other words, its length should be > log_10(2^1000) ~ 301
    // So N = 1000 is big enough
    int digits[N] = {1};
    int len = 1;

    for (int i = 0; i < N; i++) {
        multiply_arr(digits, len, 2);
        len = carry_digits(digits, len);
    }

    printf("%d\n", sumof(digits, len));

    return 0;
}
