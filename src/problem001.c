// Multiples of 3 or 5

#include <stdio.h>

#define LIMIT 1000

int main(void)
{
    long num3 = (LIMIT - 1) / 3;
    long num5 = (LIMIT - 1) / 5;
    long num15 = (LIMIT - 1) / 15;

    long sum3 = num3 * (num3 + 1) / 2 * 3;
    long sum5 = num5 * (num5 + 1) / 2 * 5;
    long sum15 = num15 * (num15 + 1) / 2 * 15;

    long res = sum3 + sum5 - sum15;

    printf("%ld\n", res);

    return 0;
}
