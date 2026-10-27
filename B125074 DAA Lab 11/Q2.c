
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int to, next;
} Edge;

int main(void) {
    int n, m;

    // Input: number of vertices and edges
    scanf("%d %d", &n, &m);

    int *head = malloc((size_t)n * sizeof(int));
    Edge *edges = malloc((size_t)(2 * m) * sizeof(Edge));

    if (!head || !edges) return 1;

    for (int i = 0; i < n; i++)
        head[i] = -1;

    int edgeCount = 0;

    // Undirected graph: store both directions.
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        edges[edgeCount] = (Edge){v, head[u]};
        head[u] = edgeCount++;

        edges[edgeCount] = (Edge){u, head[v]};
        head[v] = edgeCount++;
    }

    int K, R;
    scanf("%d %d", &K, &R);

    int *hubs = malloc((size_t)K * sizeof(int));
    int *dist = malloc((size_t)n * sizeof(int));
    int *owner = malloc((size_t)n * sizeof(int));
    int *queue = malloc((size_t)n * sizeof(int));

    if (!hubs || !dist || !owner || !queue) return 1;

    for (int i = 0; i < n; i++) {
        dist[i] = -1;
        owner[i] = -1;
    }

    // Input hub vertices in hub-index order.
    for (int i = 0; i < K; i++)
        scanf("%d", &hubs[i]);

    int front = 0, rear = 0;

    // All hubs are sources at distance zero.
    for (int i = 0; i < K; i++) {
        int h = hubs[i];

        if (dist[h] == -1) {
            dist[h] = 0;
            owner[h] = i + 1;
            queue[rear++] = h;
        } else if (i + 1 < owner[h]) {
            // Handles repeated hub vertices, if present.
            owner[h] = i + 1;
        }
    }

    // Multi-source BFS.
    while (front < rear) {
        int u = queue[front++];

        for (int e = head[u]; e != -1;
             e = edges[e].next) {

            int v = edges[e].to;
            int candidateDist = dist[u] + 1;

            if (dist[v] == -1) {
                dist[v] = candidateDist;
                owner[v] = owner[u];
                queue[rear++] = v;
            } else if (dist[v] == candidateDist &&
                       owner[u] < owner[v]) {
                // Equal distance: smallest hub index wins.
                owner[v] = owner[u];
            }
        }
    }

    // Apply radius constraint.
    for (int v = 0; v < n; v++) {
        if (dist[v] == -1 || dist[v] > R)
            owner[v] = -1;
    }

    printf("Vertex  Owner  Distance\n");

    for (int v = 0; v < n; v++) {
        printf("%d       %d      %d\n",
               v, owner[v], dist[v]);
    }

    free(head);
    free(edges);
    free(hubs);
    free(dist);
    free(owner);
    free(queue);

    return 0;
}
