#include <stdio.h>

int findPartition(int a[], int n)
{
    int i = 0;

    while (i < n && a[i] == 0)
        i++;

    return i;
}

int main()
{
    int n;
    int a[100];

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter %d elements (0s followed by 1s): ", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int p = findPartition(a, n);

    if (p == 0)
        printf("Partition point = 0\n");
    else if (p == n)
        printf("Partition point = %d\n", n);
    else
        printf("Partition point = %d\n", p);

    return 0;
}