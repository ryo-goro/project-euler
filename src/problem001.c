// Multiples of 3 or 5
// 233168

#include <stdio.h>

#define LIMIT 1000

long sum_of_multiples(int multiple, int limit)
{
    if (limit <= 0) {
        return 0;
    }

    if (multiple == 0) {
        return 0;
    }

    if (multiple < 0) {
        multiple = -multiple;
    }

    long n = (limit - 1) / multiple;

    return n * (n + 1) / 2 * multiple;
}

int main(void)
{
    long sum3  = sum_of_multiples(3,  LIMIT);
    long sum5  = sum_of_multiples(5,  LIMIT);
    long sum15 = sum_of_multiples(15, LIMIT);

    printf("%ld\n", sum3 + sum5 - sum15);

    return 0;
}
