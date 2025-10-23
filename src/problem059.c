// XOR Decryption
// 129448

// The password is "exp"
// The decrypted text is in ../text/problem059_decrypted.txt

#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 3

int count_char(FILE *fp, int target_ch)
{
    int count = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == target_ch) {
            count++;
        }
    }

    return count;
}

// Not versatile
void read_chars(FILE *fp, char *dst)
{
    int idx = 0;
    int ch;
    int ascii_code = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ',') {
            dst[idx++] = (char)ascii_code;
            ascii_code = 0;
        } else {
            ascii_code = ascii_code * 10 + ch - '0';
        }
    }

    dst[idx] = ascii_code;
}

int main(void)
{
    const char *text_path = "../text/problem059.txt";
    FILE *fp = fopen(text_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s\n", text_path);
        return 1;
    }

    int num_of_chars = count_char(fp, ',') + 1;
    char *encrypted_text = malloc(num_of_chars);

    fseek(fp, 0, SEEK_SET);
    read_chars(fp, encrypted_text);
    fclose(fp);

    char *decrypted_text = malloc(num_of_chars);

    const char password[PASSWORD_LEN] = "exp";

    for (int i = 0; i < PASSWORD_LEN; i++) {
        char key = password[i];

        for (int j = i; j < num_of_chars; j += PASSWORD_LEN) {
            decrypted_text[j] = encrypted_text[j] ^ key;
        }
    }

    long sum = 0;
    for (int i = 0; i < num_of_chars; i++) {
        sum += decrypted_text[i];
    }

    printf("%ld\n", sum);

    free(decrypted_text);
    free(encrypted_text);

    return 0;
}
