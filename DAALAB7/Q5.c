#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("n must be greater than 1.\n");
        return 0;
    }

    printf("\nShooter's strategy:\n");

    for (int cycle = 0; cycle < 2 * n; cycle++)
    {
        int pos;

        if (cycle % 2 == 0)
        {
            for (pos = 2; pos <= n; pos++)
                printf("%d ", pos);
        }
        else
        {
            for (pos = n - 1; pos >= 1; pos--)
                printf("%d ", pos);
        }
    }

    printf("\n");

    return 0;
}