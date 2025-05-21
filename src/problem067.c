// Maximum Path Sum II

#include <ctype.h>
#include <stdio.h>

#define N 100

int max(int a, int b)
{
    return a > b ? a : b;
}

int read_to_array(FILE *fp, int *dst)
{
    int num = 0;
    int count = 0;

    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (isdigit(ch)) {
            num = num * 10 + ch - '0';
        } else {
            dst[count++] = num;
            num = 0;
        }
    }

    dst[count++] = num;

    return count;
}

int main(void)
{
    FILE *fp = fopen("../text/problem067.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open ../text/problem067.txt\n");
        return 1;
    }

    int pyramid[N * (N + 1) / 2];

    read_to_array(fp, pyramid);
    
    fclose(fp);

    int *s[N];
    for (int i = 0; i < N; i++) {
        s[i] = &pyramid[i * (i + 1) / 2];
    }

    for (int h = 1; h < N; h++) {
        s[h][0] += s[h - 1][0];
        s[h][h] += s[h - 1][h - 1];
        for (int w = 1; w < h; w++) {
            s[h][w] += max(s[h - 1][w - 1], s[h - 1][w]);
        }
    }

    int res = s[N - 1][0];
    for (int i = 1; i < N; i++) {
        res = max(res, s[N - 1][i]);
    }

    printf("%d\n", res);

    return 0;
}
