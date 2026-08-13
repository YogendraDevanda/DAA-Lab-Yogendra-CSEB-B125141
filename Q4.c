#include <stdio.h>

long long toh(int n, char from, char aux, char to)
{
    if (n == 0)
        return 0;

    long long moves = 0;

    moves += toh(n - 1, from, to, aux);

    moves++;

    moves += toh(n - 1, aux, from, to);

    return moves;
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    printf("Minimum moves = %lld\n",
           toh(n, 'A', 'B', 'C'));

    return 0;
}