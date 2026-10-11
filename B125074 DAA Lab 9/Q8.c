#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, end;
} Meeting;

Meeting meetings[200005];
int heap[200005], size = 0;

int compare(const void *a, const void *b) {
    Meeting x = *(Meeting *)a;
    Meeting y = *(Meeting *)b;
    return (x.start > y.start) - (x.start < y.start);
}

void push(int x) {
    int i = size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] <= x) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = x;
}

int popMin(void) {
    int ans = heap[0], last = heap[--size];
    int i = 0;

    while (2 * i + 1 < size) {
        int c = 2 * i + 1;
        if (c + 1 < size && heap[c + 1] < heap[c])
            c++;
        if (last <= heap[c]) break;
        heap[i] = heap[c];
        i = c;
    }
    if (size > 0) heap[i] = last;
    return ans;
}

int main(void) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &meetings[i].start,
                       &meetings[i].end);

    qsort(meetings, n, sizeof(Meeting), compare);

    int rooms = 0;

    for (int i = 0; i < n; i++) {
        if (size > 0 && heap[0] <= meetings[i].start) {
            popMin();
        } else {
            rooms++;
        }

        push(meetings[i].end);
    }

    printf("Minimum meeting rooms = %d\n", rooms);
    return 0;
}