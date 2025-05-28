// Counting Summations
// Ref: https://manabitimes.jp/math/888

#include <stdio.h>

#define N 100

int main(void)
{
    long p[N + 1][N + 1] = {0};
    p[1][1] = 1;

    for (int n = 2; n <= N; n++) {
        for (int k = 1; k <= n; k++) {
            p[n][k] = p[n - 1][k - 1] + p[n - k][k];
        }
    }

    long res = 0;
    for (int k = 2; k <= N; k++) {
        res += p[N][k];
    }

    printf("%ld\n", res);

    return 0;
}
