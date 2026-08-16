/*
 * DAA Lab-03, Q6: Use of loop invariants in sorting (Selection Sort)
 *
 * Pseudocode:
 *   SELECTION-SORT(A, n)
 *     for i = 1 to n-1
 *         min_idx = i
 *         for j = i+1 to n
 *             if A[j] < A[min_idx]
 *                 min_idx = j
 *         exchange A[i] with A[min_idx]
 *
 * Loop Invariant: At the start of each iteration of the outer for loop
 * (for index i), the subarray A[1 .. i-1] consists of the i-1 smallest
 * elements of the original array, sorted in increasing order.
 *
 *   - Initialization: Before the first iteration (i = 1), A[1 .. 0] is
 *     empty, so the invariant holds trivially.
 *   - Maintenance: In iteration i, we find the minimum of A[i .. n] and
 *     swap it into A[i]. Since A[1 .. i-1] was already the i-1 smallest
 *     elements sorted, and A[i] now holds the smallest of the remaining
 *     elements, A[1 .. i] is the i smallest elements sorted, preserving
 *     the invariant for i+1.
 *   - Termination: The loop ends when i = n. At that point A[1 .. n-1]
 *     holds the n-1 smallest elements sorted, and since A[n] must be the
 *     single largest remaining element, the whole array A[1 .. n] is sorted.
 *
 * Why only the first (n-1) elements? Once the first n-1 elements are
 * placed in sorted order, the last element is automatically the largest
 * remaining element and is already in its correct position -- no
 * comparison is needed for it.
 *
 * Running time: The algorithm always scans the remaining unsorted part
 * to find the minimum, regardless of input order, giving
 *   Worst case: Theta(n^2)
 *   Best case:  Theta(n^2)  -- no better, since the inner loop always
 *               runs the same number of comparisons irrespective of
 *               whether the array is already sorted.
 */

#include <stdio.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("\nBefore sorting: ");
    printArray(arr, n);

    selectionSort(arr, n);

    printf("After sorting:  ");
    printArray(arr, n);

    return 0;
}