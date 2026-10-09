#include <stdio.h>
#include <string.h>

#define MAXN 100
#define MAXL 1000

int overlap(char a[], char b[]) {
    int la = (int)strlen(a);
    int lb = (int)strlen(b);
    int k;

    for (k = (la < lb ? la : lb); k > 0; k--) {
        if (strncmp(a + la - k, b, k) == 0)
            return k;
    }

    return 0;
}

int main() {
    static char s[MAXN][MAXL];
    int n, i, j;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    if (n < 1 || n >= MAXN) {
        printf("Invalid number of strings.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        scanf("%999s", s[i]);
    }

    while (n > 1) {
        int bestI = -1, bestJ = -1, bestOverlap = -1;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i == j)
                    continue;

                int k = overlap(s[i], s[j]);

                if (k > bestOverlap) {
                    bestOverlap = k;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        if (bestI < 0 || bestJ < 0)
            break;

        int lenA = (int)strlen(s[bestI]);
        int lenB = (int)strlen(s[bestJ]);

        if (lenA + lenB - bestOverlap >= MAXL) {
            printf("Merged string exceeds buffer capacity.\n");
            return 1;
        }

        strcat(s[bestI], s[bestJ] + bestOverlap);

        for (i = bestJ; i < n - 1; i++)
            strcpy(s[i], s[i + 1]);

        n--;

        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; ) {
                if (strstr(s[i], s[j]) != NULL) {
                    int k;

                    for (k = j; k < n - 1; k++)
                        strcpy(s[k], s[k + 1]);

                    n--;
                } else if (strstr(s[j], s[i]) != NULL) {
                    strcpy(s[i], s[j]);

                    for (int k = j; k < n - 1; k++)
                        strcpy(s[k], s[k + 1]);

                    n--;
                    j = i + 1;
                } else {
                    j++;
                }
            }
        }
    }

    printf("Greedy superstring: %s\n", s[0]);

    return 0;
}