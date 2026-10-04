#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, amount;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = malloc(n * sizeof(int));

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &amount);

    long long *dp = calloc(amount + 1, sizeof(long long));

    // There is one way to make amount 0: choose nothing
    dp[0] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = coins[i]; j <= amount; j++)
        {
            dp[j] += dp[j - coins[i]];
        }
    }

    printf("Total number of ways = %lld\n", dp[amount]);

    free(coins);
    free(dp);

    return 0;
}