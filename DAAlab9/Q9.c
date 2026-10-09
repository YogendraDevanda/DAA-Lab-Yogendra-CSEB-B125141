#include <stdio.h>
#include <limits.h>

#define MAX 15

long long w[MAX];
long long prefix[MAX + 1];
long long dp[MAX][MAX];
int split[MAX][MAX];

long long sum(int i, int j) {
    return prefix[j + 1] - prefix[i];
}

void solve(int n) {
    int i, j, k, len;

    for (i = 0; i < n; i++)
        dp[i][i] = 0;

    for (len = 2; len <= n; len++) {
        for (i = 0; i + len <= n; i++) {
            j = i + len - 1;
            dp[i][j] = LLONG_MAX;

            for (k = i; k < j; k++) {
                long long cost =
                    dp[i][k] + dp[k + 1][j] + sum(i, j);

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
}

void printTree(int i, int j) {
    if (i == j) {
        printf("%d", i + 1);
        return;
    }

    printf("(");
    printTree(i, split[i][j]);
    printf(",");
    printTree(split[i][j] + 1, j);
    printf(")");
}

int main() {
    int n, i;

    printf("Enter number of weights (1-15): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid input.\n");
        return 1;
    }

    prefix[0] = 0;

    for (i = 0; i < n; i++) {
        scanf("%lld", &w[i]);

        if (w[i] < 0) {
            printf("Weights must be non-negative.\n");
            return 1;
        }

        prefix[i + 1] = prefix[i] + w[i];
    }

    solve(n);

    printf("Minimum weighted path length: %lld\n", dp[0][n - 1]);
    printf("Optimal alphabetic tree: ");
    printTree(0, n - 1);
    printf("\n");

    return 0;
}