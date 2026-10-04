#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    int *dp = malloc(n * sizeof(int));

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    // Each element by itself forms an increasing subsequence
    for (int i = 0; i < n; i++)
        dp[i] = A[i];

    // Find the maximum sum increasing subsequence
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                dp[i] = max(dp[i],
                            dp[j] + A[i]);
            }
        }
    }

    // Find the maximum sum
    int answer = dp[0];

    for (int i = 1; i < n; i++)
    {
        if (dp[i] > answer)
            answer = dp[i];
    }

    printf("Maximum Sum Increasing Subsequence = %d\n", answer);

    free(A);
    free(dp);

    return 0;
}