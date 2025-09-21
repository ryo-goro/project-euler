// Powerful Digit Sum

#include <stdio.h>

#define LIMIT 100
#define MAX_NUM_OF_DIGITS 256

void multiply(int *digits, int num_of_digits, int multiplier)
{
    for (int i = 0; i < num_of_digits; i++) {
        digits[i] *= multiplier;
    }
}

int carry(int *digits, int num_of_digits)
{
    for (int i = 0; i < num_of_digits - 1; i++) {
        digits[i + 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    int top = digits[num_of_digits - 1];

    if (top < 10) {
        return num_of_digits;
    }

    do {
        digits[num_of_digits++ - 1] = top % 10;
        top /= 10;
    } while (top >= 10);

    digits[num_of_digits - 1] = top;

    return num_of_digits;
}

int sumof(const int *arr, int n)
{
    int res = 0;

    for (int i = 0; i < n; i++) {
        res += arr[i];
    }

    return res;
}

int main(void)
{
    int digits[MAX_NUM_OF_DIGITS];
    int res = 1;

    for (int a = 2; a < LIMIT; a++) {
        int num_of_digits = 1;
        digits[0] = 1;

        for (int b = 1; b < LIMIT; b++) {
            multiply(digits, num_of_digits, a);
            num_of_digits = carry(digits, num_of_digits);

            int sum = sumof(digits, num_of_digits);

            if (sum > res) {
                res = sum;
            }
        }
    }

    printf("%d\n", res);

    return 0;
}
