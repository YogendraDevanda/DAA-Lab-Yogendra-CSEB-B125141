#include <stdio.h>

#define MAX 1000

int parent[MAX], sz[MAX];
long long weight[MAX], sum[MAX];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

int unite(int u, int v, int K)
{
    int a = find(u);
    int b = find(v);

    if (a == b)
        return 0;

    if (sz[a] + sz[b] > K)
        return 0;

    if (sz[a] < sz[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    sz[a] += sz[b];
    sum[a] += sum[b];

    return 1;
}

long long maximumWeight(int n, int K)
{
    long long best = 0;

    for (int i = 0; i < n; i++) {
        if (find(i) == i && sz[i] <= K && sum[i] > best)
            best = sum[i];
    }

    return best;
}

int main()
{
    int n, m, K, u, v;

    printf("Enter vertices, edges and K: ");
    scanf("%d %d %d", &n, &m, &K);

    if (n <= 0 || n > MAX || m < 0 ||
        K < 1 || K > n) {
        printf("Invalid input\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("Weight of vertex %d: ", i);
        scanf("%lld", &weight[i]);

        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
    }

    printf("Enter edges:\n");

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid edge\n");
            continue;
        }

        if (unite(u, v, K))
            printf("Edge accepted\n");
        else
            printf("Edge rejected\n");

        printf("Maximum component weight: %lld\n",
               maximumWeight(n, K));
    }

    return 0;
}