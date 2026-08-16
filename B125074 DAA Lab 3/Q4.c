/*
 * DAA Lab-03, Q4: Matrix Multiplication using D&C Approach
 *
 * Write a C program to multiply two square matrices of size n x n
 * using Strassen's method (n assumed to be a power of 2).
 */

#include <stdio.h>
#include <stdlib.h>

int **allocMatrix(int n) {
    int **m = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) m[i] = malloc(n * sizeof(int));
    return m;
}

void freeMatrix(int **m, int n) {
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

int **add(int **A, int **B, int n, int sign) {
    int **C = allocMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + sign * B[i][j];
    return C;
}

int **strassen(int **A, int **B, int n) {
    int **C = allocMatrix(n);

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int half = n / 2;
    int **A11 = allocMatrix(half), **A12 = allocMatrix(half);
    int **A21 = allocMatrix(half), **A22 = allocMatrix(half);
    int **B11 = allocMatrix(half), **B12 = allocMatrix(half);
    int **B21 = allocMatrix(half), **B22 = allocMatrix(half);

    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }

    /* Strassen's 7 products */
    int **M1 = strassen(add(A11, A22, half, 1), add(B11, B22, half, 1), half);
    int **M2 = strassen(add(A21, A22, half, 1), B11, half);
    int **M3 = strassen(A11, add(B12, B22, half, -1), half);
    int **M4 = strassen(A22, add(B21, B11, half, -1), half);
    int **M5 = strassen(add(A11, A12, half, 1), B22, half);
    int **M6 = strassen(add(A21, A11, half, -1), add(B11, B12, half, 1), half);
    int **M7 = strassen(add(A12, A22, half, -1), add(B21, B22, half, 1), half);

    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + half] = M3[i][j] + M5[i][j];
            C[i + half][j] = M2[i][j] + M4[i][j];
            C[i + half][j + half] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }

    freeMatrix(A11, half); freeMatrix(A12, half); freeMatrix(A21, half); freeMatrix(A22, half);
    freeMatrix(B11, half); freeMatrix(B12, half); freeMatrix(B21, half); freeMatrix(B22, half);
    freeMatrix(M1, half); freeMatrix(M2, half); freeMatrix(M3, half); freeMatrix(M4, half);
    freeMatrix(M5, half); freeMatrix(M6, half); freeMatrix(M7, half);

    return C;
}

int main() {
    int n;
    printf("Enter size of square matrices (power of 2): ");
    scanf("%d", &n);

    int **A = allocMatrix(n), **B = allocMatrix(n);

    printf("Enter elements of matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    int **C = strassen(A, B, n);

    printf("\nResultant matrix A x B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    freeMatrix(A, n); freeMatrix(B, n); freeMatrix(C, n);
    return 0;
}