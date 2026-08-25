#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 1: MEDIAN WITHOUT SORTING
===========================================================

Find the median of a list of N numbers without sorting
the list. Do the complexity analysis of your algorithm.


PSEUDOCODE
-----------------------------------------------------------

QUICKSELECT(A, low, high, k)

    while low <= high

        pivotIndex = PARTITION(A, low, high)

        rank = pivotIndex - low + 1

        if rank == k
            return A[pivotIndex]

        else if k < rank
            high = pivotIndex - 1

        else
            k = k - rank
            low = pivotIndex + 1

    return -1


PARTITION(A, low, high)

    pivot = A[high]
    i = low

    for j = low to high - 1

        if A[j] < pivot
            swap A[i] and A[j]
            i = i + 1

    swap A[i] and A[high]

    return i


MEDIAN(A, N)

    if N is odd

        k = (N + 1) / 2
        return QUICKSELECT(A, 0, N-1, k)

    else

        k1 = N / 2
        k2 = N / 2 + 1

        lower = QUICKSELECT(A, 0, N-1, k1)
        upper = QUICKSELECT(A, 0, N-1, k2)

        return (lower + upper) / 2


COMPLEXITY ANALYSIS
-----------------------------------------------------------

Expected Time Complexity : O(N)
Worst-case Time Complexity: O(N^2)
Auxiliary Space           : O(1)

Quickselect is used instead of sorting the complete list.
Only the partition containing the required middle element
is processed further.
===========================================================
*/

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[high]);

    return i;
}

/*
    Quickselect finds the k-th smallest element.

    k is 1-based:
        k = 1  -> smallest element
        k = 2  -> second smallest element
        ...
*/
int quickSelect(int arr[], int low, int high, int k)
{
    while (low <= high)
    {
        int pivotIndex = partition(arr, low, high);

        /*
            Number of elements from low through pivotIndex.
            This gives the rank of the pivot within the
            current subarray.
        */
        int rank = pivotIndex - low + 1;

        if (rank == k)
        {
            return arr[pivotIndex];
        }
        else if (k < rank)
        {
            /*
                Required element is in the left partition.
            */
            high = pivotIndex - 1;
        }
        else
        {
            /*
                Required element is in the right partition.
                Remove the left partition and pivot from
                the required rank.
            */
            k = k - rank;
            low = pivotIndex + 1;
        }
    }

    return -1;
}

int main()
{
    int n;

    printf("Enter N: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("N must be positive.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    /*
        If N is odd, there is one middle element.

        Example:
        N = 5
        Median position = (5 + 1) / 2 = 3
    */
    if (n % 2 == 1)
    {
        int k = (n + 1) / 2;

        int median = quickSelect(arr, 0, n - 1, k);

        printf("Median = %d\n", median);
    }
    else
    {
        /*
            If N is even, there are two middle elements.

            Example:
            N = 6
            Middle positions = 3 and 4

            Median = (3rd smallest + 4th smallest) / 2
        */
        int k1 = n / 2;
        int k2 = (n / 2) + 1;

        int lower = quickSelect(arr, 0, n - 1, k1);
        int upper = quickSelect(arr, 0, n - 1, k2);

        double median = (lower + upper) / 2.0;

        printf("Median = %.2f\n", median);
    }

    free(arr);

    return 0;
}