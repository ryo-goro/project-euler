// Coded Triangle Numbers
// 162

#include <stdio.h>

#define BUF_LEN 256

int is_triangle(int target)
{
    int triangle_idx = 0;
    int triangle_num = 0;

    while (triangle_num < target) {
        triangle_idx++;
        triangle_num += triangle_idx;
    }

    return triangle_num == target;
}

int word_score(const char *word)
{
    int score = 0;

    while (*word) {
        score += *word++ - 'A' + 1;
    }

    return score;
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
        if (is_triangle(word_score(buf))) {
            count++;
        }
    }

    fclose(fp);

    printf("%d\n", count);

    return 0;
}
