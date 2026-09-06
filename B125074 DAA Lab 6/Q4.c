#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
===========================================================
QUESTION 3: LONGEST COMMON SUBSEQUENCE (LCS)
===========================================================

Implement the Longest Common Subsequence (LCS) algorithm
using Dynamic Programming.

Given two strings, find the length of their longest common
subsequence and display the subsequence.

Analyze the complexity of the algorithm.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

LCS(X, Y)

    m = length of X
    n = length of Y

    Create dp[m+1][n+1]

    for i = 0 to m

        for j = 0 to n

            if i == 0 OR j == 0

                dp[i][j] = 0

            else if X[i-1] == Y[j-1]

                dp[i][j] =
                    dp[i-1][j-1] + 1

            else

                dp[i][j] =
                    maximum(
                        dp[i-1][j],
                        dp[i][j-1]
                    )

    length = dp[m][n]

    Start from dp[m][n]

    while i > 0 AND j > 0

        if X[i-1] == Y[j-1]

            Store X[i-1]
            i = i - 1
            j = j - 1

        else if dp[i-1][j] > dp[i][j-1]

            i = i - 1

        else

            j = j - 1

    Reverse the stored characters

    Display the LCS


-----------------------------------------------------------
WHAT IS A SUBSEQUENCE?
-----------------------------------------------------------

A subsequence is obtained by deleting zero or more
characters without changing the order of the remaining
characters.

For example:

    ABCDE

    ACE

is a subsequence because A, C and E occur in the same
order.


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Let:

    m = length of first string
    n = length of second string

Time Complexity  : O(m * n)

Space Complexity : O(m * n)

The DP table contains (m+1) x (n+1) states and every
state is calculated once.


===========================================================
*/

int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    char X[100];
    char Y[100];

    printf("Enter first string: ");
    scanf("%99s", X);

    printf("Enter second string: ");
    scanf("%99s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    /*
        Allocate the DP table.
    */

    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    if (dp == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));

        if (dp[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    /*
        Fill the DP table.
    */

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            /*
                Empty string has LCS length 0.
            */
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }

            /*
                Characters match.

                Therefore, extend the previous LCS.
            */
            else if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] =
                    dp[i - 1][j - 1] + 1;
            }

            /*
                Characters do not match.

                Take the better result obtained by
                removing one character from either string.
            */
            else
            {
                dp[i][j] =
                    maximum(
                        dp[i - 1][j],
                        dp[i][j - 1]
                    );
            }
        }
    }

    int lcsLength = dp[m][n];

    /*
        Allocate memory for the LCS.
    */
    char *lcs =
        (char *)malloc((lcsLength + 1) * sizeof(char));

    if (lcs == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /*
        Trace backwards through the DP table to
        reconstruct the actual LCS.
    */

    int i = m;
    int j = n;
    int index = lcsLength - 1;

    while (i > 0 && j > 0)
    {
        /*
            Matching characters belong to the LCS.
        */
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];

            index--;

            i--;
            j--;
        }

        /*
            Move in the direction of the larger
            DP value.
        */
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    lcs[lcsLength] = '\0';

    printf("\nLength of LCS = %d\n", lcsLength);

    printf("Longest Common Subsequence = %s\n", lcs);

    /*
        Free allocated memory.
    */

    free(lcs);

    for (i = 0; i <= m; i++)
    {
        free(dp[i]);
    }

    free(dp);

    return 0;
}