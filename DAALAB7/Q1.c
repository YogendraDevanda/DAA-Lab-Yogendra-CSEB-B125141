#include <stdio.h>
typedef struct
{
    int x;
    int y;
} Point;

int original(int x, int y, int n)
{
    return (x >= 0 && y >= 0 && x + y < n);
}

int inverted(int x, int y, int n, int tx, int ty)
{
    int X = x - tx;
    int Y = y - ty;
    int j = -Y;
    int i = X + Y;

    return (i >= 0 && j >= 0 && i + j < n);
}

int main()
{
    int n;
    printf("Enter number of rows: ");
    scanf("%d", &n);
    if (n <= 0 || n > 40)
    {
        printf("Invalid number of rows.\n");
        return 0;
    }
    int total = n * (n + 1) / 2;
    int formula = total / 3;

    printf("\nTotal coins = %d\n", total);
    printf("Minimum moves by formula = %d\n", formula);

    int bestMoves = total + 1;
    int bestTx = 0;
    int bestTy = 0;
    for (int tx = -n; tx <= n; tx++)
    {
        for (int ty = -n; ty <= n; ty++)
        {
            int common = 0;

            for (int x = 0; x < n; x++)
            {
                for (int y = 0; y < n; y++)
                {
                    if (original(x, y, n) &&
                        inverted(x, y, n, tx, ty))
                    {
                        common++;
                    }
                }
            }
            int moves = total - common;
            if (moves < bestMoves)
            {
                bestMoves = moves;
                bestTx = tx;
                bestTy = ty;
            }
        }
    }
    printf("\nBest translation = (%d, %d)\n",
           bestTx, bestTy);

    printf("Minimum moves found by algorithm = %d\n",
           bestMoves);

    if (bestMoves == formula)
    {
        printf("Formula VALIDATED successfully!\n");
    }
    else
    {
        printf("Formula validation failed.\n");
    }
    Point from[1000];
    Point to[1000];
    int countFrom = 0;
    int countTo = 0;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (original(x, y, n) &&
                !inverted(x, y, n, bestTx, bestTy))
            {
                from[countFrom].x = x;
                from[countFrom].y = y;
                countFrom++;
            }
        }
    }
    for (int x = -n; x <= 2 * n; x++)
    {
        for (int y = -n; y <= 2 * n; y++)
        {
            if (inverted(x, y, n, bestTx, bestTy) &&
                !original(x, y, n))
            {
                to[countTo].x = x;
                to[countTo].y = y;
                countTo++;
            }
        }
    }
    if (countFrom != countTo)
    {
        printf("\nError: Source and destination positions do not match.\n");
        return 0;
    }
    printf("\nCoins to move:\n");
    for (int i = 0; i < countFrom; i++)
    {
        printf("Move %d: (%d,%d) -> (%d,%d)\n",
               i + 1,
               from[i].x,
               from[i].y,
               to[i].x,
               to[i].y);
    }
    return 0;
}