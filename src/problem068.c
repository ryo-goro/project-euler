// Magic 5-gon Ring
// 6531031914842725

#include <stdio.h>

#define N 5

#define swap(type, x, y)    do { type t = x; x = y; y = t; } while (0)

void reverse(int *a, int l, int r)
{
    for (int i = 0, h = (r - l) / 2; i < h; i++) {
        swap(int, a[l + i], a[r - 1 - i]);
    }
}

int next_permutation(int *a, int n)
{
    int i = n - 2;
    for (; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            break;
        }
    }

    if (i < 0) {
        reverse(a, 0, n);
        return 0;
    }

    int tmp = a[i];
    int j = n - 1;
    for (; j > i; j--) {
        if (a[j] > tmp) {
            break;
        }
    }

    swap(int, a[i], a[j]);
    reverse(a, i + 1, n);

    return 1;
}

int main(void)
{
    int outer[N];
    int inner[N];

    int perm[2 * N - 1];
    for (int i = 0; i < 2 * N - 1; i++) {
        perm[i] = i + 1;
    }

    int digits[3 * N];
    unsigned long long res = 0;

    for (int idx10 = 0; idx10 < N; idx10++) {
        outer[idx10] = 10;
        do {
            for (int i = 0, j = 0; i < N; i++) {
                if (i == idx10) {
                    continue;
                }
                outer[i] = perm[j++];
            }
            for (int i = 0; i < N; i++) {
                inner[i] = perm[i + N - 1];
            }

            if (
                   outer[0] + inner[0] == outer[1] + inner[2]
                && outer[1] + inner[1] == outer[2] + inner[3]
                && outer[2] + inner[2] == outer[3] + inner[4]
                && outer[3] + inner[3] == outer[4] + inner[0]
            ) {
                int idx = 0;
                int min_node = outer[0];
                for (int i = 1; i < N; i++) {
                    if (outer[i] < min_node) {
                        idx = i;
                        min_node = outer[i];
                    }
                }

                for (int i = 0, j = 0; i < N; i++) {
                    digits[j++] = outer[idx];
                    digits[j++] = inner[idx];

                    if (++idx == N) {
                        idx = 0;
                    }
                    digits[j++] = inner[idx];
                }

                unsigned long long candidate = 0;

                for (int i = 0; i < 3 * N; i++) {
                    if (digits[i] == 10) {
                        candidate *= 100;
                    } else {
                        candidate *= 10;
                    }
                    candidate += digits[i];
                }

                if (candidate > res) {
                    res = candidate;
                }
            }
        } while (next_permutation(perm, 2 * N - 1));
    }

    printf("%llu\n", res);

    return 0;
}
