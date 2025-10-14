// Coded Triangle Numbers
// 162

#include <ctype.h>
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

// Reads consecutive uppercase letters from a file into an array
// and returns the number of letters read
// Needs <ctype.h>
int read_word(FILE *fp, char *dest)
{
    int ch;

    // Ignore leading chararacters that are not uppercase letters
    while ((ch = fgetc(fp)) != EOF) {
        if (isupper(ch)) {
            break;
        }
    }

    if (ch == EOF) {
        *dest = '\0';
        return 0;
    }

    // Here, ch is an uppercase letter
    *dest++ = ch;
    int word_len = 1;

    while ((ch = fgetc(fp)) != EOF) {
        if (!isupper(ch)) {
            *dest = '\0';
            return word_len;
        }

        *dest++ = ch;
        word_len++;
    }

    *dest = '\0';
    return word_len;
}

int main(void)
{
    const char *text_path = "../text/problem042.txt";
    FILE *fp = fopen(text_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s\n", text_path);
        return 1;
    }

    int count = 0;
    char buf[BUF_LEN];

    while (read_word(fp, buf) > 0) {
        if (is_triangle(word_score(buf))) {
            count++;
        }
    }

    fclose(fp);

    printf("%d\n", count);

    return 0;
}
