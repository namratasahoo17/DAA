#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
===========================================================
QUESTION 4: HEAP SORT
===========================================================

Implement Heap Sort to sort N randomly generated elements
stored in a file. Do the complexity analysis of your
algorithm.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

HEAPIFY(A, N, i)

    largest = i

    left  = 2*i + 1
    right = 2*i + 2

    if left < N AND A[left] > A[largest]
        largest = left

    if right < N AND A[right] > A[largest]
        largest = right

    if largest != i

        swap A[i] and A[largest]

        HEAPIFY(A, N, largest)


HEAP-SORT(A, N)

    // Build max heap

    for i = N/2 - 1 down to 0

        HEAPIFY(A, N, i)


    // Extract maximum elements

    for i = N-1 down to 1

        swap A[0] and A[i]

        HEAPIFY(A, i, 0)


MAIN fu

    Read N

    Generate N random numbers

    Store the random numbers in a file

    Read the numbers into an array

    HEAP-SORT(A, N)

    Store the sorted array in another file

    Display the sorted array


-----------------------------------------------------------
HOW HEAP SORT WORKS
-----------------------------------------------------------

Heap Sort uses a MAX HEAP.

In a max heap:

        Parent >= Children

Therefore, the largest element is always at:

        A[0]

The algorithm repeatedly:

    1. Builds a max heap.
    2. Takes the largest element from A[0].
    3. Moves it to the end of the array.
    4. Reduces the heap size.
    5. Restores the max-heap property.

After all elements are extracted, the array is sorted
in ascending order.


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Building the heap:

        O(N)

Each extraction:

        O(log N)

There are approximately N extractions.

Therefore:

        O(N) + O(N log N)

        = O(N log N)


Best Case     : O(N log N)
Average Case  : O(N log N)
Worst Case   : O(N log N)

Auxiliary Space:

        O(log N)

because the supplied heapify function is recursive.

The array itself requires O(N) memory.


IMPORTANT:
-----------------------------------------------------------

Heap Sort has a guaranteed O(N log N) running time.

Unlike Quick Sort, it does not have an O(N^2)
worst-case running time.


===========================================================
*/

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/*
-----------------------------------------------------------
HEAPIFY
-----------------------------------------------------------

Maintains the max-heap property for the subtree rooted
at index i.

For an element at index i:

    Left child  = 2*i + 1
    Right child = 2*i + 2

The largest of the parent and its children is placed
at the root of the subtree.
-----------------------------------------------------------
*/

void heapify(int arr[], int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    /*
        Check whether the left child is larger than
        the current largest element.
    */
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    /*
        Check whether the right child is larger than
        the current largest element.
    */
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    /*
        If one of the children is larger than the parent,
        swap them and continue heapifying the affected
        subtree.
    */
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}


/*
-----------------------------------------------------------
HEAP SORT
-----------------------------------------------------------

Step 1:
    Build a max heap.

Step 2:
    The largest element is at arr[0].

Step 3:
    Move arr[0] to the end of the active array.

Step 4:
    Reduce the heap size.

Step 5:
    Restore the heap property.

Repeat until the complete array is sorted.
-----------------------------------------------------------
*/

void heapSort(int arr[], int n)
{
    /*
        BUILD MAX HEAP

        All elements from n/2 onwards are leaves,
        so heap construction starts at n/2 - 1.
    */

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }


    /*
        EXTRACT ELEMENTS

        The largest element is currently at arr[0].

        Move it to the end of the active heap.
    */

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);

        /*
            The heap now contains only elements
            from index 0 to i-1.
        */
        heapify(arr, i, 0);
    }
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


    /*
    -------------------------------------------------------
    ALLOCATE MEMORY
    -------------------------------------------------------
    */

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }


    /*
    -------------------------------------------------------
    GENERATE RANDOM NUMBERS
    -------------------------------------------------------
    */

    /*
        srand() initializes the random-number generator.

        Using time(NULL) gives a different sequence each
        time the program is executed.
    */
    srand((unsigned int)time(NULL));


    /*
        Open file for storing the randomly generated
        elements.
    */
    FILE *inputFile = fopen("heap_input.txt", "w");

    if (inputFile == NULL)
    {
        printf("Could not create input file.\n");
        free(arr);
        return 1;
    }


    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;

        fprintf(inputFile, "%d ", arr[i]);
    }

    fprintf(inputFile, "\n");

    fclose(inputFile);


    printf("\nRandom elements generated and stored in ");
    printf("heap_input.txt\n");


    /*
    -------------------------------------------------------
    READ THE GENERATED DATA FROM THE FILE
    -------------------------------------------------------
    */

    inputFile = fopen("heap_input.txt", "r");

    if (inputFile == NULL)
    {
        printf("Could not open input file.\n");
        free(arr);
        return 1;
    }


    for (int i = 0; i < n; i++)
    {
        fscanf(inputFile, "%d", &arr[i]);
    }

    fclose(inputFile);


    /*
    -------------------------------------------------------
    DISPLAY UNSORTED DATA
    -------------------------------------------------------
    */

    printf("\nElements before sorting:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");


    /*
    -------------------------------------------------------
    APPLY HEAP SORT
    -------------------------------------------------------
    */

    heapSort(arr, n);


    /*
    -------------------------------------------------------
    DISPLAY SORTED DATA
    -------------------------------------------------------
    */

    printf("\nElements after Heap Sort:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");


    /*
    -------------------------------------------------------
    STORE SORTED DATA IN OUTPUT FILE
    -------------------------------------------------------
    */

    FILE *outputFile = fopen("heap_output.txt", "w");

    if (outputFile == NULL)
    {
        printf("Could not create output file.\n");
        free(arr);
        return 1;
    }


    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d ", arr[i]);
    }

    fprintf(outputFile, "\n");

    fclose(outputFile);


    printf("\nSorted elements stored in ");
    printf("heap_output.txt\n");


    /*
    -------------------------------------------------------
    FREE MEMORY
    -------------------------------------------------------
    */

    free(arr);

    return 0;
}