// Distinct Powers

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main(void)
{
    int checked[MAX + 1] = {0};
    int total = 0;

    for (int a = 2; a <= MAX; a++) {
        if (checked[a]) {
            continue;
        }

        checked[a] = 1;

        if (a * a > MAX) {
            total += MAX - 1;
            continue;
        }

        int count = 1;
        int aa = a * a;
        while (aa <= MAX) {
            checked[aa] = 1;
            count++;
            aa *= a;
        }

        int len = count * MAX + 1;
        int *exponents = calloc(len, sizeof(int));
        for (int b = 2; b <= MAX; b++) {
            for (int c = 1; c <= count; c++) {
                exponents[b * c] = 1;
            }
        }

        for (int i = 2; i < len; i++) {
            if (exponents[i]) {
                total++;
            }
        }

        free(exponents);
    }

    printf("%d\n", total);

    return 0;
}
