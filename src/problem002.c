// Even Fibonacci Numbers
// 4613732

#include <stdio.h>

#define LIMIT 4000000L // 4 million

int main(void)
{
    long prev = 1L;
    long curr = 2L;

    long sum = 0L;

    while (curr <= LIMIT) {
        if (curr % 2L == 0L) {
            sum += curr;
        }

        long tmp = curr;
        curr += prev;
        prev = tmp;
    }

    printf("%ld\n", sum);

    return 0;
}
