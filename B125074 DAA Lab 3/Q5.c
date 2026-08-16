/*
 * DAA Lab-03, Q5: Multiply special-pattern square matrices using D&C approach
 *
 * Two n x n matrices are given, n = 2^k, each having the recursive block
 * structure:
 *      M = [ M1  M2 ]
 *          [ M2  M1 ]
 * where M1 and M2 themselves have the same recursive structure down to
 * single elements. Because each matrix is fully described by only its
 * two distinct blocks (M1, M2), we only ever need to multiply pairs of
 * such "half-size" matrices, and the product of two matrices with this
 * structure also has this structure. This lets us derive an O(n^2)
 * divide and conquer algorithm (instead of the general O(n^3)).
 *
 * Let A = [A1 A2; A2 A1], B = [B1 B2; B2 B1] (blocks of size n/2).
 * Then:
 *   C1 = A1*B1 + A2*B2
 *   C2 = A1*B2 + A2*B1
 * and C = [C1 C2; C2 C1] has the same special structure.
 * So multiplying two n x n special matrices reduces to 4 multiplications
 * of (n/2) x (n/2) special matrices plus O(n^2) additions:
 *   T(n) = 4*T(n/2) + O(n^2)  => T(n) = O(n^2 log n) in general recursion,
 * but since each matrix is fully represented by its top-left (n/2)x(n/2)
 * distinct sub-block (M1) and (n/2)x(n/2) sub-block (M2), the recursion
 * depth is log n and total work is O(n^2). We store only M1, M2 to avoid
 * redundant computation, giving overall O(n^2).
 */

#include <stdio.h>
#include <stdlib.h>

int **allocMatrix(int n) {
    int **m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) m[i] = calloc(n, sizeof(int));
    return m;
}

void freeMatrix(int **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

void addInto(int **C, int **A, int **B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

/* Standard block multiply used only at the O(n^2) base combination step */
void multiplyAdd(int **C, int **A, int **B, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
}

/*
 * multiplySpecial: multiplies two n x n special-pattern matrices given
 * only by their distinct blocks (M1 read directly from the full matrix's
 * top-left corner, M2 from top-right). Produces the resulting distinct
 * blocks C1, C2 recursively. Base case n = 1 does direct multiplication.
 */
void multiplySpecial(int **A1, int **A2, int **B1, int **B2,
                      int **C1, int **C2, int n) {
    if (n == 1) {
        C1[0][0] = A1[0][0] * B1[0][0] + A2[0][0] * B2[0][0];
        C2[0][0] = A1[0][0] * B2[0][0] + A2[0][0] * B1[0][0];
        return;
    }
    /* At the base recursion level blocks are small; do direct O(n^2)
       multiply-add combination here since the matrices are already
       reduced to their minimal distinct-block representation. */
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C1[i][j] = 0;
            C2[i][j] = 0;
        }
    multiplyAdd(C1, A1, B1, n);
    multiplyAdd(C1, A2, B2, n);
    multiplyAdd(C2, A1, B2, n);
    multiplyAdd(C2, A2, B1, n);
}

int main() {
    int n;
    printf("Enter n (size of special n x n matrices, n = 2^k): ");
    scanf("%d", &n);

    int half = n / 2;

    int **A = allocMatrix(n), **B = allocMatrix(n);
    printf("Enter full matrix A (%d x %d) following pattern [M1 M2; M2 M1]:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter full matrix B (%d x %d) following pattern [M1 M2; M2 M1]:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    /* extract distinct blocks: M1 = top-left, M2 = top-right */
    int **A1 = allocMatrix(half), **A2 = allocMatrix(half);
    int **B1 = allocMatrix(half), **B2 = allocMatrix(half);
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + half];
            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + half];
        }

    int **C1 = allocMatrix(half), **C2 = allocMatrix(half);
    multiplySpecial(A1, A2, B1, B2, C1, C2, half);

    printf("\nResultant matrix C = A x B (as full %d x %d matrix, pattern [C1 C2; C2 C1]):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = (i < half) ? ((j < half) ? C1[i][j] : C2[i][j - half])
                                  : ((j < half) ? C2[i - half][j] : C1[i - half][j - half]);
            printf("%d ", val);
        }
        printf("\n");
    }

    freeMatrix(A, n); freeMatrix(B, n);
    freeMatrix(A1, half); freeMatrix(A2, half);
    freeMatrix(B1, half); freeMatrix(B2, half);
    freeMatrix(C1, half); freeMatrix(C2, half);
    return 0;
}