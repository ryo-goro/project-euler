// Reciprocal Cycles
// 983

#include <stdio.h>

#define LIMIT 1000
#define WORK_LEN 1024   // Should be equal to or larger than `n`, the argument of cycle_len

// Returns the length of the shortest repetend of 1 / n
// n should be > 0
int cycle_len(int n)
{
    int nom = 10;
    int len = 1;
    int work[WORK_LEN] = {0, 1};

    while (1) {
        int r = nom % n;
        len++;
        if (work[r]) {
            return len - work[r];
        }
        work[r] = len;
        nom = 10 * r;
    }
}

int main(void)
{
    int max_len = 1;
    int res = 1;

    for (int d = 2; d < LIMIT; d++) {
        int len = cycle_len(d);

        if (max_len < len) {
            max_len = len;
            res = d;
        }
    }

    printf("%d\n", res);

    return 0;
}
