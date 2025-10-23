// Lychrel Numbers
// 249

#include <stdio.h>

#define LIMIT 10000
#define ITERATION_LIMIT 50
#define MAX_NUM_OF_DIGITS 256

void reverse_arr(int *arr, int n)
{
    for (int i = 0, h = n / 2; i < h; i++) {
        int tmp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = tmp;
    }
}

void copy_arr(int *dst, const int *src, int src_len)
{
    for (int i = 0; i < src_len; i++) {
        dst[i] = src[i];
    }
}

int add_and_carry(int *dst, const int *src, int len)
{
    for (int i = 0; i < len; i++) {
        dst[i] += src[i];
    }

    for (int i = 0; i < len - 1; i++) {
        if (dst[i] >= 10) {
            dst[i] -= 10;
            dst[i + 1]++;
        }
    }

    if (dst[len - 1] < 10) {
        return len;
    }

    dst[len - 1] -= 10;
    dst[len] = 1;
    return len + 1;
}

// Example: target = 123 -> digits = {3, 2, 1} and the function returns 3
int to_digits_rev(int *digits, long target)
{
    int len = 0;

    while (target > 0L) {
        digits[len++] = (int)(target % 10);
        target /= 10;
    }

    return len;
}

int is_palindromic(const int *arr, int n)
{
    for (int i = 0, h = n / 2; i < h; i++) {
        if (arr[i] != arr[n - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int digits[MAX_NUM_OF_DIGITS] = {0};
    int digits_rev[MAX_NUM_OF_DIGITS] = {0};

    int count = 0;

    for (int target = 1; target < LIMIT; target++) {
        int num_of_digits = to_digits_rev(digits, target);
        
        int rep;
        for (rep = 1; rep < ITERATION_LIMIT; rep++) {
            copy_arr(digits_rev, digits, num_of_digits);
            reverse_arr(digits_rev, num_of_digits);
            num_of_digits = add_and_carry(digits, digits_rev, num_of_digits);
            
            if (is_palindromic(digits, num_of_digits)) {
                break;
            }
        }

        if (rep == ITERATION_LIMIT) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
