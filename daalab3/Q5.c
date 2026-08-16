#include <stdio.h>

#define MAX 64

void specialMultiply(int A[MAX][MAX], int B[MAX][MAX],
                     int C[MAX][MAX], int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A1[MAX][MAX], A2[MAX][MAX];
    int A3[MAX][MAX], A4[MAX][MAX];

    int B1[MAX][MAX], B2[MAX][MAX];
    int B3[MAX][MAX], B4[MAX][MAX];

    int S1[MAX][MAX], S2[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];

    int P[MAX][MAX], Q[MAX][MAX];

    // Divide matrices into four blocks
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];
            A3[i][j] = A[i + k][j];
            A4[i][j] = A[i + k][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
            B3[i][j] = B[i + k][j];
            B4[i][j] = B[i + k][j + k];
        }
    }

    // S1 = A1 + A2
    // S2 = B1 + B2
    // T1 = A1 - A2
    // T2 = B1 - B2

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            S1[i][j] = A1[i][j] + A2[i][j];
            S2[i][j] = B1[i][j] + B2[i][j];

            T1[i][j] = A1[i][j] - A2[i][j];
            T2[i][j] = B1[i][j] - B2[i][j];
        }
    }

    // P = (A1 + A2)(B1 + B2)
    specialMultiply(S1, S2, P, k);

    // Q = (A1 - A2)(B1 - B2)
    specialMultiply(T1, T2, Q, k);

    // Construct result
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int X = (P[i][j] + Q[i][j]) / 2;
            int Y = (P[i][j] - Q[i][j]) / 2;

            C[i][j] = X;
            C[i][j + k] = Y;
            C[i + k][j] = Y;
            C[i + k][j + k] = X;
        }
    }
}

int main()
{
    int n;

    printf("Enter n (power of 2): ");
    scanf("%d", &n);

    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Enter first special matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    }

    printf("Enter second special matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    }

    specialMultiply(A, B, C, n);

    printf("\nResult matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);

        printf("\n");
    }

    return 0;
}