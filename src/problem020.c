// Factorial Digit Sum
// 648

#include <stdio.h>

#define N 100
#define LEN 1024

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
    int digits[LEN] = {1};
    int len = 1;

    for (int i = 2; i <= N; i++) {
        multiply_arr(digits, len, i);
        len = carry_digits(digits, len);
    }

    printf("%d\n", sumof(digits, len));

    return 0;
}
