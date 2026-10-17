#include <stdio.h>
#include <stdlib.h>

#define MAXQ 200005

int parent[MAXQ], sz[MAXQ];
int R, C;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (sz[a] < sz[b]) {
        int t = a;
        a = b;
        b = t;
    }

    parent[b] = a;
    sz[a] += sz[b];
    return 1;
}

int main(void) {
    int Q;
    scanf("%d %d %d", &R, &C, &Q);

    int total = R * C;
    int *land = calloc(total, sizeof(int));

    if (total > MAXQ || land == NULL)
        return 1;

    for (int i = 0; i < total; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    int islands = 0;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int q = 0; q < Q; q++) {
        int r, c;
        scanf("%d %d", &r, &c);

        /* Input coordinates are 0-based. */
        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid cell\n");
            continue;
        }

        int id = r * C + c;

        if (land[id]) {
            printf("%d\n", islands);
            continue;
        }

        land[id] = 1;
        islands++;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;

            int nid = nr * C + nc;

            if (land[nid] && unite(id, nid))
                islands--;
        }

        printf("%d\n", islands);
    }

    free(land);
    return 0;
}