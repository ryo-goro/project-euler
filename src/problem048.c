// Self Powers
// 9110846700

#include <stdio.h>

#define LIMIT 1000
#define NUM_OF_DIGITS 10

void multiply_arr(int *arr, int n, int multiplier)
{
    for (int i = 0; i < n; i++) {
        arr[i] *= multiplier;
    }
}

void add_arr(int *dst, const int *src, int n)
{
    for (int i = 0; i < n; i++) {
        dst[i] += src[i];
    }
}

void carry(int *digits, int len)
{
    for (int i = 0; i < len - 1; i++) {
        digits[i + 1] += digits[i] / 10;
        digits[i] %= 10;
    }
    digits[len - 1] %= 10;
}

void reverse_arr(int *arr, int n)
{
    for (int i = 0, h = n / 2; i < h; i++) {
        int tmp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = tmp;
    }
}

void println_arr(const int *arr, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
    putchar('\n');
}

int main(void)
{
    int sum[NUM_OF_DIGITS] = {0};   // The last ten digits of 1^1 + 2^2 + 3^3 + ... + 1000^1000

    for (int i = 1; i <= LIMIT; i++) {
        int pow[NUM_OF_DIGITS] = {1};   // The last ten digits of i^i
        
        for (int j = 0; j < i; j++) {
            multiply_arr(pow, NUM_OF_DIGITS, i);
            carry(pow, NUM_OF_DIGITS);
        }

        add_arr(sum, pow, NUM_OF_DIGITS);
        carry(sum, NUM_OF_DIGITS);
    }

    reverse_arr(sum, NUM_OF_DIGITS);
    println_arr(sum, NUM_OF_DIGITS);

    return 0;
}
