// Largest Prime Factor

#include <stdio.h>

#define TARGET 600851475143LL

int main(void)
{
    long long target = TARGET;
    long long res = 0LL;

    for (long long factor = 3LL; factor * factor <= target; factor += 2LL) {
        if (target % factor == 0LL) {
            res = factor;
            do {
                target /= factor;
            } while (target % factor == 0LL);
        }
    }

    if (res < target) {
        res = target;
    }

    printf("%lld\n", res);

    return 0;
}
