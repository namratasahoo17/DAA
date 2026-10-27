
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 10
#define HASH_SIZE 524288

typedef struct {
    char (*words)[MAXL + 1];
    int *table;
    int n;
} Dictionary;

// Hash a word using a simple polynomial hash.
unsigned long long hashWord(const char *s) {
    unsigned long long h = 0;

    while (*s) {
        h = h * 31 + (unsigned char)*s;
        s++;
    }

    return h % HASH_SIZE;
}

void insertWord(Dictionary *d, int id) {
    int pos = (int)hashWord(d->words[id]);

    while (d->table[pos] != -1) {
        pos = (pos + 1) % HASH_SIZE;
    }

    d->table[pos] = id;
}

int findWord(Dictionary *d, const char *word) {
    int pos = (int)hashWord(word);
    int start = pos;

    while (d->table[pos] != -1) {
        int id = d->table[pos];

        if (strcmp(d->words[id], word) == 0)
            return id;

        pos = (pos + 1) % HASH_SIZE;

        if (pos == start)
            break;
    }

    return -1;
}

// Expand one complete BFS layer.
// Returns the shortest path length if the searches meet,
// or -1 if there is no meeting in this layer.
int expandLayer(
    int *frontier,
    int frontSize,
    int *nextFrontier,
    int *nextSize,
    int *distThis,
    int *distOther,
    Dictionary *d,
    int L
) {
    *nextSize = 0;

    for (int i = 0; i < frontSize; i++) {
        int u = frontier[i];

        char original[MAXL + 1];
        strcpy(original, d->words[u]);

        for (int p = 0; p < L; p++) {
            char oldChar = d->words[u][p];

            for (char c = 'a'; c <= 'z'; c++) {
                if (c == oldChar)
                    continue;

                d->words[u][p] = c;

                int v = findWord(d, d->words[u]);

                // Only dictionary words may be
                // intermediate vertices.
                if (v == -1 || v >= d->n)
                    continue;

                if (distThis[v] == -1) {
                    distThis[v] = distThis[u] + 1;
                    nextFrontier[(*nextSize)++] = v;
                }

                if (distOther[v] != -1) {
                    d->words[u][p] = oldChar;
                    return distThis[v] + distOther[v];
                }
            }

            d->words[u][p] = oldChar;
        }

        strcpy(d->words[u], original);
    }

    return -1;
}

int main(void) {
    int N;
    scanf("%d", &N);

    Dictionary d;
    d.n = N;

    // Allocate one extra word for A if A is not in D.
    d.words = malloc((size_t)(N + 1) * sizeof(*d.words));
    d.table = malloc((size_t)HASH_SIZE * sizeof(int));

    if (!d.words || !d.table)
        return 1;

    for (int i = 0; i < HASH_SIZE; i++)
        d.table[i] = -1;

    for (int i = 0; i < N; i++) {
        scanf("%10s", d.words[i]);
        insertWord(&d, i);
    }

    char A[MAXL + 1], B[MAXL + 1];
    scanf("%10s %10s", A, B);

    int L = (int)strlen(A);

    if ((int)strlen(B) != L) {
        printf("-1\n");
        free(d.words);
        free(d.table);
        return 0;
    }

    // Identical starting and target words need no mutations.
    if (strcmp(A, B) == 0) {
        printf("0\n");
        free(d.words);
        free(d.table);
        return 0;
    }

    int start = findWord(&d, A);
    int target = findWord(&d, B);

    // The target must be in the dictionary.
    if (target == -1) {
        printf("-1\n");
        free(d.words);
        free(d.table);
        return 0;
    }

    // If A is absent, append it as the starting vertex.
    // Do not insert it into the dictionary hash table.
    if (start == -1) {
        start = N;
        strcpy(d.words[start], A);
    }

    int total = N + 1;

    int *distA = malloc((size_t)total * sizeof(int));
    int *distB = malloc((size_t)total * sizeof(int));

    int *frontA = malloc((size_t)total * sizeof(int));
    int *nextA = malloc((size_t)total * sizeof(int));
    int *frontB = malloc((size_t)total * sizeof(int));
    int *nextB = malloc((size_t)total * sizeof(int));

    if (!distA || !distB || !frontA || !nextA ||
        !frontB || !nextB)
        return 1;

    for (int i = 0; i < total; i++) {
        distA[i] = -1;
        distB[i] = -1;
    }

    distA[start] = 0;
    distB[target] = 0;

    frontA[0] = start;
    frontB[0] = target;

    int sizeA = 1;
    int sizeB = 1;
    int answer = -1;

    while (sizeA > 0 && sizeB > 0) {
        if (sizeA <= sizeB) {
            int nextSize = 0;

            answer = expandLayer(
                frontA, sizeA, nextA, &nextSize,
                distA, distB, &d, L
            );

            if (answer != -1)
                break;

            int *temp = frontA;
            frontA = nextA;
            nextA = temp;
            sizeA = nextSize;

        } else {
            int nextSize = 0;

            answer = expandLayer(
                frontB, sizeB, nextB, &nextSize,
                distB, distA, &d, L
            );

            if (answer != -1)
                break;

            int *temp = frontB;
            frontB = nextB;
            nextB = temp;
            sizeB = nextSize;
        }
    }

    printf("%d\n", answer);

    free(d.words);
    free(d.table);
    free(distA);
    free(distB);
    free(frontA);
    free(nextA);
    free(frontB);
    free(nextB);

    return 0;
}
