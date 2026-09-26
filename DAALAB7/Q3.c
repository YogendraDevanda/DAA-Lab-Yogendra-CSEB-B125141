#include <stdio.h>

#define MAX 30

long long dp[MAX + 1];
int split[MAX + 1];

long long power2(int n)
{
    return 1LL << n;
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of disks\n");
        return 0;
    }

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = 1000000000LL;
        split[i] = 0;

        for (int k = 1; k < i; k++)
        {
            long long moves = 2 * dp[k] + power2(i - k) - 1;

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("Minimum moves = %lld\n", dp[n]);
    printf("Best split = %d\n", split[n]);

    return 0;
}