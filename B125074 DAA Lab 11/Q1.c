
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

typedef struct {
    int to, weight, next;
} Edge;

typedef struct {
    int *a;
    int front, size, capacity;
} Deque;

void initDeque(Deque *dq, int capacity) {
    dq->a = malloc((size_t)capacity * sizeof(int));
    dq->front = 0;
    dq->size = 0;
    dq->capacity = capacity;
}

void pushFront(Deque *dq, int x) {
    dq->front = (dq->front - 1 + dq->capacity)
                % dq->capacity;
    dq->a[dq->front] = x;
    dq->size++;
}

void pushBack(Deque *dq, int x) {
    int pos = (dq->front + dq->size) % dq->capacity;
    dq->a[pos] = x;
    dq->size++;
}

int popFront(Deque *dq) {
    int x = dq->a[dq->front];
    dq->front = (dq->front + 1) % dq->capacity;
    dq->size--;
    return x;
}

int main(void) {
    int n, m, source;
    long long C;

    scanf("%d %d", &n, &m);
    scanf("%d %lld", &source, &C);

    Edge *edges = malloc((size_t)m * sizeof(Edge));
    int *head = malloc((size_t)n * sizeof(int));

    if (!edges || !head) return 1;

    for (int i = 0; i < n; i++)
        head[i] = -1;

    // Read directed edges: u v weight
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        edges[i].to = v;
        edges[i].weight = w;
        edges[i].next = head[u];
        head[u] = i;
    }

    // State (v, p) is stored as 2*v + p.
    long long *dist = malloc(
        (size_t)(2 * n) * sizeof(long long));

    for (int i = 0; i < 2 * n; i++)
        dist[i] = INF;

    // Each successful relaxation adds at most one entry.
    int capacity = 2 * (n + m) + 10;
    Deque dq;
    initDeque(&dq, capacity);

    int start = 2 * source;  // source with even parity
    dist[start] = 0;
    pushFront(&dq, start);

    while (dq.size > 0) {
        int state = popFront(&dq);
        int u = state / 2;
        int parity = state % 2;

        for (int e = head[u]; e != -1;
             e = edges[e].next) {

            int v = edges[e].to;
            int w = edges[e].weight;
            int newParity = parity ^ w;
            int nextState = 2 * v + newParity;

            long long newDist = dist[state] + w;

            if (newDist < dist[nextState]) {
                dist[nextState] = newDist;

                if (w == 0)
                    pushFront(&dq, nextState);
                else
                    pushBack(&dq, nextState);
            }
        }
    }

    printf("Vertex  MinimumCost\n");

    for (int v = 0; v < n; v++) {
        long long even = dist[2 * v];
        long long odd = dist[2 * v + 1];

        if (even == INF && odd == INF) {
            printf("%d      Unreachable\n", v);
            continue;
        }

        // Add the penalty only to odd-parity paths.
        long long answer = even;

        if (odd != INF && odd + C < answer)
            answer = odd + C;

        printf("%d      %lld\n", v, answer);
    }

    free(dq.a);
    free(dist);
    free(head);
    free(edges);

    return 0;
}
