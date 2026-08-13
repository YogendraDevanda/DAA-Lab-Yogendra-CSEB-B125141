#include <stdio.h>

int hasDuplicate(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] == a[j])
                return 1;
        }
    }

    return 0;
}

int main()
{
    int n;
    int a[1000];

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter %d numbers: ", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if (hasDuplicate(a, n))
        printf("Duplicate exists.\n");
    else
        printf("No duplicate exists.\n");

    printf("Worst-case time complexity: O(n^2)\n");

    return 0;
}