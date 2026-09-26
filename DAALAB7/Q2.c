#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int eggDrop(int E, int F)
{
    int dp[E + 1][F + 1];

    for (int e = 1; e <= E; e++)
    {
        dp[e][0] = 0;
        dp[e][1] = 1;
    }

    for (int f = 0; f <= F; f++)
        dp[1][f] = f;

    for (int e = 2; e <= E; e++)
    {
        for (int f = 2; f <= F; f++)
        {
            dp[e][f] = F + 1;

            for (int x = 1; x <= f; x++)
            {
                int broken = dp[e - 1][x - 1];
                int notBroken = dp[e][f - x];

                int attempts = 1 + max(broken, notBroken);

                if (attempts < dp[e][f])
                    dp[e][f] = attempts;
            }
        }
    }

    return dp[E][F];
}

int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    printf("\nMinimum droppings = %d\n",
           eggDrop(E, F));

    return 0;
}