// Largest Exponential

#include <ctype.h>
#include <math.h>
#include <stdio.h>

#define N 1000

long read_to_long(FILE *fp)
{
    long res = 0;
    int ch;

    while (isdigit(ch = fgetc(fp))) {
        res = res * 10 + ch - '0';
    }

    return res;
}

int main(void)
{
    FILE *fp = fopen("../text/problem099.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open ../text/problem099.txt\n");
        return 1;
    }

    long base[N];
    long power[N];

    for (int i = 0; i < N; i++) {
        base[i] = read_to_long(fp);
        power[i] = read_to_long(fp);
    }

    fclose(fp);

    // a^b < c^d <-> b * log10(a) < d * log10(c) (a, c > 0)

    double max = power[0] * log10(base[0]);
    int max_idx = 0;

    for (int i = 1; i < N; i++) {
        double candidate = power[i] * log10(base[i]);
        if (candidate > max) {
            max = candidate;
            max_idx = i;
        }
    }

    printf("%d\n", max_idx + 1);

    return 0;
}
