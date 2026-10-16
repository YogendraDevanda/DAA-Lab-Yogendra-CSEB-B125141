#include <stdio.h>
#include <stdlib.h>

int parent[1000], size[1000], parity[1000];

int find(int x)
{
    if (parent[x] == x)
        return x;

    int p = parent[x];
    parent[x] = find(parent[x]);
    parity[x] ^= parity[p];

    return parent[x];
}

int unite(int u, int v)
{
    int ru = find(u);
    int rv = find(v);

    if (ru == rv)
        return (parity[u] ^ parity[v]) == 1;

    if (size[ru] < size[rv]) {
        int temp = ru;
        ru = rv;
        rv = temp;
    }

    parent[rv] = ru;
    parity[rv] = parity[u] ^ parity[v] ^ 1;
    size[ru] += size[rv];

    return 1;
}

int main()
{
    int V, E, u, v;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    for (int i = 0; i < V; i++) {
        parent[i] = i;
        size[i] = 1;
        parity[i] = 0;
    }

    printf("Enter edges (u v), vertices numbered 0 to V-1:\n");

    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V) {
            printf("Invalid edge. Skipped.\n");
            continue;
        }

        if (unite(u, v))
            printf("Edge (%d, %d) accepted\n", u, v);
        else
            printf("Edge (%d, %d) rejected: odd cycle\n", u, v);
    }

    return 0;
}