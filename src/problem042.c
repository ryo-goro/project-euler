// Coded Triangle Numbers

#include <stdio.h>

#define BUF_LEN 256

int is_triangle(const char *str)
{
    int n = 0;
    while (*str) {
        n += *str++ - 'A' + 1;
    }

    int t = 1;
    int m = 1;

    while (t < n) {
        t += ++m;
    }

    return t == n;
}

int read_word(FILE *fp, char *dest)
{
    int ch;
    if ((ch = fgetc(fp)) == EOF) {
        return 0;
    }

    while (ch == '"' || ch == ',') {
        ch = fgetc(fp);
    }

    do {
        *dest++ = ch;
    } while ((ch = fgetc(fp)) != '"');

    *dest = '\0';

    return 1;
}

int main(void)
{
    int count = 0;
    char buf[BUF_LEN];

    FILE *fp = fopen("../text/problem042.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open ../text/problem042.txt\n");
        return 1;
    }

    while (read_word(fp, buf)) {
        if (is_triangle(buf)) {
            count++;
        }
    }

    fclose(fp);

    printf("%d\n", count);

    return 0;
}
