#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 4: SECURITY SWITCHES
===========================================================

There is a row of n security switches.

The switches can be manipulated as follows:

1. The rightmost switch may be turned ON or OFF at will.

2. Any other switch may be turned ON or OFF only if the
   switch immediately to its right is ON and all other
   switches to its right are OFF.

3. Only one switch may be toggled at a time.

Initially, all switches are ON.

Design an algorithm to turn OFF all switches using the
minimum number of moves.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

SECURITY_SWITCHES(N)

    if N == 0
        return 0

    if N == 1
        toggle switch 1
        return 1

    moves = 0

    while not all switches are OFF

        Find the leftmost switch that can be toggled

        Toggle that switch

        moves = moves + 1

    return moves


-----------------------------------------------------------
ALGORITHM / IDEA
-----------------------------------------------------------

Represent the switches as a binary array:

    1 = ON
    0 = OFF

Initially:

    111...111

The rightmost switch can always be toggled.

For a switch i (except the rightmost switch), it can be
toggled only when:

    switch i+1 = 1

and every switch to its right after i+1 is OFF.

Thus, at any point, only one non-rightmost switch is
eligible, together with the rightmost switch.

To obtain the minimum sequence, we recursively solve the
problem.

For n switches:

    1. First turn OFF the first n-1 switches.
    2. Toggle the nth switch.
    3. Solve the remaining configuration recursively.

The minimum number of moves follows the recurrence:

    T(n) = 2T(n-1) + 1

with:

    T(1) = 1

Solving the recurrence gives:

    T(n) = 2^n - 1


For example:

    n = 1  ->  1 move
    n = 2  ->  3 moves
    n = 3  ->  7 moves
    n = 4  -> 15 moves

Therefore, for n switches:

    Minimum moves = 2^n - 1


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Time Complexity  : O(2^N)

Space Complexity : O(N)

There are exactly 2^N - 1 toggles in the minimum sequence.

The recursive algorithm uses at most N levels of recursion.


===========================================================
*/

long long minimumMoves(int n)
{
    /*
        Minimum moves required:

            T(n) = 2^n - 1

        Start with 1 and multiply by 2, n times.
    */
    long long moves = 1;

    for (int i = 0; i < n; i++)
    {
        moves = moves * 2;
    }

    return moves - 1;
}

/*
-----------------------------------------------------------
Recursive procedure to generate the minimum sequence.

The switches are numbered from 1 to n.
0 = OFF
1 = ON
-----------------------------------------------------------
*/

void turnOffSwitches(int n, int switches[])
{
    if (n == 0)
        return;

    if (n == 1)
    {
        switches[0] = 0;

        printf("Toggle switch 1 -> OFF\n");

        return;
    }

    /*
        Solve the first n-1 switches.
    */
    turnOffSwitches(n - 1, switches);

    /*
        Toggle switch n.
    */
    switches[n - 1] = 0;

    printf("Toggle switch %d -> OFF\n", n);

    /*
        The recursive process continues according to
        the allowed switching condition.
    */
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of switches must be positive.\n");
        return 1;
    }

    /*
        Prevent overflow in the demonstration formula.
    */
    if (n >= 63)
    {
        printf("n is too large for long long calculation.\n");
        return 1;
    }

    long long moves = minimumMoves(n);

    printf("\nSECURITY SWITCHES\n");
    printf("Number of switches = %d\n", n);
    printf("Minimum number of moves = %lld\n", moves);

    /*
        Display the move sequence for small inputs.
    */
    if (n <= 10)
    {
        int *switches =
            (int *)malloc(n * sizeof(int));

        if (switches == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        /*
            Initially all switches are ON.
        */
        for (int i = 0; i < n; i++)
        {
            switches[i] = 1;
        }

        printf("\nInitial state: ");

        for (int i = 0; i < n; i++)
        {
            printf("%d ", switches[i]);
        }

        printf("\n\nMove sequence:\n");

        turnOffSwitches(n, switches);

        printf("\nFinal state: ");

        for (int i = 0; i < n; i++)
        {
            printf("%d ", switches[i]);
        }

        printf("\n");

        free(switches);
    }
    else
    {
        printf("\nMove sequence not printed for n > 10.\n");
    }

    return 0;
}