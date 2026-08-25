#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
===========================================================
QUESTION 3: QUICK SORT USING FILE
===========================================================

Implement Quick Sort of N randomly generated elements
stored in a file.


-----------------------------------------------------------
PSEUDOCODE
-----------------------------------------------------------

QUICKSORT(A, low, high)

    if low < high

        p = PARTITION(A, low, high)

        QUICKSORT(A, low, p - 1)

        QUICKSORT(A, p + 1, high)


PARTITION(A, low, high)

    pivot = A[high]

    i = low

    for j = low to high - 1

        if A[j] <= pivot

            swap A[i] and A[j]

            i = i + 1

    swap A[i] and A[high]

    return i


MAIN

    Read N

    Generate N random numbers

    Store the generated numbers in a file

    Open the file for reading

    Read the numbers into an array

    Apply QUICKSort to the array

    Display the sorted elements

    Store the sorted elements in an output file


-----------------------------------------------------------
COMPLEXITY ANALYSIS
-----------------------------------------------------------

Best Case Time Complexity    : O(N log N)

Average Case Time Complexity : O(N log N)

Worst Case Time Complexity   : O(N^2)

Auxiliary Space               : O(log N) average
                                O(N) worst case

File generation and file
reading/writing               : O(N)

The overall sorting complexity is determined by Quick Sort.

The worst case occurs when the pivot repeatedly creates
very unbalanced partitions.


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
PARTITION
-----------------------------------------------------------

The last element is selected as the pivot.

After partitioning:

    Elements <= pivot are placed on the left.

    Elements > pivot are placed on the right.

The pivot is placed in its final sorted position.
-----------------------------------------------------------
*/

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];

    int i = low;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);

            i++;
        }
    }

    swap(&arr[i], &arr[high]);

    return i;
}


/*
-----------------------------------------------------------
QUICK SORT
-----------------------------------------------------------

Quick Sort recursively sorts the two partitions created
by partition().
-----------------------------------------------------------
*/

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        /*
            Sort elements smaller than the pivot.
        */
        quickSort(arr, low, pivotIndex - 1);

        /*
            Sort elements greater than the pivot.
        */
        quickSort(arr, pivotIndex + 1, high);
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
    STEP 1: GENERATE RANDOM ELEMENTS
    -------------------------------------------------------
    */

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /*
        Initialize the random number generator.
    */
    srand((unsigned int)time(NULL));


    /*
    -------------------------------------------------------
    STEP 2: STORE RANDOM ELEMENTS IN A FILE
    -------------------------------------------------------
    */

    FILE *inputFile = fopen("quick_input.txt", "w");

    if (inputFile == NULL)
    {
        printf("Could not create input file.\n");

        free(arr);

        return 1;
    }


    printf("\nRandom elements generated:\n");

    for (int i = 0; i < n; i++)
    {
        /*
            Generate a random number between 0 and 999.
        */
        arr[i] = rand() % 1000;

        /*
            Display the generated number.
        */
        printf("%d ", arr[i]);

        /*
            Store the generated number in the file.
        */
        fprintf(inputFile, "%d ", arr[i]);
    }

    fprintf(inputFile, "\n");

    fclose(inputFile);


    printf("\n\nRandom elements stored in ");
    printf("quick_input.txt\n");


    /*
    -------------------------------------------------------
    STEP 3: READ THE ELEMENTS FROM THE FILE
    -------------------------------------------------------
    */

    inputFile = fopen("quick_input.txt", "r");

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


    printf("\nElements read from quick_input.txt:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");


    /*
    -------------------------------------------------------
    STEP 4: APPLY QUICK SORT
    -------------------------------------------------------
    */

    quickSort(arr, 0, n - 1);


    /*
    -------------------------------------------------------
    STEP 5: DISPLAY SORTED ELEMENTS
    -------------------------------------------------------
    */

    printf("\nElements after Quick Sort:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");


    /*
    -------------------------------------------------------
    STEP 6: STORE SORTED ELEMENTS IN AN OUTPUT FILE
    -------------------------------------------------------
    */

    FILE *outputFile = fopen("quick_output.txt", "w");

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
    printf("quick_output.txt\n");


    /*
    -------------------------------------------------------
    STEP 7: FREE MEMORY
    -------------------------------------------------------
    */

    free(arr);

    return 0;
}