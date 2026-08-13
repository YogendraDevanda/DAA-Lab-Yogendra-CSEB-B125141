#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n = 1000000;
    int heads = 0;

    srand((unsigned)time(NULL));

    for (int i = 0; i < n; i++)
    {
        if (rand() % 2 == 0)
            heads++;
    }

    printf("Fair coin tosses = %d\n", n);
    printf("Heads = %d\n", heads);
    printf("Estimated P(HEAD) = %.6f\n",
           (double)heads / n);

    return 0;
}