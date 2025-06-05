// Roman Numerals

#include <stdio.h>
#include <string.h>

#define N 1000
#define MAX_ROMAN_LEN 64

int roman_char_to_num(char roman_char)
{
    switch (roman_char) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
    }

    return -1;
}

int roman_to_num(const char *roman)
{
    int res = 0;
    int cur = 1000;
    int count = 0;

    while (*roman) {
        int next = roman_char_to_num(*roman++);
        if (next == cur) {
            count++;
        } else if (next < cur) {
            res += cur * count;
            cur = next;
            count = 1;
        } else {
            res += next - cur * count;
            if (*roman == '\0') {
                return res;
            }
            cur = roman_char_to_num(*roman++);
            count = 1;
        }
    }

    res += cur * count;

    return res;
}

int num_to_roman(char *roman, int num)
{
    int len = 0;

    int one_count = num % 10;
    num /= 10;
    int ten_count = num % 10;
    num /= 10;
    int hundred_count = num % 10;
    num /= 10;
    int thousand_count = num;

    /*--- Thousand ---*/
    for (int i = 0; i < thousand_count; i++) {
        roman[i] = 'M';
    }
    len += thousand_count;

    /*--- Hundred ---*/
    // hundred_count = 0, 1, 2, 3
    if (hundred_count < 4) {
        for (int i = 0; i < hundred_count; i++) {
            roman[len + i] = 'C';
        }
        len += hundred_count;
    
    // hundred_count = 4
    } else if (hundred_count == 4) {
        roman[len] = 'C';
        roman[len + 1] = 'D';
        len += 2;
    
    // hundred_count = 5, 6, 7, 8
    } else if (hundred_count < 9) {
        roman[len] = 'D';
        for (int i = 1; i < hundred_count - 4; i++) {
            roman[len + i] = 'C';
        }
        len += hundred_count - 4;
    
    // hundred_count = 9
    } else {
        roman[len] = 'C';
        roman[len + 1] = 'M';
        len += 2;
    }

    /*--- Ten ---*/
    // ten_count = 0, 1, 2, 3
    if (ten_count < 4) {
        for (int i = 0; i < ten_count; i++) {
            roman[len + i] = 'X';
        }
        len += ten_count;
    
    // ten_count = 4
    } else if (ten_count == 4) {
        roman[len] = 'X';
        roman[len + 1] = 'L';
        len += 2;
    
    // ten_count = 5, 6, 7, 8
    } else if (ten_count < 9) {
        roman[len] = 'L';
        for (int i = 1; i < ten_count - 4; i++) {
            roman[len + i] = 'X';
        }
        len += ten_count - 4;
    
    // ten_count = 9
    } else {
        roman[len] = 'X';
        roman[len + 1] = 'C';
        len += 2;
    }

    /*--- One ---*/
    // one_count = 0, 1, 2, 3
    if (one_count < 4) {
        for (int i = 0; i < one_count; i++) {
            roman[len + i] = 'I';
        }
        len += one_count;
    
    // one_count = 4
    } else if (one_count == 4) {
        roman[len] = 'I';
        roman[len + 1] = 'V';
        len += 2;
    
    // one_count = 5, 6, 7, 8
    } else if (one_count < 9) {
        roman[len] = 'V';
        for (int i = 1; i < one_count - 4; i++) {
            roman[len + i] = 'I';
        }
        len += one_count - 4;
    
    // one_count = 9
    } else {
        roman[len] = 'I';
        roman[len + 1] = 'X';
        len += 2;
    }

    roman[len] = '\0';

    return len;
}

int num_to_roman_len(int num)
{
    int count[4];
    for (int i = 0; i < 4; i++) {
        count[i] = num % 10;
        num /= 10;
    }

    int len = count[3];

    for (int i = 0; i < 3; i++) {
        switch (count[i]) {
            case 1:
            case 2:
            case 3:
                len += count[i];
                break;
            
            case 5:
            case 6:
            case 7:
            case 8:
                len += count[i] - 4;
                break;

            case 4:
            case 9:
                len += 2;
                break;
        }
    }

    return len;
}

int main(void)
{
    FILE *fp = fopen("../text/problem089.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open ../text/problem089.txt\n");
        return 1;
    }

    char roman[MAX_ROMAN_LEN];
    // char canonical_roman[MAX_ROMAN_LEN];

    int res = 0;

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%s", roman);
        // num_to_roman(canonical_roman, roman_to_num(roman));
        // printf("%s -> %s\n", roman, canonical_roman);
        res += strlen(roman) - num_to_roman_len(roman_to_num(roman));
    }

    printf("%d\n", res);

    fclose(fp);

    return 0;
}
