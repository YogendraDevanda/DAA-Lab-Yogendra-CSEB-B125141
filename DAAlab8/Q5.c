#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];
    int dp[n];

    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    for (int i = 0; i < n; i++)
        dp[i] = A[i];

    int answer = A[0];

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                dp[i] = max(dp[i], dp[j] + A[i]);
            }
        }

        answer = max(answer, dp[i]);
    }

    printf("Maximum sum = %d\n", answer);

    return 0;
}