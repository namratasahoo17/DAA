#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int *rating = malloc(n * sizeof(int));
    long long *candy = malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    /* Handle increasing ratings from left to right. */
    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candy[i] = candy[i - 1] + 1;
    }

    /* Handle decreasing ratings from right to left. */
    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1]) {
            candy[i] = candy[i + 1] + 1;
        }
    }

    long long total = 0;
    for (int i = 0; i < n; i++)
        total += candy[i];

    printf("Minimum candies = %lld\n", total);

    free(rating);
    free(candy);
    return 0;
}