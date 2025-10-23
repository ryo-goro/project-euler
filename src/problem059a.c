// XOR Decryption

// This code is to find the correct password

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

// Returns a^n
long power(long a, int n)
{
    long res = 1;

    for (int i = 0; i < n; i++) {
        res *= a;
    }

    return res;
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

    char password[PASSWORD_LEN];

    int candidate_no = 0;

    for (long pass_candidate = 0, pow = power(26, PASSWORD_LEN); pass_candidate < pow; pass_candidate++) {
        // Set candidate password
        long tmp = pass_candidate;
        for (int i = 0; i < PASSWORD_LEN; i++) {
            password[i] = tmp % 26 + 'a';
            tmp /= 26;
        }

        // Try decrypting the text with the candidate password
        for (int i = 0; i < PASSWORD_LEN; i++) {
            char key = password[i];

            for (int j = i; j < num_of_chars; j += PASSWORD_LEN) {
                decrypted_text[j] = encrypted_text[j] ^ key;
            }
        }

        for (int i = 0; i < num_of_chars - 3; i++) {
            // The text decrypted with the correct password must contain "The " or "the "
            if (
                (decrypted_text[i] == 't' || decrypted_text[i] == 'T')
                && decrypted_text[i + 1] == 'h'
                && decrypted_text[i + 2] == 'e'
                && decrypted_text[i + 3] == ' '
            ) {
                candidate_no++;
                printf("[%d] The decrypted text for the candidate password \"", candidate_no);
                for (int j = 0; j < PASSWORD_LEN; j++) {
                    putchar(password[j]);
                }
                printf("\":\n\n");
                for (int j = 0; j < num_of_chars; j++) {
                    putchar(decrypted_text[j]);
                }
                printf("\n\n");
                break;
            }
        }
    }

    free(decrypted_text);
    free(encrypted_text);

    return 0;
}
