// Sum Square Difference

#include <stdio.h>

#define N 100L

int main(void)
{
    // (1 + 2 + ... + N)^2 - (1^2 + 2^2 + ... + N^2)
    // = (N * (N + 1) / 2)^2 - N * (N + 1) * (2 * N + 1) / 6
    // = N * (N + 1) * (N - 1) * (3 * N + 2) / 12
    long res = N * (N + 1) * (N - 1) * (3 * N + 2) / 12;

    printf("%ld\n", res);

    return 0;
}
