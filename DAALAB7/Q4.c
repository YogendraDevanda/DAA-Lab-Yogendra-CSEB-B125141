#include <stdio.h>

#define MAX 30

unsigned long long dp[MAX + 1];

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of switches\n");
        return 0;
    }

    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = 2 * dp[i - 1];

        if (i % 2 != 0)
            dp[i]++;
    }

    printf("Initial state: ");
    for (int i = 0; i < n; i++)
        printf("1");

    printf("\nFinal state:   ");
    for (int i = 0; i < n; i++)
        printf("0");

    printf("\nMinimum moves = %llu\n", dp[n]);

    return 0;
}