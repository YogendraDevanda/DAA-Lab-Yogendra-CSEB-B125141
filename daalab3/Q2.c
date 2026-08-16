#include <stdio.h>

int findDefective(int coins[], int left, int right)
{
    if (left == right)
        return left;

    int n = right - left + 1;

    if (n == 2)
    {
        return (coins[left] < coins[right]) ? left : right;
    }

    int third = n / 3;

    int l1 = left;
    int r1 = left + third - 1;

    int l2 = left + third;
    int r2 = left + 2 * third - 1;

    int sum1 = 0, sum2 = 0;

    for (int i = l1; i <= r1; i++)
        sum1 += coins[i];

    for (int i = l2; i <= r2; i++)
        sum2 += coins[i];

    if (sum1 == sum2)
    {
        // Defective coin is in the remaining group
        return findDefective(coins, l2 + third, right);
    }
    else if (sum1 < sum2)
    {
        // First group is lighter
        return findDefective(coins, l1, r1);
    }
    else
    {
        // Second group is lighter
        return findDefective(coins, l2, r2);
    }
}

int main()
{
    int n;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter weights of coins:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    int index = findDefective(coins, 0, n - 1);

    printf("Defective coin is at position %d\n", index + 1);
    printf("Weight = %d\n", coins[index]);

    return 0;
}