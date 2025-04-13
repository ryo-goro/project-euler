// Names Scores

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const char **s, const char **t)
{
    return strcmp(*s, *t);
}

int main(void)
{
    FILE *fp;
    if ((fp = fopen("../text/problem022.txt", "r")) == NULL) {
        fprintf(stderr, "Cannot open ../text/problem022.txt\n");
        return 1;
    }

    int ch;
    int raw_line_len = 0;
    int names_count = 1;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '"') {
            continue;
        }
        if (ch == ',') {
            names_count++;
        }
        raw_line_len++;
    }

    char *raw_line = (char *)malloc(raw_line_len + 1);
    if (raw_line == NULL) {
        fprintf(stderr, "Out of memory\n");
        fclose(fp);
        return 1;
    }

    char **names = (char **)calloc(names_count, sizeof(char *));
    if (names == NULL) {
        fprintf(stderr, "Out of memory\n");
        fclose(fp);
        free(raw_line);
        return 1;
    }
    
    names[0] = &raw_line[0];
    names_count = 1;

    fseek(fp, 0, SEEK_SET);
    
    int idx = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '"') {
            continue;
        }
        if (ch == ',') {
            raw_line[idx++] = '\0';
            names[names_count++] = &raw_line[idx];
        } else {
            raw_line[idx++] = ch;
        }
    }
    raw_line[raw_line_len] = '\0';

    fclose(fp);

    qsort(names, names_count, sizeof(char *), (int (*)(const void *, const void *))compare);

    long total = 0;
    for (int i = 0; i < names_count; i++) {
        char *name = names[i];
        long score = 0;
        while (*name) {
            score += *name++ - 'A' + 1;
        }
        total += score * (i + 1);
    }
    
    printf("%ld\n", total);

    free(names);
    free(raw_line);

    return 0;
}
