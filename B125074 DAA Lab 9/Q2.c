#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

typedef struct Node {
    char symbol;
    int freq;
    int minSymbol;
    struct Node *left, *right;
} Node;

Node *newNode(char c, int f, Node *l, Node *r) {
    Node *p = malloc(sizeof(Node));
    p->symbol = c;
    p->freq = f;
    p->minSymbol = c;
    p->left = l;
    p->right = r;
    if (l && l->minSymbol < p->minSymbol)
        p->minSymbol = l->minSymbol;
    if (r && r->minSymbol < p->minSymbol)
        p->minSymbol = r->minSymbol;
    return p;
}

void insert(Node *heap[], int *n, Node *x) {
    int i = (*n)++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p]->freq < x->freq ||
            (heap[p]->freq == x->freq &&
             heap[p]->minSymbol <= x->minSymbol))
            break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = x;
}

Node *extractMin(Node *heap[], int *n) {
    Node *ans = heap[0];
    Node *last = heap[--(*n)];
    if (*n == 0) return ans;

    int i = 0;
    while (2 * i + 1 < *n) {
        int c = 2 * i + 1;
        if (c + 1 < *n &&
            (heap[c + 1]->freq < heap[c]->freq ||
             (heap[c + 1]->freq == heap[c]->freq &&
              heap[c + 1]->minSymbol < heap[c]->minSymbol)))
            c++;

        if (last->freq < heap[c]->freq ||
            (last->freq == heap[c]->freq &&
             last->minSymbol <= heap[c]->minSymbol))
            break;

        heap[i] = heap[c];
        i = c;
    }
    heap[i] = last;
    return ans;
}

void getLengths(Node *root, int depth, int len[]) {
    if (!root->left && !root->right) {
        len[(unsigned char)root->symbol] =
            depth == 0 ? 1 : depth;
        return;
    }
    if (root->left) getLengths(root->left, depth + 1, len);
    if (root->right) getLengths(root->right, depth + 1, len);
}

int main(void) {
    int n, heapSize = 0;
    char symbols[MAX];
    int freq[MAX], len[256] = {0};
    Node *heap[MAX];

    scanf("%d", &n);
    if (n < 1 || n > 256) return 1;

    for (int i = 0; i < n; i++) {
        scanf(" %c %d", &symbols[i], &freq[i]);
        heap[heapSize] = newNode(symbols[i], freq[i], NULL, NULL);
        insert(heap, &heapSize, heap[heapSize]);
    }

    while (heapSize > 1) {
        Node *a = extractMin(heap, &heapSize);
        Node *b = extractMin(heap, &heapSize);
        Node *p = newNode('\0', a->freq + b->freq, a, b);
        insert(heap, &heapSize, p);
    }

    getLengths(heap[0], 0, len);

    /* Sort symbols by code length, then by symbol. */
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int a = (unsigned char)symbols[i];
            int b = (unsigned char)symbols[j];
            if (len[a] > len[b] ||
                (len[a] == len[b] && a > b)) {
                char tc = symbols[i];
                symbols[i] = symbols[j];
                symbols[j] = tc;
            }
        }
    }

    unsigned long long code = 0;
    int previousLength = len[(unsigned char)symbols[0]];

    printf("Canonical Huffman Codebook:\n");
    for (int i = 0; i < n; i++) {
        int c = (unsigned char)symbols[i];
        if (i > 0) {
            code++;
            code <<= (len[c] - previousLength);
        }

        printf("%c (length %d): ", symbols[i], len[c]);
        for (int b = len[c] - 1; b >= 0; b--)
            printf("%d", (int)((code >> b) & 1ULL));
        printf("\n");
        previousLength = len[c];
    }

    return 0;
}