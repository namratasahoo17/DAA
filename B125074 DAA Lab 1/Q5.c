#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPartition(int a[], int n)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (a[mid] == 1 && (mid == 0 || a[mid - 1] == 0))
            return mid;

        if (a[mid] == 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return n;   // No 1's found (all 0's)
}

int main()
{
    int n;

    printf("Enter array size: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid array size.\n");
        return 1;
    }

    srand(time(NULL));

    int *a = (int *)malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Random transition point (0 to n) */
    int transition = rand() % (n + 1);

    for (int i = 0; i < n; i++)
    {
        if (i < transition)
            a[i] = 0;
        else
            a[i] = 1;
    }

    int result = findPartition(a, n);

    printf("\nRandom transition generated at index : %d\n", transition);
    printf("Binary Search found transition at    : %d\n", result);

    if (transition == result)
        printf("Result: Correct!\n");
    else
        printf("Result: Incorrect!\n");

    if (n <= 50)
    {
        printf("\nGenerated Array:\n");

        for (int i = 0; i < n; i++)
        {
            if (i == result)
                printf("| ");

            printf("%d ", a[i]);
        }

        printf("\n");
    }
    else
    {
        printf("\n(Array not displayed because n > 50)\n");
    }

    free(a);

    return 0;
}