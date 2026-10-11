#include <stdio.h>
#include <limits.h>

#define MAXN 505

long long weight[MAXN];
long long prefix[MAXN];
long long dp[MAXN][MAXN];
int split[MAXN][MAXN];

int main(void) {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &weight[i]);
        prefix[i] = prefix[i - 1] + weight[i];
    }

    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    for (int length = 2; length <= n; length++) {
        for (int i = 1; i + length - 1 <= n; i++) {
            int j = i + length - 1;
            long long sum = prefix[j] - prefix[i - 1];

            dp[i][j] = LLONG_MAX / 4;

            for (int k = i; k < j; k++) {
                long long cost =
                    dp[i][k] + dp[k + 1][j] + sum;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("Minimum weighted path cost = %lld\n",
           n > 0 ? dp[1][n] : 0);

    return 0;
}