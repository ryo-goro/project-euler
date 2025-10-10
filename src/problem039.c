// Integer Right Triangles
// 840

#include <stdio.h>

#define MAX_LEN 1000

int main(void)
{
    int res = 0;
    int max_count = 0;

    for (int p = 6; p <= MAX_LEN; p += 2) {
        int count = 0;
        for (int a = 1, alim = p / 3; a < alim; a++) {
            for (int b = a + 1, blim = (p - a + 1) / 2; b < blim; b++) {
                int c = p - a - b;
                if (((long)a) * a + ((long)b) * b == ((long)c) * c) {
                    count++;
                }
            }
        }

        if (count > max_count) {
            res = p;
            max_count = count;
        }
    }

    printf("%d\n", res);

    return 0;
}
