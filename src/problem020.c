// Factorial Digit Sum

#include <stdio.h>

#define N 100
#define LEN 1024

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
    int digits[LEN] = {1};
    int len = 1;

    for (int i = 2; i <= N; i++) {
        for (int j = 0; j < len; j++) {
            digits[j] *= i;
        }
        len = carry(digits, len);
    }

    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += digits[i];
    }

    printf("%d\n", sum);

    return 0;
}
