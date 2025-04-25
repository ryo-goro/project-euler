// XOR Decryption

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
    if (encrypted_text == NULL) {
        fprintf(stderr, "Out of memory\n");
        fclose(fp);
        return 1;
    }

    fseek(fp, 0, SEEK_SET);
    read_chars(fp, encrypted_text);

    char *decrypted_text = malloc(n);
    if (decrypted_text == NULL) {
        fprintf(stderr, "Out of memory\n");
        free(encrypted_text);
        fclose(fp);
        return 1;
    }

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

    /*--- 6 candidates can be obtained by executing the code below ---*/

    // int count = 0;

    // for (char a = 'a'; a <= 'z'; a++) {
    //     for (int i = 0; i < n; i += 3) {
    //         decrypted_text[i] = encrypted_text[i] ^ a;
    //     }

    //     for (char b = 'a'; b <= 'z'; b++) {
    //         for (int i = 1; i < n; i += 3) {
    //             decrypted_text[i] = encrypted_text[i] ^ b;
    //         }

    //         for (char c = 'a'; c <= 'z'; c++) {
    //             for (int i = 2; i < n; i += 3) {
    //                 decrypted_text[i] = encrypted_text[i] ^ c;
    //             }

    //             for (int i = 0; i < n - 3; i++) {
    //                 // The text must contain "The " or "the "
    //                 if (
    //                     (decrypted_text[i] == 't' || decrypted_text[i] == 'T')
    //                     && decrypted_text[i + 1] == 'h'
    //                     && decrypted_text[i + 2] == 'e'
    //                     && decrypted_text[i + 3] == ' '
    //                 ) {
    //                     count++;
    //                     printf("[%d] The decrypted text for the candidate password: \"%c%c%c\":\n", count, a, b, c);
    //                     for (int j = 0; j < n; j++) {
    //                         putchar(decrypted_text[j]);
    //                     }
    //                     printf("\n\n");
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }

    free(decrypted_text);
    free(encrypted_text);
    fclose(fp);

    return 0;
}
