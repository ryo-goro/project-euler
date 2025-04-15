// Number Spiral Diagonals

#include <stdio.h>

#define N 1001

int main(void)
{
    // 21 22 23 24 25
    // 20  7  8  9 10
    // 19  6  1  2 11
    // 18  5  4  3 12
    // 17 16 15 14 13
    //
    // - To bottom right: 3, 13, 31, ..., 4k^2 - 2k + 1 (k >= 1)
    // - To bottom left: 5, 17, 37, ..., 4k^2 + 1 (k >= 1)
    // - To upper left: 7, 21, 43, ..., 4k^2 + 2k + 1 (k >= 1)
    // - To upper right: 9, 25, 47, ..., 4k^2 + 4k + 1 (k >= 1)
    //
    // The sum of the above 4 terms is 16k^2 + 4k + 4
    // Therefore the result is 1 + < The sum of 16k^2 + 4k + 4 for 1 <= k <= 500 >
    // = (16n^3 + 30n^2 + 26n + 3) / 3 (n = 500)

    long long n = N / 2;
    long long res = (16 * n * n * n + 30 * n * n + 26 * n + 3) / 3;

    printf("%lld\n", res);

    return 0;
}
