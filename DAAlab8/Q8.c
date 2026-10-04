#include <stdio.h>
#include <float.h>

#define MAX 50

double p[MAX + 1];
double q[MAX + 1];

double cost[MAX + 1][MAX + 1];
double weight[MAX + 1][MAX + 1];

int root[MAX + 1][MAX + 1];

void printTree(int i, int j, int level)
{
    if (i > j)
    {
        printf("%*sDummy key d%d\n", level * 4, "", j);
        return;
    }

    int r = root[i][j];

    printf("%*sKey k%d\n", level * 4, "", r);

    printTree(i, r - 1, level + 1);
    printTree(r + 1, j, level + 1);
}

int main()
{
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter successful search probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter unsuccessful search probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    for (int i = 1; i <= n + 1; i++)
    {
        cost[i][i - 1] = q[i - 1];
        weight[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            cost[i][j] = DBL_MAX;

            weight[i][j] = weight[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++)
            {
                double currentCost =
                    cost[i][r - 1] +
                    cost[r + 1][j] +
                    weight[i][j];

                if (currentCost < cost[i][j])
                {
                    cost[i][j] = currentCost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.4lf\n", cost[1][n]);

    printf("\nOptimal Binary Search Tree:\n");

    printTree(1, n, 0);

    return 0;
}