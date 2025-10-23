// XOR Decryption
// 129448

// The password is "exp"
// The decrypted text is in ../text/problem059_decrypted.txt

#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 3

int count_comma(FILE *fp)
{
    int ch;
    int count = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ',') {
            count++;
        }
    }

    return count;
}

void read_chars(FILE *fp, char *dst)
{
    int idx = 0;
    int ch;
    int c = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ',') {
            dst[idx++] = (char)c;
            c = 0;
        } else {
            c = c * 10 + ch - '0';
        }
    }

    dst[idx] = c;
}

int main(void)
{
    FILE *fp = fopen("../text/problem059.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open ../text/problem059.txt\n");
        return 1;
    }

    int n = count_comma(fp) + 1;
    char *encrypted_text = malloc(n);

    fseek(fp, 0, SEEK_SET);
    read_chars(fp, encrypted_text);
    fclose(fp);

    char *decrypted_text = malloc(n);

    char password[PASSWORD_LEN] = "exp";

    for (int i = 0; i < PASSWORD_LEN; i++) {
        char key = password[i];

        for (int j = i; j < n; j += PASSWORD_LEN) {
            decrypted_text[j] = encrypted_text[j] ^ key;
        }
    }

    long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += decrypted_text[i];
    }

    printf("%ld\n", sum);

    free(decrypted_text);
    free(encrypted_text);

    return 0;
}
