// Application of sorting-II: Given two sets S1 and S2 (each of size n), and a number x, describe an O(n · logn) algorithm for finding whether there exists a pair of elements, one from S1 and one from S2, that add up to x. By choosing the proper input representation, write a program in C to validate your algorithm.

/* ALGORITHM FindPair(S1, S2, n, x)

    Sort S2 in ascending order

    FOR i ← 1 TO n DO

        target ← x - S1[i]

        IF BinarySearch(S2, target) = TRUE THEN
            OUTPUT "Pair found: (S1[i], target)"
            RETURN

    END FOR

    OUTPUT "No pair found"

END ALGORITHM */


#include <stdio.h>
#include <stdlib.h>

// algorithm to merge two arrays 

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// mearge sort algorithm

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* Compare function for mearge sort */
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/* Binary Search */
int binarySearch(int arr[], int n, int target)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return 1;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return 0;
}

int main()
{
    int n, x;

    printf("========================================\n");
    printf("       FINDING PAIR SUM TO X\n");
    printf("========================================\n");

    printf("\nEnter size of S1 and S2: ");
    scanf("%d", &n);

    int S1[n];
    int S2[n];

    printf("\nEnter elements of S1:\n");

    for (int i = 0; i < n; i++)
    {
        printf("S1[%d]: ", i + 1);
        scanf("%d", &S1[i]);
    }

    printf("\nEnter elements of S2:\n");

    for (int i = 0; i < n; i++)
    {
        printf("S2[%d]: ", i + 1);
        scanf("%d", &S2[i]);
    }

    printf("\nEnter target sum x: ");
    scanf("%d", &x);

    /*
        Sort S2.

        We only need S2 sorted because
        binary search is performed on S2.
    */

    mergeSort(S2, 0, n - 1);

    printf("\n========================================\n");
    printf("              ANALYSIS\n");
    printf("========================================\n");

    printf("S2 after sorting: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", S2[i]);
    }

    printf("\n");

    /*
        For every element in S1,
        calculate the required element in S2.
    */

    for (int i = 0; i < n; i++)
    {
        int target = x - S1[i];

        printf("\nChecking S1 element: %d\n", S1[i]);
        printf("Required element in S2: %d\n", target);

        if (binarySearch(S2, n, target))
        {
            printf("Pair found: (%d, %d)\n",
                   S1[i], target);

            printf("\n========================================\n");
            printf("              RESULT\n");
            printf("========================================\n");

            printf("Pair = (%d, %d)\n",
                   S1[i], target);

            printf("%d + %d = %d\n",
                   S1[i], target, x);

            printf("\nTime Complexity:\n");
            printf("Sorting S2      = O(n log n)\n");
            printf("Binary searches = O(n log n)\n");
            printf("Overall         = O(n log n)\n");

            return 0;
        }
    }

    /*
        No pair was found.
    */

    printf("\n========================================\n");
    printf("              RESULT\n");
    printf("========================================\n");

    printf("No pair found that adds up to %d.\n", x);

    printf("\nTime Complexity:\n");
    printf("Sorting S2      = O(n log n)\n");
    printf("Binary searches = O(n log n)\n");
    printf("Overall         = O(n log n)\n");

    return 0;
}