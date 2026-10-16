#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX], sz[MAX];

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
}

int compare(const void *a, const void *b)
{
    return (*(int *)a > *(int *)b) -
           (*(int *)a < *(int *)b);
}

int main()
{
    int n, m;
    int A[MAX], result[MAX];
    int vertices[MAX][MAX];
    int values[MAX][MAX];
    int vc[MAX] = {0}, valc[MAX] = {0};

    printf("Enter n and m: ");
    scanf("%d %d", &n, &m);

    if (n <= 0 || n > MAX || m < 0 ||
        m > n * (n - 1) / 2) {
        printf("Invalid input\n");
        return 0;
    }

    printf("Enter permutation:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        sz[i] = 1;
        result[i] = A[i];
    }

    printf("Enter allowed swaps:\n");

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid edge\n");
            return 0;
        }

        unite(u, v);
    }

    for (int i = 0; i < n; i++) {
        int root = find(i);

        vertices[root][vc[root]++] = i;
        values[root][valc[root]++] = A[i];
    }

    for (int i = 0; i < n; i++) {
        if (vc[i] == 0)
            continue;

        qsort(vertices[i], vc[i], sizeof(int), compare);
        qsort(values[i], valc[i], sizeof(int), compare);

        for (int j = 0; j < vc[i]; j++)
            result[vertices[i][j]] = values[i][j];
    }

    printf("Lexicographically smallest permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", result[i]);

    printf("\n");

    return 0;
}