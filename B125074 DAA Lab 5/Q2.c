#include <stdio.h>
#include <stdlib.h>

/*
===========================================================
QUESTION 2: K-TH SMALLEST ELEMENT WITHOUT SORTING
===========================================================

Find the K'th smallest element in a given list of N numbers
without sorting the list. Do the complexity analysis of
your algorithm.


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


KTH-SMALLEST(A, N, K)

    return QUICKSELECT(A, 0, N-1, K)


COMPLEXITY ANALYSIS
-----------------------------------------------------------

Expected Time Complexity : O(N)
Worst-case Time Complexity: O(N^2)
Auxiliary Space           : O(1)

Quickselect does not sort the complete list. After each
partition, only the part containing the K'th smallest element
is processed further.

The expected O(N) complexity occurs when the partitions are
reasonably balanced. Since this implementation always uses
the last element as the pivot, its worst case is O(N^2).
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
    Finds the K'th smallest element.

    K is 1-based:
        K = 1 -> smallest element
        K = 2 -> second smallest element
        K = N -> largest element
*/
int quickSelect(int arr[], int low, int high, int k)
{
    while (low <= high)
    {
        int pivotIndex = partition(arr, low, high);

        /*
            Rank of the pivot within the current subarray.
        */
        int rank = pivotIndex - low + 1;

        /*
            Pivot itself is the K'th smallest element.
        */
        if (rank == k)
        {
            return arr[pivotIndex];
        }

        /*
            Required element is in the left partition.
        */
        else if (k < rank)
        {
            high = pivotIndex - 1;
        }

        /*
            Required element is in the right partition.

            The elements in the left partition and the pivot
            are removed from consideration, so K is reduced
            by their count.
        */
        else
        {
            k = k - rank;
            low = pivotIndex + 1;
        }
    }

    return -1;
}

int main()
{
    int n, k;

    printf("Enter N: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("N must be positive.\n");
        return 1;
    }

    printf("Enter K (1 <= K <= N): ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of K.\n");
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

    int answer = quickSelect(arr, 0, n - 1, k);

    printf("%d-th smallest element = %d\n", k, answer);

    free(arr);

    return 0;
}