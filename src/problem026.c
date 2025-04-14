// Reciprocal Cycles

#include <stdio.h>

#define LIMIT 1000

// Returns the length of the shortest repetend of 1 / n
int cycle_len(int n, int *work)
{
    int nom = 10;
    int len = 1;
    
    work[1] = 1;

    while (1) {
        int d = nom / n;
        int r = nom % n;
        len++;
        if (work[r]) {
            return len - work[r];
        }
        work[r] = len;
        nom = 10 * (nom - n * d);
    }
}

int main(void)
{
    int max_len = 0;
    int res = -1;
    int work[LIMIT];

    for (int d = 2, len; d < LIMIT; d++) {
        for (int j = 0; j < LIMIT; j++) {
            work[j] = 0;
        }

        if (max_len < (len = cycle_len(d, work))) {
            max_len = len;
            res = d;
        }
    }

    printf("%d\n", res);

    return 0;
}
