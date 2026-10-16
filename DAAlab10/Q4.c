#include <stdio.h>

#define MAX 1000

int parent[MAX], sz[MAX];
int active[MAX];
int adj[MAX][MAX];

long long weight[MAX], sum[MAX];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int u, int v)
{
    int a = find(u);
    int b = find(v);

    if (a == b)
        return;

    if (sz[a] < sz[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    sz[a] += sz[b];
    sum[a] += sum[b];
}

long long maximumWeight(int n)
{
    long long best = 0;

    for (int i = 0; i < n; i++) {
        if (active[i] && find(i) == i && sum[i] > best)
            best = sum[i];
    }

    return best;
}

int main()
{
    int n, m, u, v;
    int order[MAX];
    long long answer[MAX];

    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &m);

    if (n <= 0 || n > MAX || m < 0 ||
        m > n * (n - 1) / 2) {
        printf("Invalid input\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        printf("Weight of vertex %d: ", i);
        scanf("%lld", &weight[i]);

        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
        active[i] = 1;
    }

    printf("Enter edges:\n");

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid edge\n");
            return 0;
        }

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printf("Enter deletion order:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &order[i]);

        if (order[i] < 0 || order[i] >= n) {
            printf("Invalid vertex\n");
            return 0;
        }

        active[order[i]] = 0;
    }

    for (int i = n - 1; i >= 0; i--) {
        int x = order[i];

        active[x] = 1;

        for (int j = 0; j < n; j++) {
            if (adj[x][j] && active[j])
                unite(x, j);
        }

        answer[i] = maximumWeight(n);
    }

    printf("Maximum component weight after each deletion:\n");

    for (int i = 0; i < n; i++)
        printf("%lld\n", answer[i]);

    return 0;
}