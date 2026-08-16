/*
 * DAA Lab-03, Q1: Binary vs Ternary Search
 *
 * In binary search, an n element list is divided into nearly two equal
 * halves, while in ternary search, it is divided into nearly three equal
 * intervals. Design and implement a C program to search for an element x
 * in a sorted list of size n using binary and ternary search. Justify and
 * validate that binary search is better than ternary search via your
 * implementation (using comparison counts).
 */

#include <stdio.h>

int binaryComparisons = 0, ternaryComparisons = 0;

int binarySearch(int arr[], int lo, int hi, int x) {
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        binaryComparisons++;
        if (arr[mid] == x) return mid;
        binaryComparisons++;
        if (arr[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int ternarySearch(int arr[], int lo, int hi, int x) {
    while (lo <= hi) {
        int mid1 = lo + (hi - lo) / 3;
        int mid2 = hi - (hi - lo) / 3;

        ternaryComparisons++;
        if (arr[mid1] == x) return mid1;
        ternaryComparisons++;
        if (arr[mid2] == x) return mid2;

        ternaryComparisons++;
        if (x < arr[mid1]) hi = mid1 - 1;
        else {
            ternaryComparisons++;
            if (x > arr[mid2]) lo = mid2 + 1;
            else { lo = mid1 + 1; hi = mid2 - 1; }
        }
    }
    return -1;
}

int main() {
    int n;
    printf("Enter size of sorted array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int x;
    printf("Enter element to search: ");
    scanf("%d", &x);

    int idxB = binarySearch(arr, 0, n - 1, x);
    int idxT = ternarySearch(arr, 0, n - 1, x);

    printf("\nBinary Search  : index = %d, comparisons = %d\n", idxB, binaryComparisons);
    printf("Ternary Search : index = %d, comparisons = %d\n", idxT, ternaryComparisons);

    if (binaryComparisons < ternaryComparisons)
        printf("\nConclusion: Binary search used fewer comparisons.\n");
    else if (binaryComparisons > ternaryComparisons)
        printf("\nConclusion: Ternary search used fewer comparisons.\n");
    else
        printf("\nConclusion: Both used equal comparisons.\n");

    printf("Theoretically, binary search is O(log2 n) with ~2 comparisons/level,\n");
    printf("while ternary search is O(log3 n) with ~4 comparisons/level.\n");
    printf("Since 2*log2(n) < 4*log3(n) for large n, binary search is asymptotically better.\n");

    return 0;
}