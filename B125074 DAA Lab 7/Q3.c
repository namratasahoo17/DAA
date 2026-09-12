#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 3: REVE'S PUZZLE
===========================================================

There are four pegs and n disks of different sizes.

Initially, all disks are placed on the first peg in
decreasing order of size, with the largest disk at the
bottom and the smallest at the top.

The objective is to transfer all disks from the first peg
to another peg.

Rules:
    1. Only one disk can be moved at a time.
    2. A larger disk cannot be placed on a smaller disk.

For 8 disks, devise an algorithm that solves the puzzle
in 33 moves.

Generalize the algorithm for n disks.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

REVE(N, SOURCE, DESTINATION, AUX1, AUX2)

    if N == 0
        return

    if N == 1
        Move disk from SOURCE to DESTINATION
        return

    Choose k such that:

        REVE(k) + 2^(N-k) - 1

    is minimum

    REVE(k, SOURCE, AUX1, DESTINATION, AUX2)

    HANOI(N-k, SOURCE, DESTINATION, AUX2)

    REVE(k, AUX1, DESTINATION, SOURCE, AUX2)


HANOI(N, SOURCE, DESTINATION, AUX)

    if N == 0
        return

    HANOI(N-1, SOURCE, AUX, DESTINATION)

    Move disk from SOURCE to DESTINATION

    HANOI(N-1, AUX, DESTINATION, SOURCE)


MAIN

    Read N

    Calculate optimal k

    REVE(N, 1, 4, 2, 3)

    Display total number of moves


-----------------------------------------------------------
ALGORITHM / IDEA
-----------------------------------------------------------

Reve's Puzzle is the four-peg version of the Tower of
Hanoi.

The Frame-Stewart strategy is used.

For n disks:

    1. Choose k smaller disks.
    2. Move these k disks from the source peg to an
       auxiliary peg using all four pegs.
    3. Move the remaining n-k disks to the destination
       peg using the ordinary 3-peg Tower of Hanoi.
    4. Move the k disks from the auxiliary peg to the
       destination peg using four pegs.

Let T(n) be the minimum number of moves for n disks.

For a chosen k:

    T(n) = 2T(k) + 2^(n-k) - 1

The value of k is selected to minimize this expression:

    T(n) = min [ 2T(k) + 2^(n-k) - 1 ]

        where 1 <= k < n


For 8 disks, the optimal split is:

    k = 4

Therefore:

    T(8)
    = 2T(4) + 2^4 - 1
    = 2(9) + 15
    = 33 moves


The optimal number of moves for the first few values is:

    T(0) = 0
    T(1) = 1
    T(2) = 3
    T(3) = 5
    T(4) = 9
    T(5) = 13
    T(6) = 17
    T(7) = 25
    T(8) = 33


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Dynamic Programming calculation:

Time Complexity  : O(N^3)

Space Complexity : O(N)

The DP table stores the minimum number of moves for each
number of disks.

For every n, all possible values of k are checked.

The actual puzzle contains an exponential number of moves.

Therefore, if all individual moves are printed:

Time Complexity  : O(T(N))

where T(N) is the minimum number of moves.

For N = 8:

    T(8) = 33


===========================================================
*/

#define MAX_DISKS 100

long long dp[MAX_DISKS + 1];
int split[MAX_DISKS + 1];

/*
-----------------------------------------------------------
Calculate the minimum number of moves using Dynamic
Programming.
-----------------------------------------------------------
*/
void calculateDP(int n)
{
    dp[0] = 0;

    if (n >= 1)
    {
        dp[1] = 1;
        split[1] = 0;
    }

    for (int disks = 2; disks <= n; disks++)
    {
        dp[disks] = 9223372036854775807LL;

        /*
            Try every possible value of k.
        */
        for (int k = 1; k < disks; k++)
        {
            /*
                Move k disks using four pegs,
                move remaining disks using three pegs,
                then move k disks again.
            */
            long long moves =
                2 * dp[k] +
                ((1LL << (disks - k)) - 1);

            if (moves < dp[disks])
            {
                dp[disks] = moves;
                split[disks] = k;
            }
        }
    }
}

/*
-----------------------------------------------------------
Three-Peg Tower of Hanoi

Moves n disks from source to destination using auxiliary.
-----------------------------------------------------------
*/
void hanoi(int n, int source, int destination, int auxiliary)
{
    if (n == 0)
        return;

    hanoi(n - 1, source, auxiliary, destination);

    printf("Move disk %d from peg %d to peg %d\n",
           n, source, destination);

    hanoi(n - 1, auxiliary, destination, source);
}

/*
-----------------------------------------------------------
Reve's Puzzle using the Frame-Stewart algorithm.
-----------------------------------------------------------
*/
void reve(int n, int source, int destination,
          int auxiliary1, int auxiliary2)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1 from peg %d to peg %d\n",
               source, destination);
        return;
    }

    /*
        Find the optimal split.
    */
    int k = split[n];

    /*
        Step 1:
        Move the smallest k disks to auxiliary1.
    */
    reve(k, source, auxiliary1,
         destination, auxiliary2);

    /*
        Step 2:
        Move the remaining n-k disks using the
        ordinary 3-peg Tower of Hanoi.
    */
    hanoi(n - k, source, destination, auxiliary2);

    /*
        Step 3:
        Move the k disks from auxiliary1 to destination.
    */
    reve(k, auxiliary1, destination,
         source, auxiliary2);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX_DISKS)
    {
        printf("Invalid input.\n");
        printf("Number of disks must be between 0 and %d.\n",
               MAX_DISKS);
        return 1;
    }

    /*
        Calculate minimum number of moves.
    */
    calculateDP(n);

    printf("\nREVE'S PUZZLE\n");
    printf("Number of disks = %d\n", n);
    printf("Minimum number of moves = %lld\n", dp[n]);

    if (n >= 1)
    {
        printf("Optimal split k = %d\n", split[n]);
    }

    /*
        For small values, print the actual sequence of moves.
        This avoids producing an enormous output for large n.
    */
    if (n <= 10)
    {
        printf("\nSequence of moves:\n");

        reve(n, 1, 4, 2, 3);
    }
    else
    {
        printf("\nMove sequence not printed for n > 10.\n");
    }

    return 0;
}