// Cube Digit Pairs

#include <stdio.h>

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse(char *a, int l, int r)
{
    for (int i = 0, h = (r - l) / 2; i < h; i++) {
        swap(char, a[l + i], a[r - 1 - i]);
    }
}

int next_combination(char *comb, int n)
{
    int cursor = n - 1;

    while (cursor >= 0 && comb[cursor]) {
        cursor--;
    }

    // comb = {1, 1, ..., 1}
    if (cursor < 0) {
        return 0;
    }

    do {
        cursor--;
    } while (cursor >= 0 && !comb[cursor]);

    // comb = {0, ..., 0, 1, ..., 1}
    if (cursor < 0) {
        reverse(comb, 0, n);
        return 0;
    }

    comb[cursor] = 0;
    comb[cursor + 1] = 1;
    reverse(comb, cursor + 2, n);

    return 1;
}

// Whether 2 dices can form a specified 2-digit number
int is_formable(const char *dice1, const char *dice2, int two_digit_num)
{
    int first_digit  = two_digit_num / 10;
    int second_digit = two_digit_num % 10;

    if (first_digit == 6 || first_digit == 9) {

        // first_digit = 6 or 9, second_digit = 6 or 9
        if (second_digit == 6 || second_digit == 9) {
            if ((dice1[6] || dice1[9]) && (dice2[6] || dice2[9])) {
                return 1;
            }
            return 0;
        }

        // first_digit = 6 or 9, second_digit != 6 or 9

        if (
               ((dice1[6] || dice1[9]) && dice2[second_digit])
            || (dice1[second_digit] && (dice2[6] || dice2[9]))
        ) {
            return 1;
        }
        return 0;
    }

    // first_digit != 6 or 9, second_digit = 6 or 9
    if (second_digit == 6 || second_digit == 9) {
        if (
                (dice1[first_digit] && (dice2[6] || dice2[9]))
            || ((dice1[6] || dice1[9]) && dice2[first_digit])
        ) {
            return 1;
        }
        return 0;
    }

    // first_digit != 6 or 9, second_digit != 6 or 9
    if ((dice1[first_digit] && dice2[second_digit]) || (dice1[second_digit] && dice2[first_digit])) {
        return 1;
    }
    
    return 0;
}

int equal(const char *a, const char *b, int n)
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    char dice1[10] = {1, 1, 1, 1, 1, 1};
    char dice2[10] = {1, 1, 1, 1, 1, 1};

    int double_count = 0;

    do {
        do {
            int i;
            for (i = 1; i <= 9; i++) {
                if (!is_formable(dice1, dice2, i * i)) {
                    break;
                }
            }
            if (i == 10) {
                if (equal(dice1, dice2, 10)) {
                    double_count += 2;
                } else {
                    double_count++;
                }
            }
        } while (next_combination(dice2, 10));
    } while (next_combination(dice1, 10));

    printf("%d\n", double_count / 2);

    return 0;
}
