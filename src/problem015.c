// Lattice Paths

#include <stdio.h>

#define N 20

int gcd(int a, int b)
{
    int r;

    while (b > 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int main(void)
{
    // The problem is to calculate 20! / (10!)^2 = (20 * 19 * ... * 11) / (10 * 9 * ... * 1)

    int numerators[N];
    for (int i = 0; i < N; i++) {
        numerators[i] = N + 1 + i;
    }

    for (int i = 2; i <= N; i++) {
        int denominator = i;

        for (int j = 0; j < N; j++) {
            int g = gcd(denominator, numerators[j]);
            denominator /= g;
            numerators[j] /= g;
            if (denominator == 1) {
                break;
            }
        }
    }

    long long res = 1LL;
    for (int i = 0; i < N; i++) {
        res *= numerators[i];
    }

    printf("%lld\n", res);

    return 0;
}
