// Powerful Digit Sum
// 972
// a = 99, b = 95

#include <stdio.h>

#define LIMIT 100
#define MAX_NUM_OF_DIGITS 256

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
    int res = 1;    // 1^b = 1

    for (int a = 2; a < LIMIT; a++) {
        //  a^0 = 1
        int num_of_digits = 1;
        digits[0] = 1;

        for (int b = 1; b < LIMIT; b++) {
            multiply_arr(digits, num_of_digits, a);
            num_of_digits = carry_digits(digits, num_of_digits);

            int sum = sumof(digits, num_of_digits);

            if (sum > res) {
                res = sum;
            }
        }
    }

    printf("%d\n", res);

    return 0;
}
