// Combinatoric Selections
// 4075

#include <stdio.h>

#define N           100
#define THRESHOLD   1000000L    // 1 million

int main(void)
{
    // n_C_0 = n_C_n = 1
    // n_C_r = {n - 1}_C_{r - 1} + {n - 1}_C_r (1 <= r < n)
    long combinations[N + 1];

    int count = 0;

    for (int n = 1; n <= N; n++) {
        long prev = 1;  // n_C_{r - 1}

        for (int r = 1; r < n; r++) {
            long curr = combinations[r - 1] + combinations[r];  // n_C_r
            if (curr > THRESHOLD) {
                count++;
                curr = THRESHOLD + 1;
            }

            combinations[r - 1] = prev;
            prev = curr;
        }
        
        combinations[n - 1] = prev;
        combinations[n] = 1;
    }

    printf("%d\n", count);

    return 0;
}
