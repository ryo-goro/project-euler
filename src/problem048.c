// Self Powers

#include <stdio.h>

#define LIMIT 1000
#define NUM_OF_DIGITS 10

void clear(int *a, int n)
{
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
}

void multiply(int *a, int b, int n)
{
    for (int i = 0; i < n; i++) {
        a[i] *= b;
    }
}

void add(int *dst, const int *src, int src_len)
{
    for (int i = 0; i < src_len; i++) {
        dst[i] += src[i];
    }
}

void carry(int *digits, int len)
{
    for (int i = 1; i < len; i++) {
        digits[i] += digits[i - 1] / 10;
        digits[i - 1] %= 10;
    }
    digits[len - 1] %= 10;
}

int main(void)
{
    int buf[NUM_OF_DIGITS] = {0};
    int res[NUM_OF_DIGITS] = {0};

    for (int i = 1; i <= LIMIT; i++) {
        clear(buf, NUM_OF_DIGITS);
        buf[0] = 1;
        
        for (int j = 0; j < i; j++) {
            multiply(buf, i, NUM_OF_DIGITS);
            carry(buf, NUM_OF_DIGITS);
        }

        add(res, buf, NUM_OF_DIGITS);
        carry(res, NUM_OF_DIGITS);
    }

    for (int i = NUM_OF_DIGITS - 1; i >= 0; i--)
        printf("%d", res[i]);
    putchar('\n');

    return 0;
}
