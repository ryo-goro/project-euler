// Distinct Powers
// 9183

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

        // Since a is checked in an ascending order, it cannot be written as x^n (n > 1) here
        // Therefore, if there are b, p, q that fulfill a^p = b^q, p is a multiple of q, so b = a^k (k = p/q)

        checked[a] = 1;
        int pow_a = a * a;

        // From the above, if a^2 > MAX, there is no b that fulfills both a < b <= MAX and a^p = b^q
        // So we can count a^2, a^3, ..., a^MAX without worrying about the duplication
        if (pow_a > MAX) {
            total += MAX - 1;
            continue;
        }

        // If a^2 <= MAX, a, a^2, a^3, ..., a^k (where k fulfills a^k <= MAX < a^{k+1})
        // should be counted carefully without duplication

        int count = 1;
        
        do {
            checked[pow_a] = 1;
            count++;
            pow_a *= a;
        } while (pow_a <= MAX);

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
