// Coin Sums
// DP

#include <stdio.h>

#define NUM_OF_COINS 8
#define PRICE 200

int main(void)
{
    int coins[NUM_OF_COINS] = {
        1, 2, 5, 10, 20, 50, 100, 200,
    };

    long dp[PRICE + 1] = {1L};

    for (int i = 0; i < NUM_OF_COINS; i++) {
        int coin = coins[i];
        for (int j = coin; j <= PRICE; j++) {
            dp[j] += dp[j - coin];
        }
    }

    printf("%ld\n", dp[PRICE]);

    return 0;
}
