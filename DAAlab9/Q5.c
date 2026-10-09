#include <stdio.h>

#define MAX 100000

int main() {
    int rating[MAX], candy[MAX];
    int n, i;
    long long total = 0;

    printf("Enter number of children: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of children.\n");
        return 1;
    }

    printf("Enter ratings:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    for (i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1])
            candy[i] = candy[i - 1] + 1;
    }

    for (i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1])
            candy[i] = candy[i + 1] + 1;
    }

    for (i = 0; i < n; i++)
        total += candy[i];

    printf("Candies for each child:\n");

    for (i = 0; i < n; i++)
        printf("%d ", candy[i]);

    printf("\nMinimum total candies: %lld\n", total);

    return 0;
}