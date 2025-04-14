// Lexicographic Permutations

#define TARGET 1000000L // 1 million
#define NUM 10

#include <stdio.h>

int main(void)
{
    int terms[NUM];
    long target = TARGET - 1L;

    for (int i = 1; i <= NUM; i++) {
        terms[i - 1] = target % i;
        target /= i;
    }

    int used[NUM] = {0};

    for (int i = NUM - 1; i >= 0; i--) {
        int j = 0;
        while (used[j]) {
            j++;
        }

        int term = terms[i];

        for (; j < NUM; j++) {
            if (!used[j] && term-- == 0) {
                printf("%d", j);
                used[j] = 1;
                break;
            }
        }
    }
    putchar('\n');

    return 0;
}
