// Lychrel Numbers

#include <stdio.h>

#define LIMIT 10000
#define MAX_ITERATIONS 50
#define MAX_NUM_OF_DIGITS 256

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse(int *a, int n)
{
    for (int i = 0, h = n / 2; i < h; i++) {
        swap(int, a[i], a[n - 1 - i]);
    }
}

void array_copy(int *dst, const int *src, int src_len)
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

int to_array(int *digits, int target)
{
    int num_of_digits = 0;

    do {
        digits[num_of_digits++] = target % 10;
        target /= 10;
    } while (target > 0);

    return num_of_digits;
}

int is_palindromic(const int *digits, int n)
{
    for (int i = 0, h = n / 2; i < h; i++) {
        if (digits[i] != digits[n - 1 - i]) {
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
        int num_of_digits = to_array(digits, target);
        
        int rep;
        for (rep = 1; rep < MAX_ITERATIONS; rep++) {
            array_copy(digits_rev, digits, num_of_digits);
            reverse(digits_rev, num_of_digits);
            num_of_digits = add_and_carry(digits, digits_rev, num_of_digits);
            
            if (is_palindromic(digits, num_of_digits)) {
                break;
            }
        }

        if (rep == MAX_ITERATIONS) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
