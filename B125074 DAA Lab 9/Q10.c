
#include <stdio.h>
#include <string.h>

#define MAXN 100
#define MAXL 10000

char s[MAXN][MAXL];

int overlap(const char *a, const char *b) {
    int la = strlen(a);
    int lb = strlen(b);
    int limit = la < lb ? la : lb;

    for (int len = limit; len > 0; len--) {
        if (strncmp(a + la - len, b, len) == 0)
            return len;
    }
    return 0;
}

void mergeStrings(char *result, const char *a,
                  const char *b) {
    if (strstr(a, b) != NULL) {
        strcpy(result, a);
        return;
    }

    if (strstr(b, a) != NULL) {
        strcpy(result, b);
        return;
    }

    int ov = overlap(a, b);

    strcpy(result, a);
    strcat(result, b + ov);
}

int main(void) {
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    if (n < 1 || n >= MAXN) {
        printf("Invalid number of strings\n");
        return 1;
    }

    printf("Enter the strings:\n");
    for (int i = 0; i < n; i++) {
        scanf("%9999s", s[i]);
    }

    while (n > 1) {
        int bestI = 0, bestJ = 1;
        int bestOverlap = -1;
        int reverse = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int ov1 = overlap(s[i], s[j]);
                int ov2 = overlap(s[j], s[i]);

                if (ov1 > bestOverlap) {
                    bestOverlap = ov1;
                    bestI = i;
                    bestJ = j;
                    reverse = 0;
                }

                if (ov2 > bestOverlap) {
                    bestOverlap = ov2;
                    bestI = i;
                    bestJ = j;
                    reverse = 1;
                }
            }
        }

        char merged[2 * MAXL];

        if (reverse)
            mergeStrings(merged, s[bestJ], s[bestI]);
        else
            mergeStrings(merged, s[bestI], s[bestJ]);

        strcpy(s[bestI], merged);

        for (int i = bestJ; i < n - 1; i++)
            strcpy(s[i], s[i + 1]);

        n--;
    }

    printf("Greedy superstring: %s\n", s[0]);
    printf("Length: %zu\n", strlen(s[0]));

    return 0;
}
