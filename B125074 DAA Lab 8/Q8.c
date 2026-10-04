#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define INF DBL_MAX

int main()
{
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    double **dp = (double **)malloc((n + 2) * sizeof(double *));
    double **weight = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));

    for (int i = 0; i <= n + 1; i++)
    {
        dp[i] = (double *)malloc((n + 2) * sizeof(double));
        weight[i] = (double *)malloc((n + 2) * sizeof(double));
        root[i] = (int *)malloc((n + 2) * sizeof(int));
    }

    printf("Enter successful search probabilities p[1] to p[%d]:\n", n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &p[i]);
    }

    printf("Enter unsuccessful search probabilities q[0] to q[%d]:\n", n);

    for (int i = 0; i <= n; i++)
    {
        scanf("%lf", &q[i]);
    }

    /*
       Base case:
       Empty subtree containing no keys.
    */

    for (int i = 1; i <= n + 1; i++)
    {
        dp[i][i - 1] = q[i - 1];
        weight[i][i - 1] = q[i - 1];
    }

    /*
       Build solutions for increasing subtree lengths.
    */

    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = INF;

            /*
               Total probability of this subtree.
            */

            weight[i][j] =
                weight[i][j - 1] + p[j] + q[j];

            /*
               Try every key as root.
            */

            for (int r = i; r <= j; r++)
            {
                double cost =
                    dp[i][r - 1]
                    + dp[r + 1][j]
                    + weight[i][j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.4lf\n",
           dp[1][n]);

    printf("\nOptimal Root = Key %d\n",
           root[1][n]);

    printf("\nRoot table:\n");

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            printf("root[%d][%d] = %d\n",
                   i, j, root[i][j]);
        }
    }

    /*
       Free memory.
    */

    for (int i = 0; i <= n + 1; i++)
    {
        free(dp[i]);
        free(weight[i]);
        free(root[i]);
    }

    free(dp);
    free(weight);
    free(root);

    free(p);
    free(q);

    return 0;
}