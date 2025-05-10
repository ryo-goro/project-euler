// Powerful Digit Counts

#include <stdio.h>
#include <math.h>

int main(void)
{
    // 10^(n - 1) <= a^n < 10^n となる自然数 a, n の組を考える
    // まず後半の不等式から, 1 <= a <= 9 を得る
    // 前半の不等式の両辺の常用対数を取って計算すると, n <= 1 / (1 - log(a)) を得る
    // そこで a = 1, 2, ..., 9 のそれぞれについて, n <= 1 / (1 - log(a)) を満たす自然数 n の個数を数え, それらの合計を求めれば良い

    int total = 0;

    for (int a = 1; a <= 9; a++) {
        total += 1 / (1 - log10(a));
    }

    printf("%d\n", total);

    return 0;
}
