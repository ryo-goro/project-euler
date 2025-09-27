// Names Scores
// 871198282

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long count_char(FILE *fp, int target_ch)
{
    fseek(fp, 0, SEEK_SET);

    long count = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == target_ch) {
            count++;
        }
    }

    return count;
}

long count_all_chars(FILE *fp)
{
    fseek(fp, 0, SEEK_SET);

    long count = 0;

    while (fgetc(fp) != EOF) {
        count++;
    }

    return count;
}

void load_names(FILE *fp, char *dst)
{
    fseek(fp, 0, SEEK_SET);

    long idx = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '"') {
            continue;
        }
        dst[idx++] = (ch == ',') ? '\0' : ch;
    }

    dst[idx] = '\0';
}

int compare(const char **s, const char **t)
{
    return strcmp(*s, *t);
}

int name_score(const char *name)
{
    int score = 0;

    while (*name) {
        score += *name++ - 'A' + 1;
    }

    return score;
}

int main(void)
{
    const char *text_path = "../text/problem022.txt";
    FILE *fp = fopen(text_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s\n", text_path);
        return 1;
    }

    long num_of_quots = count_char(fp, '"');
    long raw_line_len = count_all_chars(fp) - num_of_quots + 1;

    char *raw_line = (char *)malloc(raw_line_len);
    load_names(fp, raw_line);
    
    fclose(fp);

    long num_of_names = num_of_quots / 2;
    char **names = (char **)calloc(num_of_names, sizeof(char *));
    
    long name_count = 0;
    char *raw_line_ptr = raw_line;
    int flag = 1;

    while (name_count < num_of_names) {
        if (flag) {
            names[name_count++] = raw_line_ptr;
            flag = 0;
        }

        if (*raw_line_ptr == '\0') {
            flag = 1;
        }

        raw_line_ptr++;
    }

    qsort(names, num_of_names, sizeof(char *), (int (*)(const void *, const void *))compare);

    long total = 0;
    for (int i = 0; i < num_of_names; i++) {
        total += ((long)name_score(names[i])) * (i + 1);
    }
    
    printf("%ld\n", total);

    free(names);
    free(raw_line);

    return 0;
}
